/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:58:25 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/05 01:40:51 by fel-hazz         ###   ########.fr       */
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

	i = 0;
	if (!var)
		return (0);
	while (env[i] && ft_pathcmp(var, env[i]))
		i++;
	if (env[i])	
		return ((env[i]));
	return (default_env[1]);
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
	initialise_export();
}

char *ft_exportage3(char *s)
{
	int		i;
	char	*str;
	int		once;
	int		x;
	
	if (!s)
		return (0);
	str = malloc(sizeof(char) * (ft_strlen(s) + 13));
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
			continue;
		}
		str[x++] = s[i++];
	}
	str[x++] = '"';
	str[x] = '\0';
	return (str);
}

char *ft_exportage(char *s)
{
	int		i;
	char	*str;
	int		once;
	int		x;
	
	if (!s)
		return (0);
	str = malloc(sizeof(char) * (ft_strlen(s) + 14));
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
			continue;
		}
		str[x++] = s[i++];
	}
	str[x++] = '"';
	str[x] = '\0';
	return (str);
}

char *ft_exportage1(char *s)
{
	int		i;
	char	*str;
	int		once;
	int		x;
	
	if (!s)
		return (0);
	str = malloc(sizeof(char) * (ft_strlen(s) + 12));
	ft_strlcpy(str, "declare -x ", 100);
	once = 0;
	x = 11;
	i = 0;
	while (s[i])
		str[x++] = s[i++];
	str[x] = '\0';
	return (str);
}

void	initialise_export(void)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	while (env[y])
	{
		ft_lstaddandsort(&export_list, ft_lstnew(ft_exportage(env[y])));
		y++;
	}
	if (!ft_getenv("OLDPWD"))
		ft_lstaddandsort(&export_list, ft_lstnew(ft_exportage1("OLDPWD")));
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
		ft_exit(ENOMEM);
	return (1);
}

void	print_export(void)
{
	t_list	*traveler;

	traveler = export_list;
	while (traveler != NULL)
	{
		printf("%s\n",(char *)(traveler->content));
		traveler = traveler->next;
	}
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
		// sleep (1);
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
	char *str;
	int		i;
	int		z;
	char *tmp;
	i = 0;
	z = 0;
	while (old[i])
		i++;
	if (i > 0)
		i--;
	if (old[i] == '"')
		str = malloc(sizeof(char) * ft_strlen(old));
	else
		str = malloc(sizeof(char) * (ft_strlen(old) + 1));
	while (old[z])
	{
		if (z == i)
			break ;
		str[z] = old[z];
		z++;
	}
	str[z] = '\0';
	tmp = ft_strjoin(str, ft_strchr(var, '=') + 1);
	free (str);
	if (old[i] != '"')
		return (tmp);
	str = ft_strjoin(tmp, "\"");
	return (free(tmp), str);
}

// export and \"
// char *join_export(char *old, char *var)
// {
// 	char *str;
// 	int		i;
// 	int		z;
// 	char *tmp;
// 	i = 0;
// 	z = 0;
// 	while (old[i])
// 		i++;
// 	if (i > 0)
// 		i--;
// 	if (old[i] == '"')
// 		str = malloc(sizeof(char) * ft_strlen(old));
// 	else
// 		str = malloc(sizeof(char) * (ft_strlen(old) + 1));
// 	while (old[z])
// 	{
// 		if (z == i)
// 			break ;
// 		str[z] = old[z];
// 	}
// 	str[z] = '\0';
// 	tmp = ft_strjoin(str, ft_strchr(var, '=') + 1);
// 	free (str);
// 	if (old[i] != '"')
// 		return (tmp);
// 	str = ft_strjoin(tmp, "\"");
// 	return (free(tmp), str);
// }
void env_append(char *str, char *var)
{
		int	i;
	int	x;
	char *s;
	char *t;
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
	x = 0;
	while (var[x])
	{
		if (var[x] == '+' || var[x] == '=')
			break ;
		x++;
	}
	s = malloc(x + 2);
	x = 0;
	while (var[x])
	{
		if (var[x] == '+' || var[x] == '=')
			break ;
		s[x] = var[x];
		x++;
	}
	s[x++] = '=';
	s[x] = '\0';
	env[i] = ft_substr(ft_strchr(str,'=') + 2, 0, ft_strlen(ft_strchr(str,'=') + 2) - 1);
	t = ft_strjoin(s, env[i]);
	free (s);
	free(env[i]);
	env[i] = t;
	if (!env[i])
		ft_exit(ENOMEM);
}
void replace_value(char *var, t_list *tmp)
{
	int		i;
	char	*str;

	if (!check_var1(var))
	{
		printf("minishell: set: `%s': not a valid identifier\n",var);
		errno = 1;
		return ;
	}
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
void add_value(char *var)
{
	int		i;

	if (!check_var1(var))
	{
		printf("minishell: set: `%s': not a valid identifier\n",var);
		errno = 1;
		return ;
	}
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
	{
		int x;
		char *s;
			x = 0;
	while (var[x])
	{
		if (var[x] == '+' || var[x] == '=')
			break ;
		x++;
	}
	s = malloc(x + 2);
	x = 0;
	while (var[x])
	{
		if (var[x] == '+' || var[x] == '=')
			break ;
		s[x] = var[x];
		x++;
	}
	s[x++] = '=';
	s[x] = '\0';
	add_var(s);
	free(s);
	}
}

int ft_export(char **args)
{
	int 	i;
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

int ft_env(void)
{
	int	i;

	i = 0;
	if (!env)
		return (1);
	while (env && env[i])
		printf("%s\n",env[i++]);
	return (0);
}

int ft_printenv(const char *var)
{
	const char	*s;

	s = ft_getenv(var);
	if (s)
		printf("%s\n", ft_getenv(var));
	return (0);
}