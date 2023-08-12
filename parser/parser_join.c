/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:22:53 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/12 23:26:13 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_to_join(t_list *tokens, int *is_pseudo)
{
	token_t	*token;

	token = (token_t *)tokens->content;
	if (token->type == TYPE_WORD)
		return (1);
	if (token->type == TYPE_DOLLAR)
		return (1);
	if (token->type == TYPE_P_WORD)
	{
		*is_pseudo = 1;
		return (1);
	}
	return (0);
}

enum token_type	word_or_pword(int is_pseudo)
{
	if (is_pseudo)
		return (TYPE_P_WORD);
	return (TYPE_WORD);
}

void	init_join(t_list **new_tokens, char **joined, int *j_flag,
		int *is_pseudo)
{
	*new_tokens = NULL;
	*joined = NULL;
	*j_flag = 0;
	*is_pseudo = 0;
}

void	add_joined_to_lst(char **joined, int *j_flag, t_list **new_tokens,
		int is_pseudo)
{
	if (*j_flag)
		ft_lstadd_back(new_tokens,
			ft_lstnew(create_token(word_or_pword(is_pseudo), *joined)));
	*joined = NULL;
	*j_flag = 0;
}

t_list	*join_and_clean_tokens(t_list *tokens)
{
	t_list	*new_tokens;
	token_t	*token;
	char	*joined;
	int		j_flag;
	int		is_pseudo;

	init_join(&new_tokens, &joined, &j_flag, &is_pseudo);
	while (tokens != NULL)
	{
		token = (token_t *)tokens->content;
		if (is_valid_to_join(tokens, &is_pseudo))
			joined = ft_strjoin_free(joined, token->value, 1, 0) + 0 * j_flag++;
		else if (token->type != TYPE_WORD)
		{
			add_joined_to_lst(&joined, &j_flag, &new_tokens, is_pseudo);
			if (token->type != TYPE_SPC)
				ft_lstadd_back(&new_tokens, token_lst_dup(token));
		}
		tokens = tokens->next;
	}
	if (j_flag)
		ft_lstadd_back(&new_tokens,
			ft_lstnew(create_token(word_or_pword(is_pseudo), joined)));
	return (new_tokens);
}
