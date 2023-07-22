/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 08:28:03 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/04/16 13:43:42 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list1	*node;
	char			*line;
	t_list1			*tmp;
	ssize_t			byte;
	t_list1			*walker;

	walker = NULL;
	byte = BUFFER_SIZE;
	line = NULL;
	find_or_create(fd, &node, &tmp);
	if (!node || !tmp)
		return (NULL);
	if (read(fd, line, 0) < 0)
	{
		lst_delete(&node, &tmp, walker);
		return (NULL);
	}
	get_line1(&tmp, fd, &line, byte);
	put_linestrim(&tmp, &line);
	if (!line || !(tmp->str) || line == tmp->str)
	{
		lst_delete(&node, &tmp, walker);
		return (line);
	}
	return (line);
}

void	find_or_create(int fd, t_list1 **node, t_list1 **tmp)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return ;
	*tmp = *node;
	while (*tmp && (*tmp)->fd != fd && (*tmp)->next)
		*tmp = (*tmp)->next;
	if (*tmp && (*tmp)->fd == fd)
		return ;
	else if (!(*tmp))
	{
		*node = malloc(sizeof(t_list1));
		if (!(*node))
			return ;
		(*node)->fd = fd;
		(*node)->next = NULL;
		(*node)->str = NULL;
		*tmp = *node;
		return ;
	}
	(*tmp)->next = malloc(sizeof(t_list1));
	if (!((*tmp)->next))
		return ;
	(*tmp)->next->fd = fd;
	(*tmp)->next->next = NULL;
	(*tmp)->next->str = NULL;
	(*tmp) = (*tmp)->next;
}

char	get_line1(t_list1 **tmp, int fd, char **line, ssize_t byte)
{
	ssize_t	positio;

	while (!find_newline((*tmp)->str) && byte)
	{
		positio = 0;
		*line = malloc(BUFFER_SIZE + 1000 + 1);
		if (!(*line))
			return (free ((*tmp)->str), ((*tmp)->str) = 0, 1);
		**line = '\0';
		while (!find_newline(*line) && positio < 1000 && byte)
		{
			byte = read(fd, *line + positio, BUFFER_SIZE);
			if (byte == 0 && positio == 0)
				return (free(*line), *line = 0, 1);
			if (byte == 0)
				break ;
			positio += byte;
			if (byte < 0)
				return (free ((*tmp)->str),
					(*tmp)->str = 0, free(*line), *line = 0, 1);
			(*line)[positio] = '\0';
		}
		ft_strjoin1(&((*tmp)->str), &((*line)), &byte, &positio);
	}
	return (1);
}

char	ft_strjoin1(char **s1, char **s2, ssize_t *byte, ssize_t *positio)
{
	char	*p;

	*byte = *positio;
	if (*byte == 0)
		return (free(*s2), *s2 = 0, 1);
	*positio = ft_strlen1(*s1, 1);
	p = malloc(*positio + *byte + 1);
	if (!p)
	{
		if (*s1)
			free(*s1);
		*s1 = 0;
		return (free(*s2), *s2 = 0, *byte = 0, 1);
	}
	ft_strncpy1(p, *s1, *positio);
	ft_strncpy1(p + *positio, *s2, *byte);
	if (*s1)
		free(*s1);
	*s1 = p;
	free(*s2);
	*s2 = 0;
	return (1);
}

char	ft_strjoin2(char **s1)
{
	char	*p;
	ssize_t	i;
	ssize_t	x;

	if (!(*s1))
		return (1);
	i = ft_strlen1(*s1, 1);
	x = ft_strlen1(*s1, 0);
	if (i <= x)
		return (free(*s1), *s1 = 0, 1);
	p = malloc(i - x + 1);
	if (!p)
		return (free(*s1), *s1 = 0, 1);
	ft_strncpy1(p, *(s1) + x, i - x);
	free(*s1);
	*s1 = p;
	if (!p[0])
		return (free (p), p = 0, *s1 = 0, 1);
	return (1);
}
