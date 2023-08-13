/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:07:59 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/12 19:46:47 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	costum_env_expand(t_list **tokens, char **env, int q_open)
{
	if (is_lexable(*tokens, q_open))
		expand_env(tokens, env, 1);
	else
		expand_env(tokens, env, 0);
}

int	abdellah_and_hakim(t_list *tokens)
{
	tokens = tokens->next;
	if (tokens != NULL && ((token_t *)tokens->content)->type == TYPE_SPC)
		tokens = tokens->next;
	while (tokens != NULL && (((token_t *)tokens->content)->type == TYPE_WORD
			|| ((token_t *)tokens->content)->type == TYPE_DOLLAR))
		tokens = tokens->next;
	if (tokens != NULL && (((token_t *)tokens->content)->type == TYPE_QUOTE
			|| ((token_t *)tokens->content)->type == TYPE_D_QUOTE))
		return (1);
	return (0);
}

void	f(t_list **new_token_lst, t_list *tokens)
{
	if (((token_t *)tokens->content)->type == TYPE_HERE_DOC
		&& abdellah_and_hakim(tokens))
		ft_lstadd_back(new_token_lst, ft_lstnew(create_token(TYPE_HERE_DOC_NX,
					ft_strdup(((token_t *)tokens->content)->value))));
	else
		ft_lstadd_back(new_token_lst,
			token_lst_dup((token_t *)tokens->content));
}
