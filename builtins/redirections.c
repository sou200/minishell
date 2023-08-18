/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 01:00:58 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/18 12:06:10 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_input(t_list *left_red, int pipe)
{
	t_token	*holder;

	holder = (t_token *)left_red->content;
	if (!holder)
		return (pipe);
	if (!holder->value || (ft_strchr(holder->value, ' ')
			&& holder->is_pseudo == 1))
		print_error(1, 2, "minishell: ", ": ambiguous redirect\n");
	if (!holder->value[0] && holder->type == TYPE_RD_L)
		print_error(1, 3, "minishell: ",
			holder->value, ": No such file or directory\n");
	if (holder->type == TYPE_RD_L)
		ft_open(holder->value, &pipe, -3);
	else
		pipe = ft_input(holder->value, holder->type, 0, 0);
	return (pipe);
}

void	redirection(t_prototype *cmd, int *infile
	, int *outfile, t_token *holder)
{
	while (cmd->redire)
	{
		holder = (t_token *)cmd->redire->content;
		if (!holder)
			return ;
		if (cmd->left_red && cmd->left_red->content
			&& holder->type == ((t_token *)(cmd->left_red)->content)->type)
		{
			*infile = redirect_input(cmd->left_red,*infile);
			if (cmd->left_red->next && (*infile != 0))
				close(*infile);
			cmd->left_red = cmd->left_red->next;
		}
		else
		{
			*outfile = redirect_output(cmd->right_red,*outfile);
			if (cmd->right_red->next && (*outfile != 1))
				close(*outfile);
			cmd->right_red = cmd->right_red->next;
		}
		cmd->redire = cmd->redire->next;
	}
	if (*outfile != 1)
		dup2(*outfile, 1);
}

int	redirect_output(t_list *right_red, int pipe)
{
	t_token	*holder;

	holder = (t_token *)right_red->content;
	if (!holder)
		return (pipe);
	if (!holder->value || (ft_strchr(holder->value, ' ')
			&& holder->is_pseudo == 1))
		print_error(1, 2, "minishell: ", ": ambiguous redirect\n");
	if (!holder->value[0])
		print_error(1, 3, "minishell: ",
			holder->value, ": No such file or directory\n");
	if (holder->type == TYPE_RD_R)
		ft_open(holder->value, &pipe, -1);
	else
		ft_open(holder->value, &pipe, -2);
	return (pipe);
}
