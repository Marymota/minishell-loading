/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestevao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:44:39 by pestevao          #+#    #+#             */
/*   Updated: 2022/02/10 17:44:40 by pestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_unset(char *str)
{
	char	tmp[9999];
	int		i;
	int		j;

	j = 0;
	while (++j < g_v.env_c)
	{
		i = -1;
		while (g_v.env[j][++i] && g_v.env[j][i] != '=' && i < 9998)
			tmp[i] = g_v.env[j][i];
		tmp[i] = '\0';
		if (ft_strcmp(str, tmp) == 0)
		{
			free(g_v.env[j]);
			while (j < g_v.env_c - 1)
			{
				g_v.env[j] = g_v.env[j + 1];
				j++;
			}
			g_v.env[j] = NULL;
			g_v.env_c--;
		}
	}
}

void	parse_unset(t_parser *cmd, int cmd_n)
{
	int	i;

	i = 0;
	if (cmd->count_token[cmd_n] > 0)
		while (++i <= cmd->count_token[cmd_n])
			run_unset(cmd->cmds[cmd_n][i]);
}
