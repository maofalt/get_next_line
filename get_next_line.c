/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:10:47 by motero            #+#    #+#             */
/*   Updated: 2022/05/17 18:02:54 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUF_SIZE 4096

char	*get_next_line(int fd)
{
	static int		ret;
	char	*buffer;
	char	buf[BUF_SIZE + 1];

	if (fd == -1)
		return (NULL);
	while (ret = read(fd, buf, BUF_SIZE ))
	{
		buf[ret] = '\0';
	}
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
	nbr_line = 0;
	while (line)
	{
		line = get_next_line(fd);
		printf("|%i| %s \n", nbr_line++, line);
	}
	printf("File is done");
	return 0;
}
