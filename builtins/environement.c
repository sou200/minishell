/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:00:38 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/06 00:09:41 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

const char	*ft_getenv(const char *var)
{
	int		i;

	i = 0;
	if (!var)
		return (0);
	while (env[i] && ft_pathcmp(var, env[i]))
		i++;
	if (env[i])
		return ((env[i]));
	i = 0;
	while (default_env[i] && ft_pathcmp(var, default_env[i]))
		i++;
	return (default_env[i]);
}

void	initialise_env(const char **en)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (!en)
		return ;
	while (en[y])
		y++;
	env = malloc((y + 1) * sizeof(char *));
	if (!env)
		ft_error(ENOMEM, "malloc: ");
	y = -1;
	while (en[++y])
	{
		env[y] = ft_strdup(en[y]);
		if (!env[y])
			ft_error(ENOMEM, "malloc: ");
	}
	env[y] = 0;
	initialise_export();
}

void	initialise_export(void)
{
	int		x;
	int		y;
	t_list	*t;

	x = 0;
	y = 0;
	while (env[y])
	{
		t = ft_lstnew(ft_exportage(env[y]));
		if (!t)
			ft_error(ENOMEM, "malloc: ");
		ft_lstaddandsort(&export_list, t);
		y++;
	}
	if (!ft_getenv("OLDPWD"))
	{
		t = ft_lstnew(ft_exportage1("OLDPWD"));
		if (!t)
			ft_error(ENOMEM, "malloc: ");
		ft_lstaddandsort(&export_list, t);
	}
}

int	ft_env(void)
{
	int	i;

	i = 0;
	if (!env)
		return (1);
	while (env && env[i])
		printf("%s\n", env[i++]);
	return (0);
}

int	ft_printenv(const char *var)
{
	const char	*s;

	s = ft_getenv(var);
	if (s)
		printf("%s\n", ft_getenv(var));
	return (0);
}
