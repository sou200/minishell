/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:32:23 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/17 10:33:52 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	holder(int c)
{
	(void ) c;
	gl.return_value = 300;
}

void	holder1(int c)
{
	(void ) c;
	gl.return_value = 400;
}

void	controlec2(int c)
{
	(void ) c;
	kill(0, SIGUSR2);
	exit(0);
}
