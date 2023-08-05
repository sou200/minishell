/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 00:15:27 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/06 00:20:09 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_var(const char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	check_var1(const char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[i])
	{
		if (var[i] == '=')
			break ;
		if (var[i] == '+' && var[i + 1] == '=')
			break ;
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	**realloc_env(int n)
{
	char	**cpy;

	cpy = ft_malloc(sizeof(char *) * (n));
	return (cpy);
}

void	*ft_malloc(size_t size)
{
	void	*space;

	space = malloc(size);
	if (!space)
		ft_error(ENOMEM, "malloc: ");
	return (space);
}

void	error_malloc(int condition)
{
	if (!condition)
		return ;
	ft_error(ENOMEM, "malloc: ");
}
