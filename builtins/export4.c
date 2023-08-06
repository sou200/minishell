/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 00:21:19 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/06 05:40:49 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_value(char *var, t_list *tmp)
{
	int		i;
	char	*str;

	if (!check_var1(var))
		return (print_error(1, 3
				, "minishell: export: `", var, "': not a valid identifier\n"));
	if (!ft_strchr(var, '='))
		return ;
	i = which_export(var);
	if (i == 2)
		str = join_export((char *)(tmp->content), var);
	else
		str = ft_exportage(var);
	free(tmp->content);
	tmp->content = str;
	if (i == 2)
		env_append(str, var);
	else
		add_var(var);
}

char	*join_export(char *old, char *var)
{
	char	*str;
	int		i;
	char	*tmp;

	i = 0;
	while (old[i] && !((old[i] == '"') && (old[i + 1] == '\0')))
		i++;
	if (!old[i])
		return (ft_exportage3(var));
	old[i] = '\0';
	tmp = ft_strjoin(old, ft_strchr(var, '=') + 1);
	error_malloc(!tmp);
	str = ft_strjoin(tmp, "\"");
	error_malloc(!str);
	return (free(tmp), str);
}

void	env_append(char *str, char *var)
{
	int		x;
	char	*s;
	char	*t;

	x = 0;
	while (var[x] && !(var[x] == '+' || var[x] == '='))
		x++;
	s = ft_malloc(x + 2);
	x = -1;
	while (var[++x] && !(var[x] == '+' || var[x] == '='))
		s[x] = var[x];
	s[x++] = '=';
	s[x] = '\0';
	x = env_append_find(str, var);
	if (!ft_strchr(str, '='))
		return (add_var(s), free(s));
	t = ft_substr(ft_strchr(str, '=') + 2, 0,
			ft_strlen(ft_strchr(str, '=') + 2) - 1);
	error_malloc(!t);
	str = ft_strjoin(s, t);
	error_malloc(!str);
	ft_free(2, s, t);
	if (!env[x])
		return (add_var(str), free(str));
	env[x] = str;
}

int	env_append_find(char *str, char *var)
{
	int	i;
	int	x;

	i = 0;
	while (env[i])
	{
		x = 0;
		while (env[i][x] && var[x] && env[i][x] == var[x]
				&& !(env[i][x] == var[x] && env[i][x] == '='))
			x++;
		if (var[x] == '+' && var[x + 1] == '=' && env[i][x] == '=')
			break ;
		if (env[i][x] == var[x] && env[i][x] == '=')
			break ;
		i++;
	}
	free(env[i]);
	return (i);
}

t_list	*export_exists(char *value)
{
	t_list	*traveler;
	char	*str;
	int		i;
	int		y;

	traveler = export_list;
	while (traveler)
	{
		i = 11;
		y = 0;
		str = ((char *)(traveler->content));
		while (str[i] && value[y] && (str[i] == value[y])
			&& !(str[i] == '=' && value[y] == '='))
		{
			i++;
			y++;
		}
		if (value[y] == '+')
			y++;
		if (str[i] == value[y] || (str[i] == '=' && !value[y])
			|| (!str[i] && value[y] == '='))
			return (traveler);
		traveler = traveler->next;
	}
	return (0);
}
