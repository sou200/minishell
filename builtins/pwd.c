/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 08:49:29 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/07/16 15:30:34 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char *pwd;
    struct stat p;

	pwd = getcwd(0, 0);
	if (!pwd)
		return ;
    lstat(pwd,&p);
    printf("%d \n",S_ISLNK(p.st_mode));
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	free(pwd);
}