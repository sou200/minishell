/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:30:06 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/20 03:45:26 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_valid_pipe(t_list *token_lst)
{
    if(token_lst->prev == NULL || token_lst->next == NULL)
        return 0;
   return ((token_t *)token_lst->next->content)->type != TYPE_PIPE;
}

t_list *token_lst_dup(token_t *token)
{
    t_list *dup;
    token_t *new_token;

    new_token = create_token(token->type, token->value);
    dup = ft_lstnew(new_token);
    return dup;
}

int is_valid_redi(t_list *token_lst)
{
    if(token_lst->next == NULL)
        return 0;
    return ((token_t *)token_lst->next->content)->type == TYPE_WORD || ((token_t *)token_lst->next->content)->type == TYPE_DOLLAR || ((token_t *)token_lst->next->content)->type == TYPE_QUOTE || ((token_t *)token_lst->next->content)->type == TYPE_D_QUOTE;
}

void check_quote(int *q_type, enum token_type cas)
{
    if(cas == TYPE_QUOTE && *q_type != 2)
    {
        if(*q_type == 1)
            *q_type = 0;
        else
            *q_type = 1;
    } else if(cas == TYPE_D_QUOTE && *q_type != 1)
    {
        if(*q_type == 2)
            *q_type = 0;
        else
            *q_type = 2;
    }
}

t_list *tokens_without_spc(t_list *token_lst)
{
    int open_q;
    t_list* new_token_lst;

    open_q = 0;
    new_token_lst = NULL;
    while (token_lst != NULL)
    {
        if(((token_t *)token_lst->content)->type != TYPE_SPC)
            ft_lstadd_back(&new_token_lst, token_lst_dup((token_t *)token_lst->content));
        token_lst = token_lst->next;
    }
    return new_token_lst;
}

int is_valid_syntax(t_list *token_lst)
{
    token_t *token;
    int q_type;

    q_type = 0;
    token_lst = tokens_without_spc(token_lst);
    while(token_lst != NULL)
    {
        token = (token_t *)token_lst->content;
        if(token->type == TYPE_QUOTE || token->type == TYPE_D_QUOTE)
            check_quote(&q_type, token->type);
        else if(token->type == TYPE_PIPE && !is_valid_pipe(token_lst) && !q_type)
            return 0;
        else if((token->type == TYPE_RD_L || token->type == TYPE_RD_R || token->type == TYPE_APPEND || token->type == TYPE_HERE_DOC) && !is_valid_redi(token_lst) && !q_type)
            return 0;
        token_lst = token_lst->next;
    }
    return !q_type;
}