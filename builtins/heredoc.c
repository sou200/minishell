/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:29:17 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/05 01:00:40 by fel-hazz         ###   ########.fr       */
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
	if (flag == -1)
		*fd = open(str, O_RDWR | O_TRUNC | O_CREAT, 0666);
	else if (flag == -2)
		*fd = open(str, O_RDWR | O_APPEND | O_CREAT, 0666);
	else
		*fd = open(str, O_RDONLY);
	if (*fd == -1)
		ft_error(1, "open: ");
}

char	*generate_name(void)
{
	static int		i;
	char			*str;

	if (i == 0)
		i = 554;
	str = ft_itoa(i);
	if (str)
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

int	ft_input(char *stop)
{
	int		fd;
	char	*str;
	int		tmp;

	str = generate_name();
	if (!str)
		ft_error(1, "here_doc: ");
	ft_open(str, &fd, -1);
	ft_open(str, &tmp, -1);
	unlink(str);
	free(str);
	write(1, "> ", 2);
	str = get_next_line(0);
	while (str && ft_strrcmp(stop, str))
	{
		str = expand_heredoc_line(str, env);
		write(fd, str, ft_strlen(str));
		write(1, "> ", 2);
		free(str);
		str = get_next_line(0);
	}
	free(str);
	str = NULL;
	ft_close(1, fd);
	return (tmp);
}
