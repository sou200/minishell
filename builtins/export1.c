/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:23:11 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/18 13:57:25 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_exportage(char *s)
{
	int		i;
	char	*str;
	int		once;
	int		x;

	if (!s)
		return (0);
	str = ft_malloc(sizeof(char) * (ft_strlen(s) + 14));
	ft_strlcpy(str, "declare -x ", 100);
	once = 0;
	x = 11;
	i = 0;
	while (s[i])
	{
		if (s[i] == '=' && once++ == 0)
		{
			str[x++] = s[i++];
			str[x++] = '"';
			continue ;
		}
		str[x++] = s[i++];
	}
	return (str[x++] = '"', str[x] = '\0', str);
}

char	*ft_exportage1(char *s)
{
	int		i;
	char	*str;
	int		once;
	int		x;

	if (!s)
		return (0);
	str = ft_malloc(sizeof(char) * (ft_strlen(s) + 12));
	ft_strlcpy(str, "declare -x ", 100);
	once = 0;
	x = 11;
	i = 0;
	while (s[i])
		str[x++] = s[i++];
	return (str[x] = '\0', str);
}

char	*ft_exportage3(char *s)
{
	int		i;
	char	*str;
	int		once;
	int		x;

	if (!s)
		return (0);
	str = ft_malloc(sizeof(char) * (ft_strlen(s) + 13));
	ft_strlcpy(str, "declare -x ", 100);
	once = 0;
	x = 11;
	i = 0;
	while (s[i])
	{
		if (s[i] == '+' && once++ == 0)
			i++;
		if (s[i] == '=' && once++ == 1)
		{
			str[x++] = s[i++];
			str[x++] = '"';
			continue ;
		}
		str[x++] = s[i++];
	}
	return (str[x++] = '"', str[x] = '\0', str);
}

void	print_export(void)
{
	t_list	*traveler;

	traveler = gl.export_list;
	while (traveler != NULL)
	{
		printf("%s\n", (char *)(traveler->content));
		traveler = traveler->next;
	}
}

int	ft_export(char **args)
{
	int		i;
	t_list	*tmp;

	gl.return_value = 0;
	i = -1;
	if (!args[0])
		print_export();
	while (args[++i])
	{
		tmp = export_exists(args[i]);
		if (!tmp)
			add_value(args[i]);
		else
			replace_value(args[i], tmp);
	}
	return (gl.return_value);
}
