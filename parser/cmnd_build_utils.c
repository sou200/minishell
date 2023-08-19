/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnd_build_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:19:32 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/19 22:21:42 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmnd_arg_count(t_list *tokens)
{
	int	count;

	count = 0;
	while (tokens != NULL && ((t_token *)tokens->content)->type != TYPE_PIPE)
	{
		if (is_redirection((t_token *)tokens->content))
			tokens = tokens->next;
		else if (((t_token *)tokens->content)->value != NULL)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

void	add_smpl_cmnd(t_list **cmnd_lst, t_cmd_helper *c)
{
	t_prototype	*smpl_cmnd;

	smpl_cmnd = malloc(sizeof(t_prototype));
	smpl_cmnd->cmnd = c->cmnds;
	smpl_cmnd->left_red = c->left_red;
	smpl_cmnd->right_red = c->right_red;
	smpl_cmnd->redire = c->redire;
	ft_lstadd_back(cmnd_lst, ft_lstnew(smpl_cmnd));
}

void	*create_rd(enum e_tokentype type, void *content, int p)
{
	t_token	*rd;

	rd = malloc(sizeof(t_token));
	if (!rd)
		ft_exit(ENOMEM);
	rd->type = type;
	rd->value = ft_strdup((char *)content);
	rd->is_pseudo = p;
	return (rd);
}

void	add_red(t_list **tokens, t_token *token, t_cmd_helper *c)
{
	char	*red_name;

	red_name = ((t_token *)(*tokens)->next->content)->value;
	ft_lstadd_back(&c->redire, ft_lstnew(create_rd(token->type, red_name,
				((t_token *)(*tokens)->next->content)->type == TYPE_P_WORD)));
	if (token->type == TYPE_RD_L || token->type == TYPE_HERE_DOC
		|| token->type == TYPE_HERE_DOC_NX)
		ft_lstadd_back(&c->left_red, ft_lstnew(create_rd(token->type, red_name,
					((t_token *)(*tokens)->next->content)->type
					== TYPE_P_WORD)));
	else
		ft_lstadd_back(&c->right_red, ft_lstnew(create_rd(token->type, red_name,
					((t_token *)(*tokens)->next->content)->type
					== TYPE_P_WORD)));
	*tokens = (*tokens)->next;
}

void	build_smpl_cmnd(t_list **tokens, t_list **smpl_cmnds)
{
	t_token			*token;
	t_cmd_helper	c;

	ft_memset(&c, 0, sizeof(t_cmd_helper));
	c.cmnds = malloc((cmnd_arg_count(*tokens) + 1) * sizeof(char *));
	while (*tokens != NULL
		&& ((t_token *)(*tokens)->content)->type != TYPE_PIPE)
	{
		token = (t_token *)(*tokens)->content;
		if (is_redirection(token))
			add_red(tokens, token, &c);
		else if (token->value != NULL)
			c.cmnds[c.cmd_index++] = ft_strdup(token->value);
		*tokens = (*tokens)->next;
	}
	c.cmnds[c.cmd_index] = NULL;
	add_smpl_cmnd(smpl_cmnds, &c);
}
