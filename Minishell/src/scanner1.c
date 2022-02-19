/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmota <mmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:15:35 by mmota             #+#    #+#             */
/*   Updated: 2022/02/14 20:08:56 by mmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_cmd_token(t_parser *cmd, int cmd_n)
{	
	int		redir;
	int		j;

	j = -1;
	redir = get_redir(cmd, cmd_n, 0);
	if (redir == 0 || redir == 2)
	{
		while (++j <= cmd->count_token[cmd_n])
		{
			if (cmd->is_redir[cmd_n][j] == 1)
			{	
				if (cmd->is_redir[0][0] == 1)
					return (2);
				while (cmd->cmds[cmd_n][j - 1][0] == '-')
						j--;
				return (j - 1);
			}
		}
	}
	return (0);
}

int	copy_path(t_parser *cmd, int cmd_n, int i, char *ret)
{
	int		cmd_len;
	char	*path;
	int		token;

	token = get_cmd_token(cmd, cmd_n);
	path = search_path(cmd, cmd_n, token, 0);
	cmd_len = ft_strlen((char *)cmd->cmds[cmd_n][0]);
	if (cmd->cmds[cmd_n][0][0] == '/')
		while (++i < cmd_len)
			ret[i] = cmd->cmds[cmd_n][0][i];
	else
		while (path[++i])
			ret[i] = path[i];
	return (i);
}

char	*search_path(t_parser *cmd, int cmd_n, int token, int x)
{
	int		j;
	char	*env;
	char	list_paths[10][50];

	env = getenv("PATH");
	j = 0;
	while (env && *env)
	{
		if (*env != ':')
			list_paths[j][x++] = *env;
		else if (*env == ':')
		{
			list_paths[j][x++] = '/';
			list_paths[j++][x] = '\0';
			x = 0;
		}
		env++;
	}
	list_paths[j][x] = '/';
	list_paths[j][++x] = '\0';
	while (--j)
		if (list_files(cmd, cmd_n, token, list_paths[j]))
			env = list_paths[j];
	return (env);
}

int	list_files(t_parser *cmd, int cmd_n, int token, char *path)
{
	struct dirent	*dp;
	DIR				*dir;

	dir = opendir(path);
	if (!dir)
	{
		printf("dir error\n");
		exit(EXIT_FAILURE);
	}
	dp = readdir(dir);
	while (dp != NULL)
	{
		if (ft_strcmp(dp->d_name, cmd->cmds[cmd_n][token]) == 0)
		{
			closedir(dir);
			return (1);
		}
		dp = readdir(dir);
	}
	closedir(dir);
	return (0);
}

int	create_process(t_parser *cmd, int cmd_n, int j)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (get_redir(cmd, cmd_n, 0) > -1)
			redirections(cmd, cmd_n);
		execute_built_cmd(cmd, j, cmd_n);
		exit(0);
	}
	else if (pid < 0)
		exec_error();
	wait(&status);
	g_v.last_exit = WEXITSTATUS(status);
	return (1);
}
