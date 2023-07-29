/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 01:28:49 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/28 23:17:38 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft/libft.h"
// #include "dirent.h"
// #include <stdio.h>

// #include<stdio.h>
// #include<errno.h>
// #include<sys/stat.h>
// #include "minishell.h"
// static char *getcwd_logical(void);
// void usage(void);

// int
// main(int argc, char *argv[])
// {
// 	// 4207130
// //    p = getcwd_logical();
// //    printf("%s\n",p);
// //    p = getcwd(NULL,0);
// //    printf("%s\n");
// 	if (((p = getcwd_logical()) != NULL) ||
// 	    ((errno == ENOENT) && (p = getcwd(NULL, 0)) != NULL))
// 		printf("%s\n", p);
// 	exit(0);
// }

// static char *
// getcwd_logical(void)
// {
// 	struct stat lg, phy;
// 	char *pwd;

// 	if ((pwd = getenv("PWD")) != NULL && *pwd == '/') {
// 		if (stat(pwd, &lg) == -1 || stat(".", &phy) == -1)
// 			return (NULL);
// 		if (lg.st_dev == phy.st_dev && lg.st_ino == phy.st_ino)
// 			return (pwd);
// 	}

// 	errno = ENOENT;
// 	return (NULL);
// }
#include<sys/types.h>
#include<pwd.h>
#include<stdlib.h>
#include <stdio.h>
#include<unistd.h>
int main()
{
// 	int fd[2];
// 	pipe(fd);
// 	printf("%d %d\n",fd[0],fd[1]);
// pipe(fd);
// 	printf("%d %d\n",fd[0],fd[1]);
// 	while(1);

	int infile ;
	int outfile ;
	int i = 0;
	int fd[2];
	pipe(fd);
	int pid;
	while (i < 2)
	{
		if (i == 0)
		{
			pid = fork();
			if (!pid)
			{
				dup2(fd[1],1);
				close(fd[1]);
				close(fd[0]);
				char *arg[2] = {"/bin/cat",0};
				execve("/bin/cat",arg,0);
			}
			// else
			// {
			// }
		}
		else if ( i == 1)
		{
			pid = fork();
			
			if (!pid)
			{
				dup2(fd[0],0);
				close(fd[1]);
				close(fd[0]);
				char *arg[2] = {"/bin/ls",0};
				execve("/bin/ls",arg,0);
			}
			// else
			// {

			// }
		}
		i++;
	}

	// close(fd[0]);
	// close(fd[1]);
	i = 0;
	while (i++ < 2)
		wait(0);
}