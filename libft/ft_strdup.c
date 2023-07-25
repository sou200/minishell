/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 23:19:47 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/21 02:14:20 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	unsigned int	len;
	char			*p;
	unsigned int	i;

	if(s == NULL)
		return NULL;

	len = ft_strlen(s);
	p = (char *)malloc((len + 1) * sizeof(char));
	if (p == 0)
		return (0);
	i = 0;
	while (i <= len)
	{
		*(p + i) = *(s + i);
		i++;
	}
	return (p);
}
