/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:58:25 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/07/20 18:56:21 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../minishell.h"

void	initialise_env(const char **en)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	while (en[y])
		y++;
	env = malloc((y + 1) * sizeof(char *));
	if (!env)
		ft_exit(ENOMEM);
	y = -1;
	while (en[++y])
	{
		env[y] = ft_strdup(en[y]);
		if (!env[y])
			ft_exit(ENOMEM);//freee this in env
	}
}
#include<signal.h>



int	size_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**realloc_env(int n)
{
	int	i;
	char **cpy;

	i = 0;
	while (env[i])
		i++;
	cpy = malloc(sizeof(char *) * (i + 1));
	if (!cpy)
		ft_exit(ENOMEM);
	return (cpy);	
}

void free_table(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = 0;
		i++;
	}
	free(str);
}

void remove_var(const char *var)
{
	int	i;
	char **new;
	int	y;

	i = 0;
	while (env[i] && !ft_strncmp(var,env[i],ft_strlen(var) + 1))
		i++;
	if (!env[i])
		return ;
	new = realloc_env(size_double(var) - 1);	
	y = -1;
	while (env[++y] && (y != i))
		new[y] = env[y];
	while (env[y] && env[y + 1])
	{
		new[y] = env[y + 1];
		y++;
	}
	new[y] = 0;
	free_table(env);
	env = new;
}