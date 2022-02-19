/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmota <mmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:23:24 by pestevao          #+#    #+#             */
/*   Updated: 2022/02/14 18:53:29 by mmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_exit(t_parser *p)
{
	char	*replace;
	int		i;

	p->i++;
	replace = ft_itoa(g_v.last_exit);
	i = 0;
	while (replace != NULL && replace[i] != '\0')
	{
		p->cmds[p->count_cmd][p->count_token[p->count_cmd]][p->j] = replace[i];
		p->j++;
		i++;
	}
	free(replace);
}

void	handle_dollar(t_parser *p, char *str)
{
	p->i++;
	if (str[p->i] == '?')
	{
		handle_exit(p);
	}
	else if (ft_isalpha(str[p->i]))
	{
		handle_env(p, str);
	}
	else
	{
		p->cmds[p->count_cmd][p->count_token[p->count_cmd]][p->j] = '$';
		p->j++;
	}
}

void	print_matrix(t_parser *p)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= p->count_cmd)
	{
		j = -1;
		while (++j <= p->count_token[i])
		{
			printf("Cmd %d - Token %d: %s - Redir: %d\n", i, j,
				p->cmds[i][j], p->is_redir[i][j]);
		}
	}
}

void	parse_cmds(char *str, t_parser *p)
{
	create_memory(p);
	fill_memory(p);
	init_struct(p);
	while (str[p->i] != '\0')
	{
		if (str[p->i] == '"' && p->open_apos == 0)
			handle_quote(p);
		else if (str[p->i] == '\'' && p->open_quote == 0)
			handle_apos(p);
		else if (str[p->i] == ' ' && p->open_apos == 0 && p->open_quote == 0)
			handle_space(p, str);
		else if (str[p->i] == '$' && p->open_apos == 0)
			handle_dollar(p, str);
		else if (str[p->i] == '|' && p->open_apos == 0 && p->open_quote == 0)
			handle_pipe(p, str, 1);
		else if (is_redirection(str[p->i]) && p->open_apos == 0
			&& p->open_quote == 0)
			handle_redirection(p, str, 1);
		else
			write_char(p, str[p->i], 1);
	}
	if (parse_errors(p) == 0)
		cmd_scanner(p);
	destroy_memory(p);
}

void	count_cmds(char *str)
{
	t_parser	p;

	init_struct(&p);
	while (str[p.i] != '\0' && p.count_cmd < 9999)
	{
		if (str[p.i] == '"' && p.open_apos == 0)
			handle_quote(&p);
		else if (str[p.i] == '\'' && p.open_quote == 0)
			handle_apos(&p);
		else if (str[p.i] == ' ' && p.open_apos == 0 && p.open_quote == 0)
			handle_space(&p, str);
		else if (str[p.i] == '|' && p.open_apos == 0 && p.open_quote == 0)
			handle_pipe(&p, str, 0);
		else if (is_redirection(str[p.i]) && p.open_apos == 0
			&& p.open_quote == 0)
			handle_redirection(&p, str, 0);
		else
			write_char(&p, str[p.i], 0);
	}
	if (p.count_cmd >= 9999)
	{
		printf("Too many commands!\n");
		return ;
	}
	parse_cmds(str, &p);
}
