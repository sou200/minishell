/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:58:25 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/07/22 13:26:20 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../minishell.h"

int	ft_pathcmp(const char *s1, const char *PATH)
{
	size_t	i;

	i = 0;
	if (!s1 && !PATH)
		return (0);
	if (!s1 || !PATH)
		return (1);
	while (s1[i] && PATH[i] && PATH[i] != '=')
	{
		if (s1[i] != PATH[i])
			return (1);
		i++;
	}
	if (PATH[i] == '=' && !s1[i])
		return (0);
	return (1);
}

const char *ft_getenv(const char *var)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	if (!var)
		return (0);
	while (env[i] && ft_pathcmp(var, env[i]))
		i++;
	if (!env[i])
		return (0);
	return ((env[i] + ft_strlen(var) + 1));
}

void	initialise_env(const char **en)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	if (!en)
		return ;
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
			ft_exit(ENOMEM);
	}
	env[y] = 0;
}

int	size_double(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	**realloc_env(int n)
{
	char **cpy;

	cpy = malloc(sizeof(char *) * (n));
	if (!cpy)
		ft_exit(ENOMEM);
	return (cpy);	
}

void free_table(char **str)
{
	int i;

	i = 0;
	while (str && str[i])
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

	if (!var || !ft_getenv(var))
		return ;
	if (!check_var(var))
	{
		printf("minishell: unset: `%s': not a valid identifier\n",var);
		errno = 1;
	}
	i = 0;
	while (env[i] && ft_pathcmp(var, env[i]))
		i++;
	if (!env[i])
		return ;
	new = realloc_env(size_double(env));	
	y = -1;
	while (env[++y] && (y != i))
		new[y] = env[y];
	if (!env[y])
		return ;
	free(env[y]);
	while (env[y + 1])
	{
		new[y] = env[y + 1];
		y++;
	}
	new[y] = 0;
	free(env);
	env = new;
}

int	check_var(const char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	check_var1(const char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[i])
	{
		if (var[i] == '=')
			break ;
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}


int add_var1(const char *var)
{
	int	i;
	int	x;

	i = 0;
	while (env[i])
	{
		x = 0;
		while (env[i][x] && var[x] && env[i][x] == var[x])
		{
			if (env[i][x] == var[x] && env[i][x] == '=')
				break ;
			x++;
		}
		if (env[i][x] == var[x] && env[i][x] == '=')
			break ;
		i++;
	}
	if (!env[i] || !(env[i][x] == var[x] && env[i][x] == '='))
		return (0);
	free(env[i]);
	env[i] = ft_strdup(var);
	if (!env[i])
		ft_exit(ENOMEM);
	return (1);
}
void add_var(const char *var)
{
	int	i;
	char **new;
	int	y;

	i = 0;
	if (!var)
		return ;
	if (!check_var1(var))
	{
		printf("minishell: unset: `%s': not a valid identifier\n",var);
		errno = 1;
	}
	if (add_var1(var))
		return ;
	new = realloc_env(size_double(env) + 2);	
	y = -1;
	while (env[++y])
		new[y] = env[y];
	new[y] = ft_strdup(var);
	if (!new[y])
		ft_exit(ENOMEM);
	new[++y] = 0;
	free(env);
	env = new;
}

void ft_env(void)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env && env[i])
		printf("%s\n",env[i++]);
}

void ft_printenv(const char *var)
{
	if (!var)
		return ;
	printf("%s=%s\n",var,ft_getenv(var));
}