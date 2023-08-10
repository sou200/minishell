/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 02:56:08 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/09 12:27:38 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(void)
{
	int	i;

	gl.return_value = 0;
	i = 0;
	if (!gl.env)
		return (gl.return_value = 1, gl.return_value);
	while (gl.env && gl.env[i])
		printf("%s\n", gl.env[i++]);
	return (gl.return_value);
}

int	ft_printenv(const char *var)
{
	const char	*s;

	gl.return_value = 0;
	s = ft_getenv(var);
	if (s)
		printf("%s\n", s);
	else
		s = ft_getenv2(var);
	if (s)
		printf("%s\n", s);
	return (0);
}

int	is_num(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

const char	*ft_getenv(const char *var)
{
	int		i;

	i = 0;
	if (!var)
		return (0);
	while (gl.env[i] && ft_pathcmp(var, gl.env[i]))
		i++;
	return ((gl.env[i]));
}
