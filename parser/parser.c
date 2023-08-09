/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:43:01 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/08 01:06:04 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_redirection(token_t *token)
{
    return token->type == TYPE_HERE_DOC || token->type == TYPE_APPEND || token->type == TYPE_RD_L || token->type == TYPE_RD_R || token->type == TYPE_HERE_DOC_NX;
}

int is_lexable(t_list *tokens, int open_q)
{
    if (open_q == 1)
        while (tokens != NULL && ((token_t *)tokens->content)->type != TYPE_QUOTE)
            tokens = tokens->prev;
    else if (open_q == 2)
        while (tokens != NULL && ((token_t *)tokens->content)->type != TYPE_D_QUOTE)
            tokens = tokens->prev;
    tokens = tokens->prev;
    while (tokens != NULL && ((token_t *)tokens->content)->type == TYPE_SPC)
        tokens = tokens->prev;
    return (tokens == NULL || !is_redirection((token_t *)tokens->content));
}

void costum_env_expand(t_list **tokens, char **env, int q_open)
{
    if (is_lexable(*tokens, q_open))
        expand_env(tokens, env, 1);
    else
        expand_env(tokens, env, 0);
}

t_list *wildcard_it(t_list *tokens)
{
    t_list *new_token_list;
    int is_lex;

    new_token_list = NULL;
    while (tokens != NULL)
    {
        if (is_wildcard(tokens, &is_lex))
            yes_it_is_wild(&new_token_list, &tokens, is_lex);
        while (tokens != NULL)
        {
            ft_lstadd_back(&new_token_list, token_lst_dup((token_t *)tokens->content));
            if (((token_t *)tokens->content)->type == TYPE_SPC)
            {
                tokens = tokens->next;
                break;
            }
            tokens = tokens->next;
        }
    }
    return new_token_list;
}

int abdellah_and_hakim(t_list *tokens)
{
    tokens = tokens->next;
    if(tokens != NULL && ((token_t *)tokens->content)->type == TYPE_SPC)
        tokens = tokens->next;
    while(tokens != NULL && ((token_t *)tokens->content)->type == TYPE_WORD)
        tokens = tokens->next;
    if(tokens != NULL && (((token_t *)tokens->content)->type == TYPE_QUOTE || ((token_t *)tokens->content)->type == TYPE_D_QUOTE))
        return 1;
    return 0;
}
// << 'a' << "b" << c
void f(t_list **new_token_lst, t_list *tokens)
{
    if(((token_t *)tokens->content)->type == TYPE_HERE_DOC && abdellah_and_hakim(tokens))
        ft_lstadd_back(new_token_lst, ft_lstnew(create_token(TYPE_HERE_DOC_NX, ft_strdup(((token_t *)tokens->content)->value))));
    else
        ft_lstadd_back(new_token_lst, token_lst_dup((token_t *)tokens->content));
}

t_list *to_expanded_tokens(t_list *tokens, char **env)
{
    int open_q;
    t_list *new_token_lst;
    char *quote_content;

    open_q = 0;
    new_token_lst = NULL;
    quote_content = NULL;
    while (tokens != NULL)
    {
        if (((token_t *)tokens->content)->type == TYPE_QUOTE && open_q != 2)
            in_quote_handler(&open_q, &quote_content, &new_token_lst, 1);
        else if (((token_t *)tokens->content)->type == TYPE_D_QUOTE && open_q != 1)
            in_quote_handler(&open_q, &quote_content, &new_token_lst, 2);
        else if (((token_t *)tokens->content)->type == TYPE_DOLLAR && is_valid_env(tokens, open_q))
            costum_env_expand(&tokens, env, open_q);
        else if (open_q)
            quote_content = ft_strjoin_free(quote_content, ((token_t *)tokens->content)->value, 1, 0);
        else
            f(&new_token_lst, tokens);
            // ft_lstadd_back(&new_token_lst, token_lst_dup((token_t *)tokens->content));
        tokens = tokens->next;
    }
    return new_token_lst;
}

int is_valid_to_join(t_list *tokens, int *is_pseudo)
{
    token_t *token;

    token = (token_t *)tokens->content;
    if (token->type == TYPE_WORD)
        return 1;
    if (token->type == TYPE_DOLLAR)
        return 1;
    if(token->type == TYPE_P_WORD)
    {
        *is_pseudo = 1;
        return 1;
    }
    return 0;
}

// t_list *join_and_clean_tokens(t_list *tokens)
// {
//     t_list *new_tokens;
//     token_t *token;
//     char *joined;
//     int is_pseudo;

//     is_pseudo = 0;
//     new_tokens = NULL;
//     joined = NULL;
//     while (tokens != NULL)
//     {
//         token = (token_t *)tokens->content;
//         if (is_valid_to_join(tokens, &is_pseudo))
//             joined = ft_strjoin_free(joined, token->value, 1, 0);
//         else
//         {
//             if (joined != NULL)
//                 ft_lstadd_back(&new_tokens, ft_lstnew(create_token(is_pseudo?TYPE_P_WORD:TYPE_WORD, joined)));
//             joined = NULL;
//             is_pseudo = 0;
//             if (token->type != TYPE_SPC)
//                 ft_lstadd_back(&new_tokens, token_lst_dup(token));
//         }
//         tokens = tokens->next;
//     }
//     if (joined != NULL)
//         ft_lstadd_back(&new_tokens, ft_lstnew(create_token(is_pseudo?TYPE_P_WORD:TYPE_WORD, joined)));
//     return new_tokens;
// }

t_list *join_and_clean_tokens(t_list *tokens)
{
    t_list *new_tokens;
    token_t *token;
    char *joined;
    int j_flag;
    int is_pseudo;

    is_pseudo = 0;

    new_tokens = NULL;
    joined = NULL;
    j_flag = 0;
    while (tokens != NULL)
    {
        token = (token_t *)tokens->content;
        if (is_valid_to_join(tokens, &is_pseudo))
            joined = ft_strjoin_free(joined, token->value, 1, 0) + 0 * j_flag++;
        else if (token->type != TYPE_WORD)
        {
            if (j_flag)
                ft_lstadd_back(&new_tokens, ft_lstnew(create_token(is_pseudo?TYPE_P_WORD:TYPE_WORD, joined)));
            joined = NULL;
            j_flag = 0;
            if (token->type != TYPE_SPC)
                ft_lstadd_back(&new_tokens, token_lst_dup(token));
        }
        tokens = tokens->next;
    }
    if (j_flag)
        ft_lstadd_back(&new_tokens, ft_lstnew(create_token(is_pseudo?TYPE_P_WORD:TYPE_WORD, joined)));
    return new_tokens;
}

t_list *parce_line(char *line, char **env)
{
    t_list *tokens;
    t_list *expanded_tokens;
    t_list *wildcarded_tokens;
    t_list *final_tokens;
    t_list *smpl_cmnds;

    tokens = lexer(line);
    if (!is_valid_syntax(tokens))
        return printf("syntax error !\n"), NULL;
    expanded_tokens = to_expanded_tokens(tokens, env);
    wildcarded_tokens = wildcard_it(expanded_tokens);
    final_tokens = join_and_clean_tokens(wildcarded_tokens);
    smpl_cmnds = generate_cmnds(final_tokens);
    // ft_lstclear(&tokens, ft_free_token);
    // ft_lstclear(&expanded_tokens, ft_free_token);
    // ft_lstclear(&wildcarded_tokens, ft_free_token);
    // ft_lstclear(&final_tokens, ft_free_token);
    return smpl_cmnds;
}