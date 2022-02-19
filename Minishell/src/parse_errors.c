/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestevao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:17:23 by pestevao          #+#    #+#             */
/*   Updated: 2022/01/05 15:17:25 by pestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_error(t_parser *p)
{
	int	i;

	i = 0;
	while (i <= p->count_cmd)
	{
		if (ft_strlen(p->cmds[i][0]) == 0 && p->count_cmd > 0)
		{
			printf("Minishell: Syntax error - Pipe\n");
			g_v.last_exit = 258;
			return (1);
		}
		i++;
	}
	return (0);
}

int	valid_redir(t_parser *p, int i, int j)
{
	if (ft_strlen(p->cmds[i][j + 1]) == 0)
	{
		return (0);
	}
	if (ft_strcmp(p->cmds[i][j], ">") != 0
		&& ft_strcmp(p->cmds[i][j], ">>") != 0
		&& ft_strcmp(p->cmds[i][j], "<") != 0
		&& ft_strcmp(p->cmds[i][j], "<<") != 0)
	{
		return (0);
	}
	return (1);
}

int	redir_error(t_parser *p)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= p->count_cmd)
	{
		j = -1;
		while (++j <= p->count_token[i])
		{
			if (p->is_redir[i][j] == 1 && valid_redir(p, i, j) == 0)
			{
				printf("Minishell: Syntax error - Redirection\n");
				g_v.last_exit = 258;
				return (1);
			}
		}
	}
	return (0);
}

int	parse_errors(t_parser *p)
{
	if (pipe_error(p))
		return (1);
	if (redir_error(p))
		return (1);
	return (0);
}
