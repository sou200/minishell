/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:11:20 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/13 17:56:27 by serhouni         ###   ########.fr       */
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

	if (s2 == 0)
		return (0);
	if(s1 == 0)
		s1 = "";
	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	i = 0;
	j = 0;
	p = (char *)malloc((s1l + s2l + 1) * sizeof(char));
	if (p == 0)
		return (0);
	while (j < s1l)
		p[i++] = s1[j++];
	j = 0;
	while (j < s2l)
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}
