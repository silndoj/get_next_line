/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 03:31:23 by silndoj           #+#    #+#             */
/*   Updated: 2024/04/22 18:13:14 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1, int count)
{
	char	*t1;
	size_t	slen;

	slen = ft_strlen(s1);
	t1 = (char *) ft_calloc((slen + 1), sizeof(char));
	if (!t1)
		return (0);
	ft_memcpy(t1, s1, count + 1);
	return (t1);
}

char	*read_again(int fd, char *block)
{
	char	*block_temp;
	int		read_bytes;

	read_bytes = 0;
	while (!ft_strchr(block, '\n') && read_bytes >= 0)
	{
		block_temp = ft_calloc(BUFFER_SIZE, sizeof(char));
		if (!block_temp)
			return (NULL);
		read_bytes = read(fd, block_temp, BUFFER_SIZE);
		if (read_bytes == -1 || read_bytes == 0)
		{
			free(block_temp);
			return (NULL);
		}
		block = ft_strjoin(block, block_temp);
	}
	free(block_temp);
	block_temp = NULL;
	return (block);
}

char	*nextblock_reset(char *block, int *count)
{
	int		i;
	char	*line;

	i = 0;
	while (block[i] != '\0' && block[i] != '\n')
		i++;
	*count = i;
	line = ft_strdup(block, i);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	sublen;
	char	*ptr;
	char	*temp;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	sublen = slen - start;
	if (sublen > len)
		sublen = len;
	ptr = (char *) ft_calloc((sublen + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, (s + start + 1), sublen);
	temp = ft_strdup(ptr, ft_strlen(ptr));
	if (!temp)
		return (NULL);
	free(ptr);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*block;
	static char *temp;
	char		*nextblock;
	int			count;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	count = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (temp != NULL)
	{
		block = ft_strdup(temp, ft_strlen(temp));
		free(temp);
	}
	block = read_again(fd, block);
	if (!block)
		return (NULL);
	nextblock = nextblock_reset(block, &count);
	block = ft_substr(block, count, (ft_strlen(block) - count));
	if (block != NULL)
	{
		temp = ft_strdup(block, ft_strlen(block));
		free(block);
	}
//	if (ft_strlen(block) == 0)
//	{
//		free(block);
//		block = NULL;
//	}
	return (nextblock);
}

int main(void)
{
char	*line;
int		i;
int		fd1;
//int		fd2;
//int		fd3;
fd1 = open("tests/test.txt", O_RDONLY);
//fd2 = open("tests/test2.txt", O_RDONLY);
//fd3 = open("tests/test3.txt", O_RDONLY);
i = 1;
while (i < 7)
{
	line = get_next_line(fd1);
	printf("line [%02d]: %s", i, line);
	free(line);
//	line = get_next_line(fd2);
//	printf("line [%02d]: %s", i, line);
//	free(line);
//	line = get_next_line(fd3);
//	printf("line [%02d]: %s", i, line);
//	free(line);
	i++;
}
close(fd1);
//close(fd2);
//close(fd3);
return (0);
}
//int main(void)
//{
//	int		fd,i;
//	char	*line;
//	i = 0;
//	fd = open("example.txt", O_RDONLY | O_CREAT);
//	while (i < 16)
//	{
//		line = get_next_line(fd);
//		printf("line: %s", line);
//		free(line);
//		i++;
//	}
//	close(fd);
//	return (0);
//}
