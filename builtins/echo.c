/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 07:10:11 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/07/27 17:44:42 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	check_n(char *s)
{
	int	i;

	i = 0;
	if (s[i++] == '-' && s[i])
	{
		while (s[i] == 'n')
			i++;
		if (!s[i])
			return (0);
	}
	return (1);
}

void	ft_echo(char **cmd)
{
	int	y;

	y = check_n(cmd[0]);
	if (y == 0)
		cmd++;
	while (*cmd)
	{
		ft_putstr_fd(*cmd, 1);
		cmd++;
		if (*cmd)
			write(1, " ", 1);
	}
	if (y)
		write(1, "\n", 1);
	exit(0);
}