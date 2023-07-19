/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:43:01 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/16 17:23:51 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void parce_line(t_list *token_lst)
{
    t_token *token;
    while(token_lst != NULL)
    {
        token = (t_token *)token_lst->content;
        if(token->type == TYPE_RD_L || token->type == TYPE_RD_R)
        {
            token = (t_token *)token_lst->content;
            token_lst = token_lst->next;
            if(!token && token->type == TYPE_WORD)
                printf("%s", token->value);
            else if()
        }
        token_lst = token_lst->next;
    }
}