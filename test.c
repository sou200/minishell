/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 01:28:49 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/25 20:39:48 by fel-hazz         ###   ########.fr       */
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
	// struct passwd *e;
	// printf("%s eee\n",getenv("SHLVL"));
	// e = getpwuid(atoi(getenv("UID")));
	// printf("%s\n",e->pw_dir);
	int fd[2];
	pipe(fd);
	int pid = fork();
	if (pid == 0)
	{
		char s[2];
		// s[1] = '\0';
		// sleep(2);
		// close(fd[1]);
		printf("write = %zd\n",write(fd[1],"e",1));
		printf("read = %zd\n",read(fd[1],s,1));
		printf("write = %zd\n",write(fd[0],"e",1));
		printf("read = %zd\n",read(fd[0],s,1));
		perror("");
		printf("%s\n",s);
	}
	else
	{
		close(fd[1]);
		close(fd[0]);
		// write(fd[1],"a",1);
		waitpid(pid,0,0);
	}
}