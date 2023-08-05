/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:58:25 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/05 20:19:12 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	char	**cpy;

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
		if (var[i] == '+' && var[i + 1] == '=')
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
		if (!var[x] && env[i][x] == '=')
			return (1);
		if (env[i][x] == var[x] && env[i][x] == '=')
			break ;
		i++;
	}
	if (!env[i] || !(env[i][x] == var[x] && env[i][x] == '='))
		return (0);
	free(env[i]);
	env[i] = ft_strdup(var);
	if (!env[i])
		ft_error(ENOMEM, "malloc: ");
	return (1);
}

t_list	*export_exists(char *value)
{
	t_list	*traveler;
	char	*str;
	int		i;
	int		y;

	traveler = export_list;
	while (traveler)
	{
		i = 11;
		y = 0;
		str = ((char *)(traveler->content));
		while (str[i] && value[y] && (str[i] == value[y]))
		{
			if (str[i] == '=' && value[y] == '=')
				break ;
			i++;
			y++;
		}
		if (value[y] == '+')
			y++;
		if (str[i] == value[y] || (str[i] == '=' && !value[y]) || (!str[i] && value[y] == '='))
			return (traveler);
		traveler = traveler->next;
	}
	return (0);
}

char *join_export(char *old, char *var)
{
	char 	*str;
	int		i;
	char	*tmp;

	i = 0;
	while (old[i])
	{
		if ((old[i] == '"') && (old[i + 1] == '\0'))
			break ;
		i++;
	}
	if (!old[i])
		return (ft_exportage3(var));
	old[i] = '\0';
	tmp = ft_strjoin(old, ft_strchr(var, '=') + 1);
	str = ft_strjoin(tmp, "\"");
	return (free(tmp), str);
}

int	env_append_find(char *str, char *var)
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
		if (var[x] == '+' && var[x + 1] == '=' && env[i][x] == '=')
			break ;
		if (env[i][x] == var[x] && env[i][x] == '=')
			break ;
		i++;
	}
	free(env[i]);
	return (i);
}

void	*ft_malloc(size_t size)
{
	void	*space;

	space = malloc(size);
	if (!space)
		ft_error(ENOMEM, "malloc: ");
	return (space);
}

void	error_malloc(int condition)
{
	if (!condition)
		return ;
	ft_error(ENOMEM, "malloc: ");
}
void env_append(char *str, char *var)
{
	int		x;
	char	*s;
	char	*t;

	x = 0;
	while (var[x] && !(var[x] == '+' || var[x] == '='))
		x++;
	s = ft_malloc(x + 2);
	x = -1;
	while (var[++x] && !(var[x] == '+' || var[x] == '='))
		s[x] = var[x];
	s[x++] = '=';
	s[x] = '\0';
	x = env_append_find(str, var);
	if (!ft_strchr(str,'='))
		return (add_var(s), free(s));
	t = ft_substr(ft_strchr(str,'=') + 2, 0, ft_strlen(ft_strchr(str,'=') + 2) - 1);
	error_malloc(!t);
	str = ft_strjoin(s, t);
	error_malloc(!str);
	ft_free(2, s, t);
	if (!env[x])
		return(add_var(str), free(str));
	env[x] = str;
}
void replace_value(char *var, t_list *tmp)
{
	int		i;
	char	*str;

	if (!check_var1(var))
		return (print_error(1, 3, "minishell: export: `",var, "': not a valid identifier\n"));
	if (!ft_strchr(var, '='))
		return ;
	i = which_export(var);
	if (i == 2)
		str = join_export((char *)(tmp->content), var);
	else
		str = ft_exportage(var);
	free(tmp->content);
	tmp->content = str;
	if (i == 2)
		env_append(str, var);
	else
		add_var(var);
}

int which_export(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (1);
		if (var[i] == '+' && var[i + 1] == '=')
			return (2);
		i++;
	}
	return (3);
}

void	empty_var(char *var)
{
	int		x;
	char	*s;

	x = 0;
	// while (var[x])
	// {
	// 	if (var[x] == '+' || var[x] == '=')
	// 		break ;
	// 	x++;
	// }
	s = ft_malloc(ft_strlen(var));
	x = -1;
	while (var[++x] && !(var[x] == '+' || var[x] == '='))
		s[x] = var[x];
	s[x] = '=';
	while (var[++x + 1])
		s[x] = var[x + 1];
	s[x] = '\0';
	add_var(s);
	free(s);
}
void add_value(char *var)
{
	int		i;

	if (!check_var1(var))
		return (print_error(1, 3, "minishell: export: `",var, "': not a valid identifier\n"));
	i = which_export(var);
	if (i == 1)
		ft_lstaddandsort(&export_list, ft_lstnew(ft_exportage(var)));
	else if (i == 3)
		ft_lstaddandsort(&export_list, ft_lstnew(ft_exportage1(var)));
	else
		ft_lstaddandsort(&export_list, ft_lstnew(ft_exportage3(var)));
	if (i == 1)
		add_var(var);
	if (i == 2)
		empty_var(var);
}

void add_var(const char *var)
{
	int	i;
	char **new;
	int	y;

	i = 0;
	if (!var)
		return ;
	if (add_var1(var))
		return ;
	new = realloc_env(size_double(env) + 2);
	if (!new)
		ft_error(ENOMEM, "malloc: ");
	y = -1;
	while (env[++y])
		new[y] = env[y];
	new[y] = ft_strdup(var);
	if (!new[y])
		ft_error(ENOMEM, "malloc: ");
	new[++y] = 0;
	free(env);
	env = new;
}

