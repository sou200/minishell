/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 02:56:08 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/06 05:50:49 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(void)
{
	int	i;

	return_value = 0;
	i = 0;
	if (!env)
		return (return_value = 1, return_value);
	while (env && env[i])
		printf("%s\n", env[i++]);
	return (return_value);
}

int	ft_printenv(const char *var)
{
	const char	*s;

	return_value = 0;
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
	while (env[i] && ft_pathcmp(var, env[i]))
		i++;
	return ((env[i]));
}
