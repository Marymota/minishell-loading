/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmota <marmota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:01:15 by mmota             #+#    #+#             */
/*   Updated: 2022/02/18 12:06:23 by marmota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_error(void)
{
	if (errno == EACCES)
	{
		printf("Permission denied\n");
		exit(2);
	}
	else if (errno == ENOENT)
	{
		printf("Command not found\n");
		exit(127);
	}
	else
	{
		perror("execve");
		exit(errno);
	}
}

void	get_arr_to_execve(char *str[], t_parser *cmd, int cmd_n)
{
	int	i;
	int	j;
	int	redir;

	i = 0;
	j = 1;
	redir = get_redir(cmd, cmd_n, 0);
	if (redir > -1)
		redirections(cmd, cmd_n);
	while (++i <= cmd->count_token[cmd_n])
	{
		if (cmd->is_redir[cmd_n][i] == 1 || cmd->cmds[cmd_n][i][0] == '|')
			break ;
		if (cmd->is_redir[cmd_n][0] == 1 && i == 2)
			continue ;
		if (cmd->cmds[cmd_n][i][0] == '-'
			|| (ft_strlen(cmd->cmds[cmd_n][i]) != 0))
		{
			str[j] = cmd->cmds[cmd_n][i];
			j++;
		}
	}
	str[0] = get_cmd_path(cmd, cmd_n);
}

void	execute_pipes(t_parser *cmd, int cmd_n, int pipe_n, int *fd)
{
	char	*str[1000];
	int		i;

	i = -1;
	while (++i < 2 * pipe_n)
		close(fd[i]);
	if (built_cmds(cmd, cmd_n))
		exit(EXIT_SUCCESS);
	else
		get_arr_to_execve(str, cmd, cmd_n);
	if (execve(str[0], str, NULL) == -1)
		perror("execve");
}

int	execute_cmds(t_parser *cmd, int cmd_n)
{
	char	*str[100];
	int		status;
	pid_t	pid;

	pid = fork();
	g_v.sigprint = 0;
	if (pid == 0)
	{
		get_arr_to_execve(str, cmd, cmd_n);
		execve(str[0], str, 0);
		exec_error();
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	else
	{
		wait(&status);
		if (g_v.last_exit != 130)
			g_v.last_exit = WEXITSTATUS(status);
	}
	return (1);
}

void	execute_built_cmd(t_parser *cmd, int cmd_id, int cmd_n)
{	
	if (cmd_id == 0)
		parse_echo(cmd, cmd_n);
	else if (cmd_id == 1)
		run_cd(cmd, cmd_n);
	else if (cmd_id == 2)
		run_exit(cmd->cmds[cmd_n][0]);
	else if (cmd_id == 3)
		run_env();
	else if (cmd_id == 4)
		parse_export(cmd, cmd_n);
	else if (cmd_id == 5)
		run_pwd();
	else if (cmd_id == 6)
		parse_unset(cmd, cmd_n);
	else
		printf("Command not found\n");
	return ;
}
