/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 01:32:34 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/25 20:50:49 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_here_doc_expnd(t_list *tokens, int open_q)
{
	if (open_q == 1)
		while (tokens != NULL
			&& ((t_token *)tokens->content)->type != TYPE_QUOTE)
			tokens = tokens->prev;
	else if (open_q == 2)
		while (tokens != NULL
			&& ((t_token *)tokens->content)->type != TYPE_D_QUOTE)
			tokens = tokens->prev;
	tokens = tokens->prev;
	while (tokens != NULL && ((t_token *)tokens->content)->type == TYPE_SPC)
		tokens = tokens->prev;
	return (tokens != NULL
		&& ((t_token *)tokens->content)->type == TYPE_HERE_DOC);
}

int	env_name_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '\0' && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	return (i);
}

t_list	*env_lexer(char *env)
{
	if (env == NULL)
		return (ft_lstnew(create_token(TYPE_WORD, NULL)));
	return (lexer(env));
}

int	is_valid_env(t_list *tokens, int open_q)
{
	t_token	*token;
    if (tokens->next == NULL || open_q == 1)
        return (0);
    if (check_here_doc_expnd(tokens, open_q))
        return 0;
    token = (t_token *)tokens->next->content;
    if (token->type == TYPE_WORD && (ft_isalpha(*token->value) || *token->value == '_'))
        return 1;
    return (token->type == TYPE_QUOTE || token->type == TYPE_D_QUOTE) && open_q == 0;
}