/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:13:34 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/17 10:35:04 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredocsigs(t_list *cmd, t_var *p, int save, t_list *j)
{
	t_token	*ho;

	j = (t_list *)(((t_prototype *)(cmd->content))->left_red);
	if (p->y == 1)
	{
		save = gl.return_value;
		gl.return_value = 0;
		signal(SIGUSR1, holder);
		signal(SIGUSR2, holder1);
		while (gl.return_value != 300 && gl.return_value != 400)
			;
		signal(SIGUSR1, SIG_IGN);
		signal(SIGUSR2, SIG_IGN);
		if (gl.return_value == 400)
			return ;
		gl.return_value = save;
		p->y = 0;
	}
	while (j)
	{
		ho = (t_token *)((t_prototype *)(cmd->content))->left_red->content;
		if (ho->type == TYPE_HERE_DOC || ho->type == TYPE_HERE_DOC_NX)
			p->y = 1;
		j = j->next;
	}
}
