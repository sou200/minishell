/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 01:28:49 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/17 11:46:23 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "dirent.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
DIR *dp = opendir("");
struct dirent *d;
while ((d = readdir(dp)) != NULL) {
	// if (DT_LNK == d->d_type)
		printf("%d %s %hhu\n", (int) d->d_ino, d->d_name, d->d_type);
}
closedir(dp);
return 0;
}