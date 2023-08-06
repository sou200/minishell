/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 08:49:29 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/06 05:51:18 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*pwd;
	int		a;

	return_value = 0;
	a = 0;
	pwd = default_env[0];
	if (!pwd)
		pwd = getcwd(0, 0) + (a++ == -1);
	if (!pwd)
		return (error_write(PWD_ERROR), return_value = 1, return_value);
	if (!ft_strncmp(pwd, "/private/", 9))
	{
		pwd += 8;
		ft_putstr_fd(pwd, 1);
		write(1, "\n", 1);
		pwd -= 8;
	}
	else
	{
		ft_putstr_fd(pwd, 1);
		write(1, "\n", 1);
	}
	if (a == 1)
		free(pwd);
	return (0);
}
