/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:40:28 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/23 01:29:20 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_free_token(void *content)
{
    token_t *token;
    token = (token_t *)content;
    if(token != NULL)
        free(token->value);
    free(token);
}