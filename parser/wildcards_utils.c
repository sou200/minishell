/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:28:34 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/12 19:37:19 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_lst_to_string(t_list *list)
{
	char	*result;

	result = NULL;
	while (list != NULL)
	{
		result = ft_strjoin_free(result,
				((token_t *)list->content)->value, 1, 0);
		list = list->next;
	}
	return (result);
}

int	is_lexable_wild(t_list *tokens)
{
	tokens = tokens->prev;
	while (tokens != NULL && ((token_t *)tokens->content)->type == TYPE_SPC)
		tokens = tokens->prev;
	return (tokens == NULL || !is_redirection((token_t *)tokens->content));
}

int	is_wildcard(t_list *tokens, int *is_lex)
{
	*is_lex = is_lexable_wild(tokens);
	while (tokens != NULL)
	{
		if (((token_t *)tokens->content)->type == TYPE_SPC)
			return (0);
		if (((token_t *)tokens->content)->type == TYPE_STAR)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

void	yes_it_is_wild(t_list **new_token_list, t_list **tokens, int is_lex)
{
	t_list	*files_lst;
	char	*pattern;
	int		*flags;
	char	*files;

	pattern = get_pattern(tokens, &flags);
	files_lst = get_matched_files(pattern, flags);
	if (files_lst == NULL)
		ft_lstadd_back(new_token_list, ft_lstnew(create_token(TYPE_WORD,
					ft_strdup(pattern))));
	else if (is_lex)
		ft_lstadd_back(new_token_list, files_lst);
	else
	{
		files = join_lst_to_string(files_lst);
		ft_lstadd_back(new_token_list, ft_lstnew(create_token(TYPE_P_WORD,
					files)));
	}
	free(flags);
	free(pattern);
}

t_list	*wildcard_it(t_list *tokens)
{
	t_list	*new_token_list;
	int		is_lex;

	new_token_list = NULL;
	while (tokens != NULL)
	{
		if (is_wildcard(tokens, &is_lex))
			yes_it_is_wild(&new_token_list, &tokens, is_lex);
		while (tokens != NULL)
		{
			ft_lstadd_back(&new_token_list,
				token_lst_dup((token_t *)tokens->content));
			if (((token_t *)tokens->content)->type == TYPE_SPC)
			{
				tokens = tokens->next;
				break ;
			}
			tokens = tokens->next;
		}
	}
	return (new_token_list);
}
