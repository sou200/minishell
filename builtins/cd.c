/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:48:22 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/07/19 16:57:21 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

const char *ft_getenv(const char *var)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	while (env[i] && ft_strncmp(var, env[i], ft_strlen(var) + 1))
		i++;
	if (!env[i])
		return (0);
	if (!*(env[i] + ft_strlen(var) + 1))
		return (0);
	return ((env[i] + ft_strlen(var) + 1));
}

char	**cd_path(char **env)
{
	const char	*path;
	char	**paths;

	path = ft_getenv("CDPATH");
	if (!*path)
		return(0);
	paths = ft_split(path, ':');
	if (!paths)
		ft_exit(ENOMEM);
	return (paths);
}


int		get_sizeslach(char *s)
{
	int	i;
	int	x;
	int	o;

	i = 0;
	x = 0;
	o = 0;
	while (s[i])
	{
		while (s[i] == '/')
		{
			o++;
			i++;
		}
		if (o != 0)
		{
			o = 0;
			x++;
		}
		while (s[i] && s[i] != '/')
		{
			i++;
			x++;
		}
	}
	return (x);
}

char	*trim_backslash(char *s)
{
	int		i;
	char	*trimed;
	int		x;

	trimed = malloc(sizeof(char) * (get_sizeslach(s) + 1));
	if (!trimed)
	return(free(s),ft_exit(ENOMEM));
	i = 0;
	x = 0;
	while (s[i])
	{
		if (s[i] == '/')
		{
			trimed[x++] = '/';
			while(s[i] == '/')
				i++;
		}
		if (s[i])
			trimed[x++] = s[i++];
	}
	return(trimed[x] = '\0', free(s), trimed);
}
char	*cd_pathcheck(const char *dirname)
{
	char	*tmp;
	char	*str;
	char	**paths;
	int		i;

	paths = cd_path(env);
	if (!paths)
		return (0);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			ft_exit(ENOMEM);
		str = ft_strjoin(tmp, dirname);
		if (!str)
			return(free(tmp), ft_exit(ENOMEM));
		free(tmp);
		if (!access(str, X_OK))
			return (trim_backslash(str));
		free(str);
		i++;
	}
	return (0);
}

char return_value;

int abs_path (const char *dirname)
{
  if (dirname == 0 || *dirname == '\0')
    return (0);
  if (dirname[0] == '/')
    return (1);
  if (dirname[0] == '.' && (!dirname[1] || dirname[1] == '/'))
    return (1);
  if (dirname[0] == '.' && dirname[1] == '.' && (!dirname[2] || dirname[2] == '/'))
    return (1);
  return (0);
}

void	ft_cd(char *dirname)
{
	char	flag;
	const char	*cdpath;

	cdpath = ft_getenv("CDPATH");
	flag = 0;
	if (!dirname)
	{
		dirname = ft_getenv("HOME");
		if (!dirname)
		{
			printf("minishell: cd: HOME not set\n");
			return_value = 1; 
		}
	}
	else if (dirname[0] == '-' && dirname[1] == '\0')
	{
		dirname = ft_getenv("OLDPWD");
		if (!dirname)
		{
			printf("minishell: cd: OLDPWD not set\n");
			return_value = 1;
		}
		else
			flag = 1;
	}
	else if (!abs_path(dirname) && cdpath)
	{
		cdpath = cd_pathcheck(cdpath);
		if (cdpath)
		{
			if (!chdir(cdpath))
				printf("%s\n",cdpath);
			else
			{
				printf("cd: %s", strerror(errno));
				return_value = 1;
			}
			free((void *)cdpath);
		}
	}
	else
	{
		if (!chdir(dirname))
		{
			if (flag)
				printf("%s\n",dirname);
		}
		else
		{
			printf("cd: %s", strerror(errno));
			return_value = 1;
		}
	}
}