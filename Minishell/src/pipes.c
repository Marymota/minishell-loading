/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmota <mmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:03:44 by marmota           #+#    #+#             */
/*   Updated: 2022/02/10 22:26:28 by mmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_pipes(t_parser *cmd)
{
	int	i;
	int	j;
	int	pipe_count;

	i = -1;
	pipe_count = 0;
	while (++i <= cmd->count_cmd)
	{
		j = 0;
		while (++j <= cmd->count_token[i])
		{
			if (ft_strcmp(cmd->cmds[i][j], "|") == 0)
				pipe_count++;
		}
	}
	return (pipe_count);
}

void	close_fds(int pipe_n, int *fd)
{
	int	i;
	int	status;

	i = -1;
	while (++i < 2 * pipe_n)
		close(fd[i]);
	i = -1;
	while (++i < pipe_n + 1)
		wait(&status);
	g_v.last_exit = WEXITSTATUS(status);
}

int	*create_pipes(int *fd, int pipe_n)
{
	int	i;
	int	status;

	i = -1;
	while (++i < pipe_n)
		if (pipe(fd + i * 2) < 0)
			exec_error();
	wait(&status);
	g_v.last_exit = WEXITSTATUS(status);
	return (fd);
}

void	redir_pipes(int *fd, int i, int redir)
{
	int	status;

	if (redir == 0 || redir == 2)
	{
		if (dup2(fd[i + 1], STDOUT_FILENO) < 0)
			exec_error();
	}
	else if (redir == 1 || redir == 3)
	{
		if (dup2(fd[i - 2], 0) < 0)
			exec_error();
	}		
	wait(&status);
	g_v.last_exit = WEXITSTATUS(status);
}

void	pipeline(t_parser *cmd, int cmd_n, int pipe_n)
{
	pid_t	pid;
	int		*fd;
	int		i;

	fd = malloc(pipe_n * 2 * sizeof(int *));
	fd = create_pipes(fd, pipe_n);
	i = 0;
	while (++cmd_n <= pipe_n && cmd_n <= cmd->count_cmd)
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmd->cmds[cmd_n + 1])
				redir_pipes(fd, i, 0);
			if (i != 0)
				redir_pipes(fd, i, 1);
			execute_pipes(cmd, cmd_n, pipe_n, fd);
		}
		else if (pid < 0)
			exec_error();
		i += 2;
	}
	close_fds(pipe_n, fd);
}
