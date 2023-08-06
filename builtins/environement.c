/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:00:38 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/06 02:58:49 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialise_env3(int i, char *s, char *tmp)
{
	char	*two[2];

	two[0] = "SHLVL=1";
	two[1] = 0;
	s = (char *)ft_getenv("SHLVL");
	if (s)
	{
		s += 6;
		if (is_num(s))
		{
			i = ft_atoi(s) + 1;
			s = ft_itoa(i);
			tmp = ft_strjoin("SHLVL=", s);
			free(s);
			two[0] = tmp;
			two[1] = 0;
			ft_export(two);
			free (tmp);
		}
		else
			ft_export(two);
	}
	else
		ft_export(two);
}

void	initialise_env2(void)
{
	char	*tmp;
	char	*two[2];

	initialise_env3(0, 0, 0);
	remove_var("OLDPWD");
	if (*default_env[0])
	{
		tmp = ft_strjoin("PWD=", default_env[0]);
		two[0] = tmp;
		two[1] = 0;
		ft_export(two);
		free(tmp);
	}
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
	initialise_env2();
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
