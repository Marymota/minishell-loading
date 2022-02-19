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

void	handle_redirection(t_parser *p, char *str, int w)
{
	if (p->j > 0)
		p->count_token[p->count_cmd]++;
	p->j = 0;
	while (str[p->i] == '<' || str[p->i] == '>')
		write_char(p, str[p->i], w);
	if (w)
		p->is_redir[p->count_cmd][p->count_token[p->count_cmd]] = 1;
	p->count_token[p->count_cmd]++;
	p->j = 0;
	while (str[p->i] == ' ')
		p->i++;
}

void	handle_space(t_parser *p, char *str)
{
	while (str[p->i] == ' ')
		p->i++;
	if (str[p->i] != '\0' && str[p->i] != '|')
	{
		p->count_token[p->count_cmd]++;
		p->j = 0;
	}
}

char	*parser_getenv(char *env)
{
	char	tmp[9999];
	char	*r;
	int		i;
	int		j;
	int		k;

	j = 0;
	r = (char *)malloc(sizeof(char) * 9999);
	while (++j < g_v.env_c)
	{
		i = -1;
		while (g_v.env[j][++i] && g_v.env[j][i] != '=' && i < 9998)
			tmp[i] = g_v.env[j][i];
		tmp[i] = '\0';
		if (ft_strcmp(env, tmp) == 0)
		{
			k = -1;
			while (g_v.env[j][++i])
				r[++k] = g_v.env[j][i];
		}
	}
	return (r);
}

void	clean_replace(char *replace)
{
	int	i;

	i = -1;
	while (++i < 9999)
	{
		replace[i] = '\0';
	}
	free(replace);
}

void	handle_env(t_parser *p, char *str)
{
	char	env[9999];
	char	*replace;
	int		i;

	i = 0;
	while (ft_isalpha(str[p->i]))
	{
		env[i] = str[p->i];
		i++;
		p->i++;
	}
	env[i] = '\0';
	replace = parser_getenv(env);
	i = 0;
	while (replace != NULL && replace[i] != '\0')
	{
		p->cmds[p->count_cmd][p->count_token[p->count_cmd]][p->j] = replace[i];
		p->j++;
		i++;
	}
	clean_replace(replace);
}
