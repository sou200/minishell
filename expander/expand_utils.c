/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 01:32:34 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/19 00:35:02 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*skip_to_get_heredoc(t_list *tokens)
{
	int	open_q;

	open_q = 0;
	while (tokens != NULL)
	{
		if (((t_token *)tokens->content)->type == TYPE_SPC && !open_q)
			break ;
		else if (((t_token *)tokens->content)->type == TYPE_QUOTE
			|| ((t_token *)tokens->content)->type == TYPE_D_QUOTE)
			check_quote(&open_q, ((t_token *)tokens->content)->type);
		tokens = tokens->prev;
	}
	return (tokens);
}

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
	tokens = skip_to_get_heredoc(tokens);
	while (tokens != NULL && ((t_token *)tokens->content)->type == TYPE_SPC)
		tokens = tokens->prev;
	return (tokens != NULL
		&& ((t_token *)tokens->content)->type == TYPE_HERE_DOC);
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
	char **splited_env;
	t_list *list;
	int i;
	
	i = 0;
	list = NULL;
	if (env == NULL)
		return (ft_lstnew(create_token(TYPE_WORD, NULL)));
	splited_env = ft_split(env, ' ');
	if(splited_env == NULL)
		return NULL;
	while(splited_env[i] != NULL)
	{
		ft_lstadd_back(&list, ft_lstnew(create_token(TYPE_WORD, splited_env[i++])));
		ft_lstadd_back(&list, ft_lstnew(create_token(TYPE_SPC, ft_strdup(" "))));
	}
	return free(splited_env[i]), free(splited_env), list;
}

int	is_valid_env(t_list *tokens, int open_q)
{
	t_token	*token;

	if (tokens->next == NULL || open_q == 1)
		return (0);
	token = (t_token *)tokens->next->content;
	if ((token->type == TYPE_QUOTE || token->type == TYPE_D_QUOTE)
		&& open_q == 0)
		return (1);
	if (check_here_doc_expnd(tokens, open_q))
		return (0);
	return (token->type == TYPE_WORD && (ft_isalpha(*token->value)
			|| *token->value == '_' || *token->value == '?'));
}
