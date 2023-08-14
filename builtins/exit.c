/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:53:30 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/14 17:59:26 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi1(const char *str)
{
	int			i;
	long long	z;
	int			s;

	z = 0;
	s = 1;
	i = 0;
	while (str && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str && (str[i] == '-' || str[i] == '+') && str[i++] == '-')
		s = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		z = z * 10 + (str[i] - 48);
		if ((z * s > LONG_MAX) || (z * s < LONG_MIN)
			|| ((((z * 10 + (str[i] - 48))
						/ 10 - ((str[i] - 48) / 10))) * s != z * s))
			break ;
		i++;
	}
	if (str[i])
		return (print_error1(3, "minishell: exit: ", str
				, ": numeric argument required\n"), gl.return_value = 255, 0);
	return ((z * s) % 256);
}

int	ft_exit1(char **cmd)
{
	int	r;

	gl.return_value = 0;
	if (!cmd || !cmd[0])
		ft_exit(0);
	r = ft_atoi1(cmd[0]);
	if (gl.return_value != 0)
		ft_exit(gl.return_value);
	if (!cmd[1])
		ft_exit(r);
	else
		return (print_error1(1, "minishell: exit: too many arguments\n")
			, gl.return_value = 1, 1);
	return (0);
}
