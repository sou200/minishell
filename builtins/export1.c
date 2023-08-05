/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:23:11 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/05 17:37:09 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//normal export from env
char	*ft_exportage(char *s)
{
	int		i;
	char	*str;
	int		once;
	int		x;

	if (!s)
		return (0);
	str = malloc(sizeof(char) * (ft_strlen(s) + 14));
	if (!str)
		ft_error(ENOMEM, "malloc: ");
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
	str[x++] = '"';
	str[x] = '\0';
	return (str);
}

//export export only
char	*ft_exportage1(char *s)
{
	int		i;
	char	*str;
	int		once;
	int		x;

	if (!s)
		return (0);
	str = malloc(sizeof(char) * (ft_strlen(s) + 12));
	if (!str)
		ft_error(ENOMEM, "malloc: ");
	ft_strlcpy(str, "declare -x ", 100);
	once = 0;
	x = 11;
	i = 0;
	while (s[i])
		str[x++] = s[i++];
	str[x] = '\0';
	return (str);
}

//export append
char	*ft_exportage3(char *s)
{
	int		i;
	char	*str;
	int		once;
	int		x;

	if (!s)
		return (0);
	str = malloc(sizeof(char) * (ft_strlen(s) + 13));
	if (!str)
		ft_error(ENOMEM, "malloc: ");
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
	str[x++] = '"';
	str[x] = '\0';
	return (str);
}

//add export to free list
void	print_export(void)
{
	t_list	*traveler;

	traveler = export_list;
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
	return (0);
}
