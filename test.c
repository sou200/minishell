/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 01:28:49 by serhouni          #+#    #+#             */
/*   Updated: 2023/06/10 23:34:52 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// int * f()
// {
//     int *arr[] = {1,2,NULL,4};
//     return arr;
// }

// void paketa(int *a)
// {
//     printf("%d",*a);
// }
int main() {
    int i = 0;

    paketa(&(i++));
    return 0;
}

int func(int i)
{
    return i;
}