/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 08:49:29 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/07/19 17:29:41 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char *pwd;

	pwd = getcwd(0, 0);
	pwd = getenv("PWD");
	if (!pwd)
	{
		perror("getcwd");
		return ;
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
}
