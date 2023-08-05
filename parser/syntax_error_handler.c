/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:30:06 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/05 06:46:21 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_valid_neighbor(t_token *token)
{
    return token->type == TYPE_WORD || token->type == TYPE_DOLLAR || token->type == TYPE_QUOTE || token->type == TYPE_D_QUOTE || token->type == TYPE_STAR;
}

int is_valid_pipe(t_list *token_lst)
{
    if(token_lst->prev == NULL || token_lst->next == NULL)
        return 0;
   return ((t_token *)token_lst->next->content)->type != TYPE_PIPE;
}

int is_valid_redi(t_list *token_lst)
{
    if(token_lst->next == NULL)
        return 0;
    return is_valid_neighbor((t_token *)token_lst->next->content);
}

void check_quote(int *q_type, enum t_tokenype cas)
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
    t_token *token;
    int q_type;
    t_list *s_tokenpc;

    q_type = 0;
    s_tokenpc = tokens_without_spc(token_lst);
    token_lst = s_tokenpc;
    while(token_lst != NULL)
    {
        token = (t_token *)token_lst->content;
        if(token->type == TYPE_QUOTE || token->type == TYPE_D_QUOTE)
            check_quote(&q_type, token->type);
        else if(token->type == TYPE_PIPE && !is_valid_pipe(token_lst) && !q_type)
            return ft_lstclear(&s_tokenpc, ft_free_token), 0;
        else if((token->type == TYPE_RD_L || token->type == TYPE_RD_R || token->type == TYPE_APPEND || token->type == TYPE_HERE_DOC) && !is_valid_redi(token_lst) && !q_type)
            return ft_lstclear(&s_tokenpc, ft_free_token), 0;
        token_lst = token_lst->next;
    }
    return ft_lstclear(&s_tokenpc, ft_free_token), !q_type;
}