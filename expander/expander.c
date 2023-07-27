/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:50:04 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/27 16:46:38 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_env_var(char **env, char *var)
{
    size_t i;

    i = env_name_len(var);
    if(ft_strlen(*env) <= i)
        return NULL;
    while (*env != NULL)
    {
        if(ft_strlen(*env) > i && !ft_strncmp(*env, var, i) && (*env)[i] == '=')
            return ft_substr(*env, i + 1, ft_strlen(*env) - i);
        env++;
    }
    return NULL;
}

void insert_env_in_token_lst(char *env_val, char *env_word, t_list **tokens, t_list *tmp_token)
{
    t_list *var_lexer;
    char *rest_word;
    int word_len;
    int env_len;

    rest_word = NULL;
    env_len = env_name_len(env_word);
    word_len = ft_strlen(env_word);
    if(word_len - env_len > 0)
        rest_word = ft_substr(env_word, env_len, word_len - env_len);
    var_lexer = env_lexer(env_val);
    var_lexer->prev = *tokens;
    ft_lstdelone((*tokens)->next, ft_free_token);
    (*tokens)->next = var_lexer;
    if(rest_word != NULL)
        ft_lstadd_back(tokens, ft_lstnew(create_token(TYPE_WORD, rest_word)));
    ft_lstadd_back(tokens, tmp_token);
}

int is_valid_to_expand(char *s, int i)
{
	if(s[i + 1] != '\0' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_'))
        return 1;
    return 0;
}

char * expand_heredoc_line(char *line, char **env)
{
	int i;
    int env_name_l;
    char *env_val;
    char *result;
    char *before;
    char *after;

	i = 0;
	while(line[i] != '\0')
	{
		if(line[i] == '$' && is_valid_to_expand(line, i))
		{
            before = ft_substr(line, 0, i++);
            env_name_l = env_name_len(line + i);
            after = ft_substr(line, env_name_l + i, ft_strlen(line) - i - env_name_l);
			env_val = get_env_var(env, line + i);
            result = ft_strjoin_free(before, env_val, 1, 1);
            result = ft_strjoin_free(result, after, 1, 1);
            i += env_name_l;
            free(line);
            line = result;
		}
        i++;
	}
    return line;
}

void expand_env(t_list **tokens, char **env)
{
    t_list *tmp_token;
    char *env_word;
    char *env_val;
    if(((t_token *)(*tokens)->next->content)->type == TYPE_QUOTE || ((t_token *)(*tokens)->next->content)->type == TYPE_D_QUOTE)
        return ;
    tmp_token = (*tokens)->next->next;
    env_word = ((t_token *)(*tokens)->next->content)->value;
    env_val = get_env_var(env, env_word);
    insert_env_in_token_lst(env_val, env_word, tokens, tmp_token);
    free(env_val);
}