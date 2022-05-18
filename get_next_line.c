/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:10:47 by motero            #+#    #+#             */
/*   Updated: 2022/05/18 13:19:54 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUF_SIZE 4096

char	*get_next_line(int fd)
{
	static int		ret;
	char			test[BUF_SIZE +1];
	char			*buf;
	int				line_size;
	
	if (fd == -1)
		return (NULL);
	line_size = 1;
	ret = read(fd, test, line_size);
	test[ret] = 0;
	while (test[line_size - 1] != '\n')
		read(fd, test, line_size++);
	buf = malloc(sizeof(char) * (line_size + 1));
	ret = read(fd, buf, BUF_SIZE);
	buf[ret] = '\0';
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
	line = get_next_line(fd);
	printf("|%i| %s \n", nbr_line++, line);
	printf("File is done");
	return 0;
}
