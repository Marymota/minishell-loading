/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmota <mmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:57:00 by mmota             #+#    #+#             */
/*   Updated: 2022/02/14 19:06:48 by mmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_filename(t_parser *cmd, int cmd_n, int i)
{
	char	str[100];
	char	*res;
	int		j;
	int		x;

	j = 0;
	x = 0;
	while (cmd->cmds[cmd_n][i][j] != '\0' && cmd->cmds[cmd_n][i][j] != '\n')
	{
		str[x] = cmd->cmds[cmd_n][i][j];
		++j;
		++x;
	}
	str[x] = '\0';
	res = str;
	return (res);
}

void	fill_builtin_mem(char **cmds_list)
{
	cmds_list[0] = "echo";
	cmds_list[1] = "cd";
	cmds_list[2] = "exit";
	cmds_list[3] = "env";
	cmds_list[4] = "export";
	cmds_list[5] = "pwd";
	cmds_list[6] = "unset";
}

int	do_not_redir(t_parser *cmd, int cmd_n)
{
	if (cmd->is_redir[cmd_n][0] == 1)
	{
		if (ft_strcmp(cmd->cmds[cmd_n][2], "export") == 0
			|| ft_strcmp(cmd->cmds[cmd_n][2], "unset") == 0)
			return (1);
	}
	else
	{
		if (ft_strcmp(cmd->cmds[cmd_n][0], "export") == 0
			|| ft_strcmp(cmd->cmds[cmd_n][0], "unset") == 0)
			return (1);
	}
	return (0);
}
