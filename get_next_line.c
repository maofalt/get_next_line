/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:10:47 by motero            #+#    #+#             */
/*   Updated: 2022/05/19 18:51:04 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUF_SIZE 500
#include <stdio.h>

void	*ft_memcpy(void * dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	while(n-- && (d || s))
		*d++ = *s++;
	return (dest);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t l_src;

	l_src = ft_strlen(src);
	if (l_src + 1 < size)
		ft_memcpy(dest, src, l_src + 1);
	else if (size != 0)
	{
		ft_memcpy(dest, src, size -1);
		dest[size - 1] = '\0';
	}
	return (l_src);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*cdest;
	const char	*csrc;

	if (!dest && !src)
		n =0;
	if (dest < src)
	{
		csrc = (const char *) src;
		cdest = (char *) dest;
		while (n--)
			*cdest++ = *csrc++;
	}
	else
	{
		csrc = (const char *) src + (n - 1);
		cdest = (char *) dest + (n  - 1);
		while (n --)
			*cdest-- = *csrc--;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*new_ptr;

	new_ptr = (char *)malloc ((ft_strlen(s) * sizeof(char)) + 1);
	if (!new_ptr)
		return (NULL);
	ft_memmove(new_ptr, s, ft_strlen(s) + 1);
	return (new_ptr);
}

size_t	ft_wlen(char const *s, char c)
{
	size_t	w_len;

	w_len = 0;
	while(*s && *s++ != c)
		w_len++;
	return (w_len);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	nbr_lines;
	size_t	w_len;
	size_t	i;

	if(!s)
		return (NULL);
	nbr_lines = ft_nbr_lines(s,c);
	split = (char **)malloc(sizeof(char *) * (nbr_lines + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (*s && i < nbr_lines)
	{
		w_len = 0;
		while (*s == c)
			s++;
		w_len = ft_wlen(s,c);
		split[i] = ft_substr(s, 0 , w_len);
		i++;
		s += w_len;
	}
	split[i] = 0;
	return (split);
}

char	*get_next_line(int fd)
{
	int					ret;
	static char			buf[BUF_SIZE + 1] = {0};
	char				*temp;
	char				**line;
	size_t				size_line;

	if (fd == -1)
		return (NULL);
	if (buf[0] = 0)
	{
		ret = read(fd, buf, BUF_SIZE);
		buf[ret] = 0;
	}
	temp = ft_strdup(buf);
	if ((ft_strchr(temp, '\n') ))
	{
		line = ft_split(buf, '\n');
		temp = ft_strchr(buf, '\n') + 1;
		return(line[0]);
	}
	else
	return (buf);
}

#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int	fd;
	char *line;
	int	nbr_line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening the file\n");
		return (1);
	}
	nbr_line = 1;
	while (nbr_line < 10)
	{
		line = get_next_line(fd);
		printf("|%i| %s \n", nbr_line++, line);
	}
	printf("File is done");
	return 0;
}
