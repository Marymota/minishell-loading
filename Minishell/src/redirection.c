/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmota <mmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:10:46 by mmota             #+#    #+#             */
/*   Updated: 2022/02/14 18:46:53 by mmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_redir(t_parser *cmd, int cmd_n, int flag)
{
	int	i;

	i = flag;
	while (i <= cmd->count_token[cmd_n])
	{
		if (cmd->is_redir[cmd_n][i] == 0)
		{
			i++;
			continue ;
		}
		if (ft_strcmp(cmd->cmds[cmd_n][i], "<") == 0)
			return (0);
		else if (ft_strcmp(cmd->cmds[cmd_n][i], ">") == 0)
			return (1);
		else if (ft_strcmp(cmd->cmds[cmd_n][i], "<<") == 0)
			return (2);
		else if (ft_strcmp(cmd->cmds[cmd_n][i], ">>") == 0)
			return (3);
		++i;
	}
	return (-1);
}

void	redir_input(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
	}
}

void	redir_output(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
	}
}

int	exec_heredoc(char *eof)
{
	char	*tmp;
	char	*file;
	int		fd;

	file = "heredoc";
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
			exit(EXIT_FAILURE);
		if (ft_strcmp(tmp, eof) == 0)
			break ;
		write(fd, tmp, ft_strlen(tmp));
		write(fd, "\n", 1);
	}
	signal(SIGINT, handle_signal);
	close(fd);
	fd = open(file, O_RDONLY, 0644);
	unlink(file);
	return (fd);
}

void	redirections(t_parser *cmd, int cmd_n)
{
	int		i;
	char	*file;
	int		fd;

	i = -1;
	while (++i < cmd->count_token[cmd_n])
	{
		file = get_filename(cmd, cmd_n, i + 1);
		if (ft_strcmp(cmd->cmds[cmd_n][i], "<") == 0)
			fd = open(file, O_RDONLY, 0644);
		else if (ft_strcmp(cmd->cmds[cmd_n][i], ">") == 0)
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (ft_strcmp(cmd->cmds[cmd_n][i], ">>") == 0)
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (ft_strcmp(cmd->cmds[cmd_n][i], "<<") == 0)
			fd = exec_heredoc((char *)cmd->cmds[cmd_n][i + 1]);
		if (do_not_redir(cmd, cmd_n) == 1)
			continue ;
		if (cmd->cmds[cmd_n][i][0] == '>')
			redir_output(fd);
		if (cmd->cmds[cmd_n][i][0] == '<')
			redir_input(fd);
	}
	close(fd);
}
