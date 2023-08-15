/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:40:58 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/15 18:58:23 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

const char	*ft_getenv3(const char *var)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (!ft_strcmp(var, "PWD"))
	{
		if (!gl.default_env[2])
			return (0);
		while (gl.default_env[2][x] && gl.default_env[2][x] != '=')
			x++;
		return ((gl.default_env[2] + ++x));
	}
	else if (!ft_strcmp(var, "OLDPWD"))
	{
		if (!gl.default_env[3])
			return (0);
		while (gl.default_env[3][x] && gl.default_env[3][x] != '=')
			x++;
		return ((gl.default_env[3] + ++x));
	}
	return (0);
}

void	controlec1(int c)
{
	(void ) c;
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_cd_1(char *str)
{
	char	*s[2];

	if (ft_getenv1("PWD"))
	{
		str = ft_strjoin("OLDPWD=", ft_getenv1("PWD"));
		error_malloc(!str);
		s[0] = str;
		s[1] = 0;
		ft_export(s);
		free(str);
	}
	else if (ft_getenv3("PWD"))
	{
		str = ft_strjoin("OLDPWD=", ft_getenv3("PWD"));
		error_malloc(!str);
		free(gl.default_env[3]);
		gl.default_env[3] = str;
	}
	else
	{
		s[0] = "OLDPWD";
		s[1] = 0;
		ft_unset(s);
	}
}
