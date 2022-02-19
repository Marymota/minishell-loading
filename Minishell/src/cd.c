/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestevao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:40:10 by pestevao          #+#    #+#             */
/*   Updated: 2022/02/10 17:40:11 by pestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_error(int e)
{
	g_v.last_exit = 1;
	if (e == 0)
		printf("Minishell: cd: too many arguments\n");
	else if (e == 1)
		printf("Minishell: cd: No such file or directory\n");
}

void	run_chdir(char *str)
{
	char	dir[9999];
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", getcwd(dir, 9999));
	export_set_env(tmp);
	chdir(str);
	free(tmp);
}

void	run_cd(t_parser *cmd, int cmd_n)
{
	int	e;

	g_v.last_exit = 0;
	if (!cmd->count_token[cmd_n])
		run_chdir(parser_getenv("HOME"));
	else
	{
		if (ft_strcmp(cmd->cmds[cmd_n][1], "..") == 0)
			run_chdir("..");
		else if (ft_strcmp(cmd->cmds[cmd_n][1], "-") == 0)
		{
			run_chdir(parser_getenv("OLDPWD"));
			run_pwd();
		}
		else if (ft_strcmp(cmd->cmds[cmd_n][1], "//") == 0)
			run_chdir("//");
		else if (cmd->count_token[cmd_n] > 1)
			cd_error(0);
		else
		{
			e = chdir((char *)cmd->cmds[cmd_n][1]);
			if (e != 0)
				cd_error(1);
		}
	}
}
