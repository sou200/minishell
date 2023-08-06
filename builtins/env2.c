/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 02:56:08 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/06 02:57:05 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(void)
{
	int	i;

	i = 0;
	if (!env)
		return (1);
	while (env && env[i])
		printf("%s\n", env[i++]);
	return (0);
}

int	ft_printenv(const char *var)
{
	const char	*s;

	s = ft_getenv(var);
	if (s)
		printf("%s\n", ft_getenv(var));
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
	if (env[i])
		return ((env[i]));
	i = 0;
	while (default_env[i] && ft_pathcmp(var, default_env[i]))
		i++;
	return (default_env[i]);
}
