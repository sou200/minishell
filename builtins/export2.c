/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:35:22 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/09 12:27:38 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_value(char *var)
{
	int		i;

	if (!check_var1(var))
		return (gl.return_value = 1, print_error1(3
				, "minishell: export: `", var, "': not a valid identifier\n"));
	i = which_export(var);
	if (i == 1)
		ft_lstaddandsort(&gl.export_list, ft_lstnew(ft_exportage(var)));
	else if (i == 3)
		ft_lstaddandsort(&gl.export_list, ft_lstnew(ft_exportage1(var)));
	else
		ft_lstaddandsort(&gl.export_list, ft_lstnew(ft_exportage3(var)));
	if (i == 1)
		add_var(var);
	if (i == 2)
		empty_var(var);
}

int	which_export(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (1);
		if (var[i] == '+' && var[i + 1] == '=')
			return (2);
		i++;
	}
	return (3);
}

void	add_var(const char *var)
{
	int		i;
	char	**new;
	int		y;

	i = 0;
	if (!var)
		return ;
	if (add_var1(var))
		return ;
	new = realloc_env(size_double(gl.env) + 2);
	error_malloc(!new);
	y = -1;
	while (gl.env[++y])
		new[y] = gl.env[y];
	new[y] = ft_strdup(var);
	error_malloc(!new[y]);
	new[++y] = 0;
	free(gl.env);
	gl.env = new;
}

int	add_var1(const char *var)
{
	int	i;
	int	x;

	i = -1;
	while (gl.env[++i])
	{
		x = 0;
		while (gl.env[i][x] && var[x] && gl.env[i][x] == var[x]
			&& !(gl.env[i][x] == var[x] && gl.env[i][x] == '='))
			x++;
		if (!var[x] && gl.env[i][x] == '=')
			return (1);
		if (gl.env[i][x] == var[x] && gl.env[i][x] == '=')
			break ;
	}
	if (!gl.env[i] || !(gl.env[i][x] == var[x] && gl.env[i][x] == '='))
		return (0);
	return (free(gl.env[i]), gl.env[i] = ft_strdup(var), error_malloc(!gl.env[i]), 1);
}

void	empty_var(char *var)
{
	int		x;
	char	*s;

	x = 0;
	s = ft_malloc(ft_strlen(var));
	x = -1;
	while (var[++x] && !(var[x] == '+' || var[x] == '='))
		s[x] = var[x];
	s[x] = '=';
	while (var[++x + 1])
		s[x] = var[x + 1];
	s[x] = '\0';
	add_var(s);
	free(s);
}
