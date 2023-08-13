/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:30:57 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/12 19:38:07 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(token_t *token)
{
	return (token->type == TYPE_HERE_DOC || token->type == TYPE_APPEND
		|| token->type == TYPE_RD_L || token->type == TYPE_RD_R
		|| token->type == TYPE_HERE_DOC_NX);
}

int	is_lexable(t_list *tokens, int open_q)
{
	if (open_q == 1)
		while (tokens != NULL
			&& ((token_t *)tokens->content)->type != TYPE_QUOTE)
			tokens = tokens->prev;
	else if (open_q == 2)
		while (tokens != NULL
			&& ((token_t *)tokens->content)->type != TYPE_D_QUOTE)
			tokens = tokens->prev;
	tokens = tokens->prev;
	while (tokens != NULL && ((token_t *)tokens->content)->type == TYPE_SPC)
		tokens = tokens->prev;
	return (tokens == NULL || !is_redirection((token_t *)tokens->content));
}
