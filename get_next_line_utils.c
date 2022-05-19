/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:10:58 by motero            #+#    #+#             */
/*   Updated: 2022/05/19 18:51:46 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_nbr_lines(char const *s)
{
	size_t	nbr_words;

	nbr_words = 0;
	while(*s)
	{
		if(*s == c)
			s++;
		else
		{
			while (*s != c && *s)
				s++;
			nbr_words++;
		}
	}
	return (nbr_words);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	idx;
	char			*modified_s;

	if (!s || !(modified_s = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	idx = 0;
	while (start < ft_strlen((char *)s) && s[start + idx] && idx < len)
	{
		modified_s[idx] = s[start + idx];
		idx++;
	}
	modified_s[idx] = '\0';
	return (modified_s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*new_s;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	new_s = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_s || (s1 == NULL && s2 == NULL))
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		new_s[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		new_s[i + j] = s2[j];
		j++;
	}
	new_s[i + j] = '\0';
	return (new_s);
}

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	char	*s_cpy;
	size_t	s_len;
	int		c_256;

	c_256 = c % 256;
	s_cpy = (char *)s;
	s_len = ft_strlen(s);
	if (c_256 == '\0')
		return (s_cpy + s_len);
	else
	{
		s_len = 0;
		while (s_cpy[s_len])
		{
			if (s_cpy[s_len++] == c_256)
				return ((char *)s_cpy + (--s_len));
		}
		return (NULL);
	}
}
