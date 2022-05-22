/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:10:47 by motero            #+#    #+#             */
/*   Updated: 2022/05/22 17:50:41 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUF_SIZE 5
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

size_t	ft_linelen(char const *s)
{
	size_t	l_len;

	l_len = 0;
	while(*s)
	{
		if (*s++ == '\n')
		{
			l_len++;
			break;
		}
		l_len++;
	}
	return (l_len);
}

char	*ft_split(char const *s)
{
	char	*split;
	size_t	len_line;
	
	if(!s)
		return (NULL);
	len_line = 0;
	len_line = ft_linelen(s);
	split = ft_substr(s, 0 , len_line);
	s += len_line;
	split[len_line] = 0;
	return (split);
}

char	*get_next_line(int fd)
{
	int					ret;
	static char			buf[BUF_SIZE + 1] = {0};
	char				*temp;
	char				*line;

	if (fd == -1 || BUF_SIZE == 0 || (read(fd, buf, BUF_SIZE) < 0))
		return (NULL);
	if ((buf[0] == 0))
	{
		ret = read(fd, buf, BUF_SIZE);
		buf[ret] = 0;
	}
	temp = ft_strdup(buf);
	while (!(ft_strchr(temp, '\n')))
	{
		line = ft_split(buf);
		temp = ft_strchr(buf, '\n') + 1 ;
		ft_memcpy(buf, temp, ft_strlen(temp) + 1);
	}
	return (line);
}

#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int	fd;
	char *line;
	int	nbr_line;

	fd = open("test", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening the file\n");
		return (1);
	}
	nbr_line = 1;
	line = get_next_line(fd);
	while (nbr_line <= 13)
	{
		printf("|%i| %s", nbr_line++, line);
		line = get_next_line(fd);
	}
	printf("File is done");
	return 0;
}
