/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:10:47 by motero            #+#    #+#             */
/*   Updated: 2022/05/18 19:31:26 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUF_SIZE 10

char	*get_next_line(int fd)
{
	static int		ret;
	char			*buf;
	
	if (fd == -1)
		return (NULL);
	buf = malloc(sizeof(char) * (BUF_SIZE + 1));
	ret = read(fd, buf, BUF_SIZE);
	buf[ret] = '\0';
	if (ft_strchr(buf, '\n'))
	//if found ft_split and send only first line
	else
		while ()
	// there i no \n in the files or EOF
	// save actual buffer in other one
	// read the document again from the last 
	// test again until /n and then sjoin
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
