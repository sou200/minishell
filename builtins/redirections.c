/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 01:00:58 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/05 01:51:02 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close(int n, ...)
{
	va_list	t;
	int		i;

	i = 0;
	va_start(t, n);
	while (i < n)
	{
		if (close(va_arg(t, int)) == -1)
			ft_error(1, "close ");
		i++;
	}
	va_end(t);
}

int	redirect_input(t_list *left_red, int pipe)
{
	t_token	*holder;

	while (left_red)
	{
		holder = (t_token *)left_red->content;
		if (!holder)
			return (pipe);
		if (holder->type == TYPE_RD_L)
			ft_open(holder->value, &pipe, 3);
		else
			pipe = ft_input(holder->value);
		if (left_red->next && (pipe != 0))
			close(pipe);
		left_red = left_red->next;
	}
	if (pipe != 0)
		ft_dup2(pipe, 0);
	return (pipe);
}

void	ft_dup2(int x, int y)
{
	if (dup2(x, y) == -1)
		ft_error(1, "dup2 ");
}

int	redirect_output(t_list *right_red, int pipe)
{
	t_token	*holder;

	while (right_red)
	{
		holder = (t_token *)right_red->content;
		if (!holder)
			return (pipe);
		if (holder->type == TYPE_RD_R)
			ft_open(holder->value, &pipe, -1);
		else
			ft_open(holder->value, &pipe, -2);
		if (right_red->next && (pipe != 1))
			close(pipe);
		right_red = right_red->next;
	}
	if (pipe != 1)
		ft_dup2(pipe, 1);
	return (pipe);
}
