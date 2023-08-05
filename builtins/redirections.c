/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 01:00:58 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/05 05:09:15 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	redirect_input(t_list *left_red, int pipe)
{
	t_token	*holder;

	while (left_red)
	{
		holder = (t_token *)left_red->content;
		if (!holder)
			return (pipe);
		if (!holder->value)
			print_error(1, 2, "minishell: ", ": ambiguous redirect\n");//CMD NAME
		if (!holder->value[0])
			print_error(1, 3, "minishell: ",
				holder->value, ": No such file or directory\n");
		if (holder->type == TYPE_RD_L)
			ft_open(holder->value, &pipe, 3);
		else
			pipe = ft_input(holder->value);
		if (left_red->next && (pipe != 0))
			close(pipe);
		left_red = left_red->next;
	}
	if (pipe != 0)
		dup2(pipe, 0);
	return (pipe);
}

int	redirect_output(t_list *right_red, int pipe)
{
	t_token	*holder;

	while (right_red)
	{
		holder = (t_token *)right_red->content;
		if (!holder)
			return (pipe);
		if (!holder->value)
			print_error(1, 2, "minishell: ", ": ambiguous redirect\n");//CMD NAME
		if (!holder->value[0])
			print_error(1, 3, "minishell: ",
				holder->value, ": No such file or directory\n");
		if (holder->type == TYPE_RD_R)
			ft_open(holder->value, &pipe, -1);
		else
			ft_open(holder->value, &pipe, -2);
		if (right_red->next && (pipe != 1))
			close(pipe);
		right_red = right_red->next;
	}
	if (pipe != 1)
		dup2(pipe, 1);
	return (pipe);
}
