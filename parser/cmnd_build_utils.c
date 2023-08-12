/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnd_build_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:19:32 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/12 23:43:03 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmnd_arg_count(t_list *tokens)
{
	int	count;

	count = 0;
	while (tokens != NULL && ((token_t *)tokens->content)->type != TYPE_PIPE)
	{
		if (is_redirection((token_t *)tokens->content))
			tokens = tokens->next;
		else if (((token_t *)tokens->content)->value != NULL)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

void	add_smpl_cmnd(t_list **cmnd_lst, char **cmnds, t_list *left_red,
		t_list *right_red)
{
	smpl_cmnd_t	*smpl_cmnd;

	smpl_cmnd = malloc(sizeof(smpl_cmnd_t));
	smpl_cmnd->cmnd = cmnds;
	smpl_cmnd->left_red = left_red;
	smpl_cmnd->right_red = right_red;
	ft_lstadd_back(cmnd_lst, ft_lstnew(smpl_cmnd));
}

void	*create_rd(enum token_type type, void *content, int p)
{
	t_rd	*rd;

	rd = malloc(sizeof(t_rd));
	if (!rd)
		exit(-1);
	rd->type = type;
	rd->value = content;
	rd->is_pseudo = p;
	return (rd);
}

void	add_red(t_list **tokens, token_t *token, t_list **left_red,
		t_list **right_red)
{
	char	*red_name;

	red_name = ft_strdup(((token_t *)(*tokens)->next->content)->value);
	if (token->type == TYPE_RD_L || token->type == TYPE_HERE_DOC
		|| token->type == TYPE_HERE_DOC_NX)
		ft_lstadd_back(left_red, ft_lstnew(create_rd(token->type, red_name,
					((token_t *)(*tokens)->next->content)->type
					== TYPE_P_WORD)));
	else
		ft_lstadd_back(right_red, ft_lstnew(create_rd(token->type, red_name,
					((token_t *)(*tokens)->next->content)->type
					== TYPE_P_WORD)));
	*tokens = (*tokens)->next;
}

void	build_smpl_cmnd(t_list **tokens, t_list **smpl_cmnds)
{
	t_list	*left_red;
	t_list	*right_red;
	token_t	*token;
	char	**cmnds;
	int		cmd_index;

	cmnds = malloc((cmnd_arg_count(*tokens) + 1) * sizeof(char *));
	cmd_index = 0;
	left_red = NULL;
	right_red = NULL;
	while (*tokens != NULL
		&& ((token_t *)(*tokens)->content)->type != TYPE_PIPE)
	{
		token = (token_t *)(*tokens)->content;
		if (is_redirection(token))
			add_red(tokens, token, &left_red, &right_red);
		else if (token->value != NULL)
			cmnds[cmd_index++] = ft_strdup(token->value);
		*tokens = (*tokens)->next;
	}
	cmnds[cmd_index] = NULL;
	add_smpl_cmnd(smpl_cmnds, cmnds, left_red, right_red);
}
