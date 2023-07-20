/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:50:04 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/20 03:42:42 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int env_name_len(char *var)
{
    int i;

    i = 0;
    while(var[i] != '\0' && (ft_isalnum(var[i]) || var[i] == '_'))
        i++;
    return i;
}

// int is_redirection(token_t *token)
// {
//     return token->type == TYPE_HERE_DOC || token->type == TYPE_APPEND ||token->type == TYPE_RD_L ||token->type == TYPE_RD_R;
// }

// int check_redir_expand(t_list *tokens)
// {
//     while (tokens != NULL && (((token_t*)tokens->content)->type == TYPE_WORD || ((token_t*)tokens->content)->type == TYPE_DOLLAR))
//         tokens = tokens->prev;
//     while (tokens != NULL && ((token_t*)tokens->content)->type == TYPE_SPC)
//         tokens = tokens->prev;
//     if(tokens == NULL)
//         return 0;
//     return is_redirection((token_t*)tokens->content);
// }

int check_here_doc_expnd(t_list* tokens, int open_q)
{
    if(open_q == 1)
        while(tokens != NULL && ((token_t*)tokens->content)->type != TYPE_QUOTE)
            tokens = tokens->prev;
    else if(open_q == 2)
        while(tokens != NULL && ((token_t*)tokens->content)->type != TYPE_D_QUOTE)
            tokens = tokens->prev;
    tokens = tokens->prev;
    // while(tokens != NULL && ((token_t*)tokens->content)->type != TYPE_SPC && ((token_t*)tokens->content)->type != TYPE_HERE_DOC)
    //     tokens = tokens->prev;
    while(tokens != NULL && ((token_t*)tokens->content)->type == TYPE_SPC)
        tokens = tokens->prev;
    return tokens != NULL && ((token_t*)tokens->content)->type == TYPE_HERE_DOC;
}

int is_valid_env(t_list* tokens, int open_q)
{
    token_t * token;
    if(tokens->next == NULL || open_q == 1)
        return 0;
    if(check_here_doc_expnd(tokens, open_q))
       return 0; 
    token = (token_t *)tokens->next->content;
    if(token->type == TYPE_WORD && (ft_isalpha(*token->value) || *token->value == '_'))
        return 1;
    return (token->type == TYPE_QUOTE || token->type == TYPE_D_QUOTE) && open_q == 0; 
}

char *get_env_var(char **env, char *var)
{
    int i;

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

t_list *env_lexer(char *env)
{
    if(env == NULL)
        return ft_lstnew(create_token(TYPE_WORD, NULL));
    return lexer(env);
}

void insert_env_in_token_lst(char *env_val, char *env_name, t_list **tokens, t_list *tmp_token)
{
    t_list *var_lexer;
    char *rest_word;
    int name_len;
    int env_len;
    
    name_len = env_name_len(env_name);
    env_len = ft_strlen(env_name);
    rest_word = ft_substr(env_name, name_len, env_len - name_len);
    var_lexer = env_lexer(env_val);
    var_lexer->prev = (*tokens)->next;
    (*tokens)->next = var_lexer;
    if(ft_strlen(rest_word) > 0)
        ft_lstadd_back(tokens, ft_lstnew(create_token(TYPE_WORD, rest_word)));
    ft_lstadd_back(tokens, tmp_token);
}

void expand_env(t_list **tokens, char **env)
{
    t_list *tmp_token;
    char *env_name;
    char *env_val;
    if(((token_t *)(*tokens)->next->content)->type == TYPE_QUOTE || ((token_t *)(*tokens)->next->content)->type == TYPE_D_QUOTE)
        return ;
    tmp_token = (*tokens)->next->next;
    env_name = ((token_t *)(*tokens)->next->content)->value;
    env_val = get_env_var(env, env_name);
    insert_env_in_token_lst(env_val, env_name, tokens, tmp_token);
}