/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:48:22 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/06 08:01:41 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

const char	*ft_getenv1(const char *var)
{
	int	i;
	int	x;

	i = 0;
	if (!var)
		return (0);
	while (env[i] && ft_pathcmp(var, env[i]))
		i++;
	if (!env[i])
		return (0);
	x = 0;
	while (env[i][x] && env[i][x] != '=')
		x++;
	x++;
	return ((env[i] + x));
}

int	abs_path(const char *dirname)
{
	if (dirname == 0 || *dirname == '\0')
		return (0);
	if (dirname[0] == '/')
		return (1);
	if (dirname[0] == '.' && (!dirname[1] || dirname[1] == '/'))
		return (1);
	if (dirname[0] == '.'
		&& dirname[1] == '.' && (!dirname[2] || dirname[2] == '/'))
		return (1);
	return (0);
}

char	*get_dirname(char *dirname)
{
	char	*pwd;
	char	*tmp;

	pwd = getcwd(0, 0);
	if (!pwd)
	{
		error_write(CD_ERROR);
		pwd = ft_strjoin(default_env[0], "/");
		tmp = pwd;
		pwd = ft_strjoin(tmp, dirname);
		free(tmp);
	}
	return (pwd);
}

int	ft_cd_succes(char *dirname, char *str)
{
	char	*s[2];

	if (!chdir(dirname))
	{
		dirname = get_dirname(dirname);
		if (ft_getenv1("PWD"))
		{
			str = ft_strjoin("OLDPWD=", ft_getenv1("PWD"));
			error_malloc(!str);
			s[0] = str;
			s[1] = 0;
			ft_export(s);
			free(str);
		}
		free(default_env[0]);
		default_env[0] = ft_strdup(dirname);
		error_malloc(!default_env[0]);
		str = ft_strjoin("PWD=", dirname);
		error_malloc(!str);
		return (s[0] = str, s[1] = 0, ft_export(s), free(str), 1);
	}
	else
		return (print_error1(5, "cd: ", dirname, ": "
				, strerror(errno), "\n"), return_value = 1, 0);
}

int	ft_cd(const char *dirname)
{
	return_value = 0;
	if (!dirname)
	{
		dirname = ft_getenv1("HOME");
		if (!dirname)
			return (error_write("minishell: cd: HOME not set\n")
				, return_value = 1, 1);
		else
			ft_cd_succes((char *)dirname, 0);
	}
	else if (dirname[0] == '-' && dirname[1] == '\0')
	{
		dirname = ft_getenv1("OLDPWD");
		if (!dirname)
			return (error_write("minishell: cd: OLDPWD not set\n")
				, return_value = 1, 1);
		if (ft_cd_succes((char *)dirname, 0))
			printf("%s\n", dirname);
	}
	else
		ft_cd_succes((char *)dirname, 0);
	return (return_value);
}
