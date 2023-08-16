/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:29:17 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/16 13:08:34 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(int erno, const char *msg)
{
	error_write(msg);
	error_write(strerror(erno));
	error_write("\n");
	ft_exit(errno);
}

void	ft_open(char *str, int *fd, int flag)
{
	struct stat	buf;

	if ((flag == -3) && access(str, F_OK))
		print_error(1, 3, "minishell: ", str, ": No such file or directory\n");
	lstat(str, &buf);
	if (S_ISDIR(buf.st_mode))
		print_error(1, 3, "minishell: ", str, ": Is a directory\n");
	if ((flag == -1 || flag == -2) 
		&& !access(str, F_OK) && access(str, W_OK))
		print_error(1, 3, "minishell: ", str, ": Permission denied\n");
	else if (!(flag == -1 || flag == -2) 
		&& !access(str, F_OK) && access(str, R_OK))
		print_error(1, 3, "minishell: ", str, ": Permission denied\n");
	if (flag == -1)
		*fd = open(str, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (flag == -2)
		*fd = open(str, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else if (flag == -3)
		*fd = open(str, O_RDONLY);
	else if (flag == -4)
		*fd = open(str, O_RDWR | O_TRUNC | O_CREAT, 0666);
	else
		*fd = open(str, O_RDONLY);
}

char	*generate_name(void)
{
	static int		i;
	char			*str;

	if (i == 0)
		i = 554;
	str = ft_itoa(i);
	if (!str)
		ft_error(ENOMEM, "malloc: ");
	while (access(str, F_OK) == 0 && i > 0)
	{
		free(str);
		i++;
		str = ft_itoa(i);
		if (!str)
			ft_error(ENOMEM, "malloc: ");
	}
	if (i < 0 || access(str, F_OK) == 0)
		return (free(str), NULL);
	return (str);
}

int	ft_strrcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s1[i] != s2[i])
		return (1);
	return (0);
}


void	controlec2(int c)
{
	(void ) c;
	kill(0, SIGUSR2);
	exit(0);
}

int	ft_input(char *stop, enum e_tokentype type)
{
	int		fd;
	char	*str;
	int		tmp;

	signal(SIGINT, controlec2);
	str = generate_name();
	if (!str)
		ft_error(1, "here_doc: ");
	ft_open(str, &fd, -4);
	ft_open(str, &tmp, -4);
	unlink(str);
	free(str);
	while (1)
	{
		str = readline("> ");
		if (!str || !ft_strrcmp(stop, str))
			break ;
		if (type == TYPE_HERE_DOC)
			str = expand_heredoc_line(str);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	if (!str)
		printf("\x1b[F> ");
	signal(SIGINT, SIG_DFL);
	return (kill(0, SIGUSR1), free(str), str = NULL, close(fd), tmp);
}
