/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recyclable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:20:46 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/07/25 20:25:06 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	getalloclen(size_t slen, unsigned int start, size_t len)
{
	size_t	flen;

	flen = 0;
	while ((start + flen) < slen && flen < len)
		flen++;
	return (flen);
}

char	*ft_substr1(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	sl;
	size_t	flen;

	if (s == 0)
		return (0);
	sl = ft_strlen(s);
	flen = getalloclen(sl, start, len);
	p = (char *)malloc((flen + 1) * sizeof(char));
	if (!p)
		ft_exit(ENOMEM);
	recycle(1, p);
	ft_memmove(p, (s + start), flen);
	p[flen] = '\0';
	return (p);
}

t_list	*ft_lstnew1(void *content)
{
	t_list	newnode;
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == 0)
		ft_exit(ENOMEM);
	recycle(1, node);
	newnode.content = content;
	newnode.next = NULL;
	newnode.prev = NULL;
	*node = newnode;
	return (node);
}


char	*ft_strdupenv(const char *s)
{
	unsigned int	len;
	char			*p;
	unsigned int	i;

	len = ft_strlen(s);
	env.size += len + 1;
	p = (char *)malloc((len + 1) * sizeof(char));
	if (p == 0)
		ft_exit(ENOMEM);
	recycle(1, p);
	i = 0;
	while (i <= len)
	{
		*(p + i) = *(s + i);
		i++;
	}
	return (p);
}

char	*ft_strdup1(const char *s)
{
	unsigned int	len;
	char			*p;
	unsigned int	i;

	len = ft_strlen(s);
	p = (char *)malloc((len + 1) * sizeof(char));
	if (p == 0)
		ft_exit(ENOMEM);
	recycle(1, p);
	i = 0;
	while (i <= len)
	{
		*(p + i) = *(s + i);
		i++;
	}
	return (p);
}