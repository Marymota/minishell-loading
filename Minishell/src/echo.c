/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmota <mmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:58:13 by pestevao          #+#    #+#             */
/*   Updated: 2022/02/12 18:09:46 by mmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	@27 added to avoid printing repetive "-n" (echo -n -n -n -> "-na")
//	@32 changed because it added a space after pipeline 
//		output (echo a | echo b -> " b")
//	@44 changed to avoid using global variables; 
//		probably unecessary and difficult to justify during the presentation
#include "../minishell.h"

void	run_echo(int n, t_parser *cmd, int cmd_n)
{
	int	i;

	i = 0 + (n != 0);
	while (++i < cmd->count_token[cmd_n] + 1)
	{
		if (cmd->is_redir[cmd_n][i] == 1)
			break ;
		while (ft_strcmp(cmd->cmds[cmd_n][i], "-n") == 0)
			++i;
		if (cmd->cmds[cmd_n][i] != NULL)
		{
			printf("%s", cmd->cmds[cmd_n][i]);
			if (i != cmd->count_token[cmd_n])
				printf(" ");
		}
	}
	if (n == 0)
		printf("\n");
}

void	parse_echo( t_parser *cmd, int cmd_n)
{
	if (cmd->count_token[cmd_n] == 0)
		printf("\n");
	else if (ft_strcmp(cmd->cmds[cmd_n][1], "-n") == 0)
		run_echo(1, cmd, cmd_n);
	else
		run_echo(0, cmd, cmd_n);
}
