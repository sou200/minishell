/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 07:10:11 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/14 18:41:20 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	if (s[i] == '-' && s[i + 1])
	{
		i++;
		while (s[i] == 'n')
			i++;
		if (!s[i])
			return (0);
	}
	return (1);
}

int	ft_echo(char **cmd)
{
	int	y;
	int	x;

	x = 1;
	if (!cmd)
		return (0);
	while (1)
	{
		y = check_n(cmd[0]);
		if (y == 0)
		{
			x = 0;
			cmd++;
		}
		else
			break ;
	}
	while (*cmd)
	{
		ft_putstr_fd(*cmd, 1);
		cmd++;
		if (*cmd)
			write(1, " ", 1);
	}
	return (write(1, "\n", x), 0);
}

char	*ft_strjoin_free(char *a, char *b, int i, int j)
{
	char	*res;

	res = ft_strjoin(a, b);
	if (i && a)
		free(a);
	if (j && b)
		free(b);
	return (res);
}
