/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:58:25 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/06 07:02:31 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pathcmp(const char *s1, const char *PATH)
{
	size_t	i;

	i = 0;
	if (!s1 && !PATH)
		return (0);
	if (!s1 || !PATH)
		return (1);
	while (s1[i] && PATH[i] && PATH[i] != '=')
	{
		if (s1[i] != PATH[i])
			return (1);
		i++;
	}
	if (PATH[i] == '=' && !s1[i])
		return (0);
	return (1);
}

int	size_double(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	free_table(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		str[i] = 0;
		i++;
	}
	free(str);
}

void	print_error1(int d, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, d);
	while (i < d)
	{
		error_write(va_arg(ap, char *));
		i++;
	}
	va_end(ap);
}

// void	remove_var_check(const char *var)
// {
// 	if (!var || !ft_getenv(var))
// 		return ;
// 	if (!check_var(var))
// 		return (print_error1(1, 3
// 				, "minishell: unset: `", var, "': not a valid identifier\n"));
// }

void	remove_var(const char *var)
{
	int		i;
	char	**new;
	int		y;

	i = 0;
	if (!var || !ft_getenv(var))
		return ;
	while (env[i] && ft_pathcmp(var, env[i]))
		i++;
	if (!env[i])
		return ;
	new = realloc_env(size_double(env));
	y = -1;
	while (env[++y] && (y != i))
		new[y] = env[y];
	if (!env[y])
		return ;
	free(env[y]);
	y--;
	while (env[++y + 1])
		new[y] = env[y + 1];
	new[y] = 0;
	free(env);
	env = new;
}
