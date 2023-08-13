/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:11:20 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/13 07:34:48 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1l;
	size_t	s2l;
	size_t	i;
	size_t	j;
	char	*p;

	if (!s2 && !s1)
		return (NULL);
	if (s2 == 0)
		s2 = "";
	if (s1 == 0)
		s1 = "";
	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	i = 0;
	j = 0;
	p = (char *)malloc((s1l + s2l + 1) * sizeof(char));
	if (p == 0)
		return (0);
	ft_memmove(p, s1, s1l);
	ft_memmove(p + s1l, s2, s2l);
	p[s1l + s2l] = '\0';
	return (p);
}
