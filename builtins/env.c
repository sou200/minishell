/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:58:25 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/18 12:02:26 by fel-hazz         ###   ########.fr       */
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

void	remove_var(const char *var)
{
	int		i;
	char	**new;
	int		y;

	i = 0;
	if (!var || !ft_getenv(var))
		return ;
	while (gl.env[i] && ft_pathcmp(var, gl.env[i]))
		i++;
	if (!gl.env[i])
		return ;
	new = realloc_env(size_double(gl.env));
	y = -1;
	while (gl.env[++y] && (y != i))
		new[y] = gl.env[y];
	free(gl.env[y]);
	y--;
	while (gl.env[++y + 1])
		new[y] = gl.env[y + 1];
	new[y] = 0;
	free(gl.env);
	gl.env = new;
}
