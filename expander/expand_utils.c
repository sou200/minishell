/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 01:32:34 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/12 19:46:33 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*skip_to_get_heredoc(t_list *tokens)
{
	int	open_q;

	open_q = 0;
	while (tokens != NULL)
	{
		if (((token_t *)tokens->content)->type == TYPE_SPC && !open_q)
			break ;
		else if (((token_t *)tokens->content)->type == TYPE_QUOTE
			|| ((token_t *)tokens->content)->type == TYPE_D_QUOTE)
			check_quote(&open_q, ((token_t *)tokens->content)->type);
		tokens = tokens->prev;
	}
	return (tokens);
}

int	check_here_doc_expnd(t_list *tokens, int open_q)
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
	tokens = skip_to_get_heredoc(tokens);
	while (tokens != NULL && ((token_t *)tokens->content)->type == TYPE_SPC)
		tokens = tokens->prev;
	return (tokens != NULL
		&& ((token_t *)tokens->content)->type == TYPE_HERE_DOC);
}

int	env_name_len(char *var)
{
	int	i;

	i = 0;
	if (*var == '?')
		return (1);
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
	token_t	*token;

	if (tokens->next == NULL || open_q == 1)
		return (0);
	token = (token_t *)tokens->next->content;
	if ((token->type == TYPE_QUOTE || token->type == TYPE_D_QUOTE)
		&& open_q == 0)
		return (1);
	if (check_here_doc_expnd(tokens, open_q))
		return (0);
	return (token->type == TYPE_WORD && (ft_isalpha(*token->value)
			|| *token->value == '_' || *token->value == '?'));
}
