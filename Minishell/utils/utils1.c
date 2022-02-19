/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmota <mmota@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:16:56 by pestevao          #+#    #+#             */
/*   Updated: 2022/02/12 16:26:09 by mmota            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;

	i = 0;
	while (s1[i] != '\0')
		i++;
	s2 = malloc(sizeof(char) * i + 1);
	if (s2 == 0)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int	detect_flags(t_parser *cmd, int cmd_n, int i)
{
	while (cmd->cmds[cmd_n][--i][0] == '-')
		continue ;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	char	*ret;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return (ft_strdup(""));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!join)
		return (0);
	ret = join;
	while (len1--)
		*join++ = *s1++;
	while (len2--)
		*join++ = *s2++;
	*join = '\0';
	return (ret);
}
