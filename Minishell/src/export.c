/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestevao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:42:02 by pestevao          #+#    #+#             */
/*   Updated: 2022/02/10 17:42:03 by pestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_export(void)
{
	int	i;
	int	j;

	i = -1;
	while (g_v.env[++i])
	{
		printf("declare -x ");
		j = -1;
		while (g_v.env[i][++j] != '=' && j < 9999)
			printf("%c", g_v.env[i][j]);
		printf("=\"");
		while (g_v.env[i][++j] != '\0' && j < 9999)
			printf("%c", g_v.env[i][j]);
		printf("\"\n");
	}
}

void	fork_export(t_parser *cmd, int cmd_n)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (get_redir(cmd, cmd_n, 0) > -1)
			redirections(cmd, cmd_n);
		run_export();
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
		exec_error();
	wait(&status);
}

int	export_duplicate(char *str)
{
	char	tmp1[9999];
	char	tmp2[9999];
	int		i;
	int		j;

	i = -1;
	while (str[++i] && str[i] != '=')
		tmp1[i] = str[i];
	tmp1[i] = '\0';
	j = -1;
	while (++j < g_v.env_c)
	{
		i = -1;
		while (g_v.env[j][++i] && g_v.env[j][i] != '=' && i < 9998)
			tmp2[i] = g_v.env[j][i];
		tmp2[i] = '\0';
		if (ft_strcmp(tmp1, tmp2) == 0)
			return (j);
	}
	return (-1);
}

void	export_set_env(char *str)
{
	int	i;
	int	add;
	int	replace;

	i = -1;
	add = 0;
	while (str[++i])
		if (str[i] == '=')
			add = 1;
	replace = export_duplicate(str);
	if (replace > -1 && add)
	{
		free(g_v.env[replace]);
		g_v.env[replace] = ft_strdup(str);
	}
	else if (add)
	{
		g_v.env[g_v.env_c] = ft_strdup(str);
		g_v.env_c++;
	}
}

void	parse_export(t_parser *cmd, int cmd_n)
{
	int	i;

	i = 0;
	if (cmd->count_token[cmd_n] == 0)
		fork_export(cmd, cmd_n);
	else if (cmd->count_token[cmd_n] > 0)
	{
		while (++i <= cmd->count_token[cmd_n])
		{
			if (g_v.env_c < 9999)
				export_set_env(cmd->cmds[cmd_n][i]);
			else
				printf("Env limit reached!");
		}
	}
}
