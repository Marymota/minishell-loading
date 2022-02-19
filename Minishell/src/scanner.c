/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmota <mmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:08:44 by pestevao          #+#    #+#             */
/*   Updated: 2022/02/14 20:39:21 by mmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_redir_to_execve(t_parser *cmd, int cmd_n, int i, char *ret)
{
	int	j;
	int	cmd_len;
	int	x;

	j = -1;
	x = -1;
	while (++j <= cmd->count_token[cmd_n])
	{
		cmd_len = ft_strlen(cmd->cmds[0][2]);
		if (cmd->is_redir[0][0] == 1)
		{
			while (++x < cmd_len)
				ret[i++] = cmd->cmds[0][2][x];
		}
		else if (cmd->is_redir[cmd_n][j] == 1)
		{	
			j = detect_flags(cmd, cmd_n, j);
			cmd_len = ft_strlen(cmd->cmds[cmd_n][j]);
			while (++x < cmd_len)
				ret[i++] = cmd->cmds[cmd_n][j][x];
			return (i);
		}
	}
	return (i);
}

char	*get_cmd_path(t_parser *cmd, int cmd_n)
{
	int		i;
	int		j;
	char	*res;
	char	ret[100];
	int		cmd_len;

	i = -1;
	j = -1;
	cmd_len = ft_strlen((char *)cmd->cmds[cmd_n][0]);
	i = copy_path(cmd, cmd_n, i, ret);
	if (get_redir(cmd, cmd_n, 0) == 0 || get_redir(cmd, cmd_n, 0) == 2)
		i = get_redir_to_execve(cmd, cmd_n, i, ret);
	else if (cmd->cmds[cmd_n][0][0] != '/')
		while (j < cmd_len)
			ret[i++] = cmd->cmds[cmd_n][0][++j];
	ret[i] = '\0';
	res = ret;
	return (res);
}

int	search_builtins(t_parser *cmd, int cmd_n)
{
	int		i;
	char	**cmds_list;

	i = 0;
	cmds_list = malloc(sizeof(char *) * 7);
	fill_builtin_mem(cmds_list);
	while (++i < 7)
	{
		if (ft_strcmp(cmd->cmds[cmd_n][0], cmds_list[i]) == 0)
		{
			if (get_redir(cmd, cmd_n, 0) > -1)
				redirections(cmd, cmd_n);
			execute_built_cmd(cmd, i, cmd_n);
			free(cmds_list);
			return (1);
		}
	}
	free(cmds_list);
	return (0);
}

int	built_cmds(t_parser *cmd, int cmd_n)
{	
	int	i;

	i = -1;
	while (++i <= cmd->count_token[cmd_n])
	{
		if (ft_strcmp(cmd->cmds[cmd_n][i], "echo") == 0)
		{
			if (create_process(cmd, cmd_n, 0))
				return (1);
		}
		else if (ft_strcmp(cmd->cmds[cmd_n][i], "env") == 0)
		{	
			if (create_process(cmd, cmd_n, 3))
				return (1);
		}
		else if (ft_strcmp(cmd->cmds[cmd_n][i], "pwd") == 0)
		{	
			if (create_process(cmd, cmd_n, 5))
				return (1);
		}
		else if (search_builtins(cmd, cmd_n))
			return (1);
	}
	return (0);
}

void	cmd_scanner(t_parser *cmd)
{
	int	pipe_cnt;
	int	i;
	int	cmd_n;

	i = -1;
	cmd_n = -1;
	pipe_cnt = search_pipes(cmd);
	while (++i <= cmd->count_cmd)
	{
		if (pipe_cnt > 0)
			pipeline(cmd, cmd_n, pipe_cnt);
		else if (ft_strcmp((char *)cmd->cmds[0][0], "") == 0)
			return ;
		else if (built_cmds(cmd, i))
			return ;
		else if (execute_cmds(cmd, i))
			return ;
		return ;
	}
}
