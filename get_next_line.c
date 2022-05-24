/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:10:47 by motero            #+#    #+#             */
/*   Updated: 2022/05/24 11:15:58 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_nxtbuf(char *past_buf, char *next_buf)
{
	char	*temp;

	temp = ft_strjoin(past_buf, next_buf);
	free(past_buf);
	return (temp);
}

char	*ft_free_line(char *save)
{
	int		line_len;
	int		i;
	char	*next_buffer;

	line_len = 0;
	while (save[line_len] && save[line_len] != '\n')
		line_len++;
	if (!save[line_len])
	{
		free(save);
		return (NULL);
	}
	next_buffer = calloc(ft_strlen(save) - line_len + 1, sizeof(char));
	line_len++;
	i = 0;
	while (save[line_len])
		next_buffer[i++] = save[line_len++];
	free(save);
	return (next_buffer);
}

char	*ft_extract_line(char *save)
{
	char	*line;
	char	*buf;
	int		line_len;

	line_len = 0;
	if (!save[line_len])
		return (NULL);
	while (save[line_len] && save[line_len] != '\n')
		line_len++;
	line = ft_calloc(line_len + 2, sizeof(char));
	if (!line)
		return (NULL);
	buf = line;
	while (line_len--)
		*buf++ = *save++;
	if (*save && *save == '\n')
		*buf++ = '\n';
	return (line);
}

//* 1- We calloc past_buf, only useful on the first use
// * 2- we initiliaze byte to 1, as we ensure to enter the main loop.
// * we read fd and save it to next_buf with BUF_SIZE and we verify that there 
// were no errors.
// * 3- We join the past_bufread with the next read
// * 4-  if a '\n' is found within te next buf, we interrupt the main loop 
// and we return the buf.*/

char	*ft_read_file(int fd, char *past_buf)
{
	char	*next_buf;
	int		byte;

	if (!past_buf)
		past_buf = ft_calloc(1, 1);
	next_buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte = 1;
	while (byte > 0)
	{
		byte = read(fd, next_buf, BUFFER_SIZE);
		if (byte == -1)
		{
			free(next_buf);
			return (NULL);
		}
		next_buf[byte] = 0;
		past_buf = ft_free_nxtbuf(past_buf, next_buf);
		if (ft_strchr(next_buf, '\n'))
			break ;
	}
	free(next_buf);
	return (past_buf);
}

///* 1- Verify if fd  is correct, buf_size is correct and read  is possible
// * 2- We use ft_read_file to read the file at least until there is a '\n', 
// insuring there is at least a line or EOF
// 3- we extract the first possible line or until EOF
// * 4-*/
char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
		return (NULL);
	save = ft_read_file(fd, save);
	if (!save)
		return (NULL);
	line = ft_extract_line(save);
	save = ft_free_line(save);
	return (line);
}

/*#include <sys/stat.h>
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
}*/
