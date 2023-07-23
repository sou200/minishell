/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:30:06 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/23 01:10:36 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_valid_pipe(t_list *token_lst)
{
    if(token_lst->prev == NULL || token_lst->next == NULL)
        return 0;
   return ((token_t *)token_lst->next->content)->type != TYPE_PIPE;
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

int is_valid_syntax(t_list *token_lst)
{
    token_t *token;
    int q_type;
    t_list *token_spc;

    q_type = 0;
    token_spc = tokens_without_spc(token_lst);
    token_lst = token_spc;
    while(token_lst != NULL)
    {
        token = (token_t *)token_lst->content;
        if(token->type == TYPE_QUOTE || token->type == TYPE_D_QUOTE)
            check_quote(&q_type, token->type);
        else if(token->type == TYPE_PIPE && !is_valid_pipe(token_lst) && !q_type)
            return ft_lstclear(&token_spc, ft_free_token), 0;
        else if((token->type == TYPE_RD_L || token->type == TYPE_RD_R || token->type == TYPE_APPEND || token->type == TYPE_HERE_DOC) && !is_valid_redi(token_lst) && !q_type)
            return ft_lstclear(&token_spc, ft_free_token), 0;
        token_lst = token_lst->next;
    }
    return ft_lstclear(&token_spc, ft_free_token), !q_type;
}