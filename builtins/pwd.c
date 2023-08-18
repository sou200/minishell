/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 08:49:29 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/18 10:48:28 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*pwd;
	int		a;

	gl.return_value = 0;
	a = 0;
	pwd = gl.default_env[0];
	if (!pwd || !pwd[0])
		pwd = getcwd(0, 0) + (a++ == -1);
	if (!pwd)
		return (big_error(PWD_ERROR), gl.return_value = 1, gl.return_value);
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	if (a == 1)
		free(pwd);
	return (0);
}
