/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 02:26:29 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/21 02:35:04 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strjoin_free(char *a, char *b, int i, int j)
{
    char *res = ft_strjoin(a, b);
    if(i && a)
        free(a);
    if(j && b)
        free(b);
    return res;
}