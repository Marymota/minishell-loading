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

int	is_redirection(char c)
{
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	return (0);
}

void	write_char(t_parser *p, char c, int w)
{
	if (w != 0)
		p->cmds[p->count_cmd][p->count_token[p->count_cmd]][p->j] = c;
	p->j++;
	p->i++;
}

void	handle_quote(t_parser *p)
{
	if (p->open_quote == 0)
		p->open_quote = 1;
	else
		p->open_quote = 0;
	p->i++;
}

void	handle_apos(t_parser *p)
{
	if (p->open_apos == 0)
		p->open_apos = 1;
	else
		p->open_apos = 0;
	p->i++;
}

void	handle_pipe(t_parser *p, char *str, int w)
{
	if (p->count_cmd >= 9999)
		return ;
	if (p->j > 0)
		p->count_token[p->count_cmd]++;
	p->j = 0;
	write_char(p, str[p->i], w);
	p->count_cmd++;
	p->j = 0;
	while (str[p->i] == ' ')
		p->i++;
}
