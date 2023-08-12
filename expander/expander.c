/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:50:04 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/12 19:45:49 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_var(char **env, char *var)
{
	size_t	i;

	i = env_name_len(var);
	if (ft_strlen(*env) <= i)
		return (NULL);
	while (*env != NULL)
	{
		if (ft_strlen(*env) > i && !ft_strncmp(*env, var, i)
			&& (*env)[i] == '=')
			return (ft_substr(*env, i + 1, ft_strlen(*env) - i));
		env++;
	}
	return (NULL);
}

void	insert_env_in_token_lst(char *env_val, char *env_word, t_list **tokens,
		t_list *tmp_token)
{
	t_list	*var_lexer;
	char	*rest_word;
	int		word_len;
	int		env_len;

	rest_word = NULL;
	env_len = env_name_len(env_word);
	word_len = ft_strlen(env_word);
	if (word_len - env_len > 0)
		rest_word = ft_substr(env_word, env_len, word_len - env_len);
	var_lexer = env_lexer(env_val);
	var_lexer->prev = *tokens;
	ft_lstdelone((*tokens)->next, ft_free_token);
	(*tokens)->next = var_lexer;
	if (rest_word != NULL)
		ft_lstadd_back(tokens, ft_lstnew(create_token(TYPE_WORD, rest_word)));
	ft_lstadd_back(tokens, tmp_token);
}

void	smpl_env(char *env_val, char *env_word, t_list *tokens)
{
	t_list	*var_lexer;
	char	*rest_word;
	char	*result;
	int		word_len;
	int		env_len;

	rest_word = NULL;
	env_len = env_name_len(env_word);
	word_len = ft_strlen(env_word);
	if (word_len - env_len > 0)
		rest_word = ft_substr(env_word, env_len, word_len - env_len);
	result = ft_strjoin(env_val, rest_word);
	((token_t *)tokens->next->content)->type = TYPE_P_WORD;
	((token_t *)tokens->next->content)->value = result;
}

void	expand_env(t_list **tokens, char **env, int lex_flag)
{
	t_list	*tmp_token;
	char	*env_word;
	char	*env_val;

	if (((token_t *)(*tokens)->next->content)->type == TYPE_QUOTE
		|| ((token_t *)(*tokens)->next->content)->type == TYPE_D_QUOTE)
		return ;
	tmp_token = (*tokens)->next->next;
	env_word = ((token_t *)(*tokens)->next->content)->value;
	if (*env_word == '?')
		env_val = ft_itoa(global.exit_status);
	else
		env_val = get_env_var(env, env_word);
	if (lex_flag)
		insert_env_in_token_lst(env_val, env_word, tokens, tmp_token);
	else
		smpl_env(env_val, env_word, *tokens);
	free(env_val);
}
