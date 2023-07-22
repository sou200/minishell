/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 08:28:08 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/04/16 13:47:32 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct x_list {
	int				fd;
	char			*str;
	struct x_list	*next;
}t_list1;
char	find_newline(char *str);
char	*get_next_line(int fd);
void	find_or_create(int fd, t_list1 **node, t_list1 **tmp);
char	get_line1(t_list1 **tmp, int fd, char **line, ssize_t byte);
char	ft_strjoin1(char **s1, char **s2, ssize_t *byte, ssize_t *positio);
char	ft_strjoin2(char **s1);
char	put_linestrim(t_list1 **tmp, char **line);
ssize_t	ft_strlen1(const char *str, int l);
void	ft_strncpy1(char *dst, char *src, ssize_t n);
char	lst_delete(t_list1 **lst, t_list1 **lst1, t_list1 *walker);
#endif