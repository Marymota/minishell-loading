/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmota <marmota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:23:24 by pestevao          #+#    #+#             */
/*   Updated: 2022/01/13 23:13:46 by marmota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_memory(t_parser *p)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i <= p->count_cmd)
	{
		j = -1;
		while (++j <= p->count_token[i])
		{
			k = -1;
			while (++k < 9999)
			{
				p->cmds[i][j][k] = '\0';
			}
		}
	}
}

void	create_memory(t_parser *p)
{
	int	i;
	int	j;

	p->cmds = (char ***)malloc(sizeof(char **) * (p->count_cmd + 1));
	p->is_redir = (int **)malloc(sizeof(int **) * (p->count_cmd + 1));
	i = -1;
	while (++i <= p->count_cmd)
	{
		p->cmds[i] = (char **)malloc(sizeof(char *) * (p->count_token[i] + 1));
		p->is_redir[i] = (int *)malloc(sizeof(int *) * (p->count_token[i] + 1));
		j = -1;
		while (++j <= p->count_token[i])
		{
			p->is_redir[i][j] = 0;
			p->cmds[i][j] = (char *)malloc(sizeof(char) * 9999);
		}
	}
}

void	destroy_memory(t_parser *p)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= p->count_cmd)
	{
		j = -1;
		while (++j <= p->count_token[i])
		{
			free(p->cmds[i][j]);
		}
		free(p->cmds[i]);
		free(p->is_redir[i]);
	}
	free(p->cmds);
	free(p->is_redir);
}

void	init_struct(t_parser *p)
{
	int	i;

	p->i = 0;
	p->j = 0;
	p->count_cmd = 0;
	p->open_quote = 0;
	p->open_apos = 0;
	i = -1;
	while (++i < 9999)
	{
		p->count_token[i] = 0;
	}
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
