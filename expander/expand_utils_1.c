/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:07:59 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/19 21:03:35 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	costum_env_expand(t_list **tokens, t_list **new_tokens,char **content, int q_open)
{
	if (is_lexable(*tokens, q_open))
	{
		ft_lstadd_back(new_tokens, ft_lstnew(create_token(TYPE_WORD, *content)));
		*content = NULL;
		expand_env(tokens, new_tokens, 1);
	}
	else
		expand_env(tokens, new_tokens, 0);
}

int	abdellah_and_hakim(t_list *tokens)
{
	tokens = tokens->next;
	if (tokens != NULL && ((t_token *)tokens->content)->type == TYPE_SPC)
		tokens = tokens->next;
	while (tokens != NULL && (((t_token *)tokens->content)->type == TYPE_WORD
			|| ((t_token *)tokens->content)->type == TYPE_DOLLAR))
		tokens = tokens->next;
	if (tokens != NULL && (((t_token *)tokens->content)->type == TYPE_QUOTE
			|| ((t_token *)tokens->content)->type == TYPE_D_QUOTE))
		return (1);
	return (0);
}

void	f(t_list **new_token_lst, t_list *tokens)
{
	if (((t_token *)tokens->content)->type == TYPE_HERE_DOC
		&& abdellah_and_hakim(tokens))
		ft_lstadd_back(new_token_lst, ft_lstnew(create_token(TYPE_HERE_DOC_NX,
					ft_strdup(((t_token *)tokens->content)->value))));
	else
		ft_lstadd_back(new_token_lst,
			token_lst_dup((t_token *)tokens->content));
}

// char	*expand_heredoc_line(char *line)
// {
// 	t_helper	a;

// 	a.i = 0;
// 	while (line[a.i] != '\0')
// 	{
// 		if (line[a.i] == '$' && is_valid_to_expand(line, a.i))
// 		{
// 			a.before = ft_substr(line, 0, a.i++);
// 			a.env_n_l = env_name_len(line + a.i);
// 			a.after = ft_substr(line, a.env_n_l + a.i, ft_strlen(line) - a.i - a.env_n_l);
// 			a.env_val = get_env_var(line + a.i);
// 			a.result = ft_strjoin_free(a.before, a.env_val, 1, 1);
// 			a.result = ft_strjoin_free(a.result, a.after, 1, 1);
// 			a.i += a.env_n_l;
// 			printf("%d\n", a.i);
// 			free(line);
// 			line = a.result;
// 		}
// 		a.i++;
// 	}
// 	return (line);
// }

int ft_count(char *line)
{
	int i;

	i = 0;
	while(line[i] != '\0' && line[i] != '$')
		i++;
	return i;
}

char	*expand_heredoc_line(char *line)
{
	t_helper	a;

	a.i = 0;
	a.result = NULL;
	while (line[a.i] != '\0')
	{
		if (line[a.i] == '$' && is_valid_to_expand(line, a.i))
		{
			a.env_val = get_env_var(line + ++a.i);
			a.env_n_l = env_name_len(line + a.i);
			a.result = ft_strjoin_free(a.result, a.env_val, 1, 1);
			a.i += a.env_n_l;
		} else if(line[a.i] == '$')
			a.result = ft_strjoin_free(a.result, ft_strdup("$"), 1, 1) + ++a.i * 0;
		else {
			char *s = ft_substr(line + a.i, 0, ft_count(line + a.i));
			a.result = ft_strjoin_free(a.result, s, 1, 1);
			a.i += ft_count(line + a.i);
		}
	}
	return (a.result);
}

int	is_valid_to_expand(char *s, int i)
{
	if (s[i + 1] != '\0' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_'))
		return (1);
	return (0);
}
