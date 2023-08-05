/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:37:06 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/04 19:38:30 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

ssize_t	ft_strlen1(const char *str, int l)
{
	ssize_t	i;

	if (!str)
		return (0);
		i = 0;
	if (l == 1)
	{
		while (str[i])
			i++;
		return (i);
	}
	while (str[i] && (str[i] != '\n'))
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

void	ft_strncpy1(char *dst, char *src, ssize_t n)
{
	ssize_t	i;

	i = 0;
	if (!n || !dst || !src)
		return ;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	find_newline(char *str)
{
	ssize_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}

char	put_linestrim(t_list1 **tmp, char **line)
{
	ssize_t	i;

	i = ft_strlen1(((*tmp)->str), 0);
	if (!i)
		return (free ((*tmp)->str), ((*tmp)->str) = 0, *line = 0, 1);
	*line = malloc(sizeof(char) * (i + 1));
	if (!(*line))
		return (free((*tmp)->str), (*tmp)->str = 0, 1);
	i = -1;
	while (((*tmp)->str)[++i] && (((*tmp)->str)[i] != '\n'))
		(*line)[i] = ((*tmp)->str)[i];
	if (((*tmp)->str)[i] && ((*tmp)->str)[i] == '\n')
	{
		(*line)[i] = ((*tmp)->str)[i];
		(*line)[++i] = '\0';
	}
	else
		(*line)[i] = '\0';
	ft_strjoin2(&((*tmp)->str));
	return (1);
}

char	lst_delete(t_list1 **lst, t_list1 **lst1, t_list1 *walker)
{
	walker = *lst;
	if (!*lst)
		return (1);
	if ((*lst1 == *lst || !(*lst1)))
	{
		if ((*lst)->str)
			free ((*lst)->str);
		(*lst)->str = 0;
		*lst1 = (*lst)->next;
		free (*lst);
		*lst = (*lst1);
		*lst1 = 0;
		return (1);
	}
	while ((walker->next) && ((walker->next)->fd != (*lst1)->fd))
		walker = walker->next;
	if ((walker->next) && (*lst1) && (((walker->next)->fd == (*lst1)->fd)))
	{
		walker->next = (*lst1)->next;
		if ((*lst1)->str)
			free ((*lst1)->str);
		return ((*lst1)->str = 0, free (*lst1), *lst1 = 0, 1);
	}
	return (1);
}
