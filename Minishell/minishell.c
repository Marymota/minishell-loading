/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmota <marmota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:54:03 by pestevao          #+#    #+#             */
/*   Updated: 2022/02/18 13:30:53 by marmota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	If there is more than one argument return the same error as in bash 
	(Minishell: <second argument>: No such file or directory)

	STTY SETTINGS	->	signals.c
	SIGNAL SETTINGS ->	signals.c
	copy_env		->	copies all the variables in envp so that we can 
						implement or own export, unset and env as builtins
	rl_outstream	->	all error messages are sent to stderr
	readline 		->	creates a prompt and keeps the data introduced
	cmd_history		->	keeps track of later inputs to the minishell
	count_cmds		->	parser.c
*/
#include "minishell.h"

void	cmd_history(char *cmd)
{
	int	str_size;

	str_size = ft_strlen(cmd);
	if (str_size > 0)
	{
		if (cmd[str_size - 1] == ' ')
		{
			cmd = ft_strcat(cmd, " ");
		}
		if (cmd && *cmd)
			add_history(cmd);
	}
}

void	copy_env(char *envp[])
{
	int	i;

	g_v.env_c = 0;
	i = -1;
	while (envp[++i] != NULL)
	{
		g_v.env[i] = ft_strdup(envp[i]);
		g_v.env_c++;
	}
}

void	free_env(void)
{
	int	i;

	i = -1;
	while (++i < g_v.env_c)
		free(g_v.env[i]);
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*cmd;

	if (argc != 1)
	{
		printf("Minishell: %s: %s\n", argv[1], strerror(2));
		exit(127);
	}
	setup_stty();
	setup_sig();
	copy_env(envp);
	rl_outstream = stderr;
	while (1)
	{
		g_v.sigprint = 1;
		cmd = readline("Minishell$> ");
		if (!cmd)
			exit(EXIT_FAILURE);
		cmd_history(cmd);
		count_cmds(cmd);
	}
	free_env();
	return (1);
}
