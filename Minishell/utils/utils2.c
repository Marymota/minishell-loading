/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pestevao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:32:49 by pestevao          #+#    #+#             */
/*   Updated: 2021/11/15 14:32:51 by pestevao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_substr_size(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	if (!s[0] || start > ft_strlen(s))
		return (0);
	i = 0;
	while (i < len && s[start + i] != 0)
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*substr;
	size_t			size;

	if (!s)
		return (NULL);
	size = ft_substr_size((char *) s, start, len);
	substr = (char *)malloc((size + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < size && s[start + i] != 0)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char) *(s1 + i) - (unsigned char) *(s2 + i));
		i++;
	}
	return ((unsigned char) *(s1 + i) - (unsigned char) *(s2 + i));
}

static int	ft_itoa_size(int n)
{
	int	i;

	i = 1;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*result;
	int				size;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = ft_itoa_size(n);
	result = (char *) malloc((size) * sizeof(char));
	if (result == NULL)
		return (NULL);
	size--;
	result[size] = '\0';
	if (n < 0)
	{
		n *= -1;
		result[0] = '-';
	}
	if (n == 0)
		result[0] = '0';
	while (size-- >= 0 && n > 0)
	{
		result[size] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}
