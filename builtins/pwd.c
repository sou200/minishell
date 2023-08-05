/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 08:49:29 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/04 21:06:18 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = default_env[0];
	if (!pwd)
		pwd = getcwd(0, 0);
	if (!pwd)
	{
		error_write(PWD_ERROR);
		return (1);
	}
	if (!ft_strncmp(pwd, "/private/",9))
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
	free(pwd);
	return (0);
}
