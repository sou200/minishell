/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:43:01 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/13 15:50:55 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void parce_line(t_list *token_lst)
{
    token_t *token;
    while(token_lst != NULL)
    {
        token = (token_t *)token_lst->content;
        if(token->type == TYPE_RD_L || token->type == TYPE_RD_R)
        {
            token = (token_t *)token_lst->content;
            token_lst = token_lst->next;
            if(!token && token->type == TYPE_WORD)
                printf("%s", token->value);
            else if()
        }
        token_lst = token_lst->next;
    }
}