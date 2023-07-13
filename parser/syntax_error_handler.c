/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:30:06 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/13 13:22:53 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_valid_syntax(t_list *token_lst)
{
    token_t *token;
    while(token_lst != NULL)
    {
        token = (token_t *)token_lst->content;
        
        token_lst = token_lst->next;
    }
}