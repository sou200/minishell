/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 04:54:21 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/15 15:38:54 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_unset(const char *var)
{
	if (!check_var(var))
		return (print_error1(3
				, "minishell: unset: `", var, "': not a valid identifier\n"), 1);
	return (0);
}

void	remove_var1(const char *var)
{
	int		i;

	i = 0;
	if (!var || !ft_getenv2(var))
		return ;
	while (gl.default_env[i] && ft_pathcmp(var, gl.default_env[i]))
		i++;
	if (!gl.default_env[i])
		return ;
	free (gl.default_env[i]);
	gl.default_env[i] = ft_strdup("");
	error_malloc(!gl.default_env[i]);
}

void	remove_export(const char *var)
{
	t_list	*tmp;

	tmp = export_exists((char *)var);
	if (!tmp)
		return ;
	if (!tmp->next)
		tmp->prev->next = 0;
	else
	{
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
	}
	free(tmp->content);
	free(tmp);
}

int	ft_unset(char **cmd)
{
	int	i;

	gl.return_value = 0;
	if (!cmd || !cmd[0])
		return (0);
	i = -1;
	while (cmd[++i])
	{
		if (valid_unset(cmd[i]))
		{
			gl.return_value = 1;
			continue ;
		}
		remove_var(cmd[i]);
		remove_var1(cmd[i]);
		remove_export(cmd[i]);
	}
	return (0);
}

const char	*ft_getenv2(const char *var)
{
	int		i;

	i = 0;
	if (!var)
		return (0);
	i = 0;
	while (gl.default_env[i] && ft_pathcmp(var, gl.default_env[i]))
		i++;
	return (gl.default_env[i]);
}
