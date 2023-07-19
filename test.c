/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 01:28:49 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/19 17:25:01 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "dirent.h"
#include <stdio.h>

#include<stdio.h>
#include<errno.h>
#include<sys/stat.h>
#include "minishell.h"
static char *getcwd_logical(void);
void usage(void);

int
main(int argc, char *argv[])
{
	// 4207130
//    p = getcwd_logical();
//    printf("%s\n",p);
//    p = getcwd(NULL,0);
//    printf("%s\n");
	if (((p = getcwd_logical()) != NULL) ||
	    ((errno == ENOENT) && (p = getcwd(NULL, 0)) != NULL))
		printf("%s\n", p);
	exit(0);
}

static char *
getcwd_logical(void)
{
	struct stat lg, phy;
	char *pwd;

	if ((pwd = getenv("PWD")) != NULL && *pwd == '/') {
		if (stat(pwd, &lg) == -1 || stat(".", &phy) == -1)
			return (NULL);
		if (lg.st_dev == phy.st_dev && lg.st_ino == phy.st_ino)
			return (pwd);
	}

	errno = ENOENT;
	return (NULL);
}