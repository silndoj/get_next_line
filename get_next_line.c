/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 03:31:23 by silndoj           #+#    #+#             */
/*   Updated: 2024/04/23 07:08:29 by silndoj          ###   ########.fr       */
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
		return (NULL);
	ft_memcpy(t1, s1, count + 1);
	return (t1);
}

char	*read_again(int fd, char *block)
{
	char	*block_temp;
	int		read_bytes;
	char	*temp;

	read_bytes = 0;
	while (!ft_strchr(block, '\n'))
	{
		block_temp = ft_calloc((BUFFER_SIZE), sizeof(char));
		if (!block_temp)
			return (free(block), block = NULL, NULL);
		read_bytes = read(fd, block_temp, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(block_temp), block_temp = NULL, NULL);
		if (!read_bytes)
		{
			free(block_temp);
			block_temp = NULL;
			break ;
		}
		temp = ft_strjoin(block, block_temp);
		free(block);
		block = temp;
		free(block_temp);
	}
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
		return (free(block), block = NULL, NULL);
	return (line);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	sublen;
	char	*ptr;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	sublen = slen - start;
	if (sublen > len)
		sublen = len;
	ptr = (char *) ft_calloc((sublen), sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, (s + start + 1), sublen);
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*block;
	char		*nextblock;
	char		*tmpblock;
	int			count;

	count = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &nextblock, 0) < 0)
		return (free(block), block = NULL, NULL);
	block = read_again(fd, block);
	if (!block)
		return (NULL);
	//nextblock = nextblock_reset(block, &count);
	while (block[count] != '\n')
		count++;
	nextblock = ft_substr(block, 0, count);
	if (ft_strlen(nextblock) == 0)
		return (free(nextblock), NULL);
	tmpblock = ft_substr(block, count, (ft_strlen(block) - count));
	free(block);
	block = tmpblock;
	return (nextblock);
}
//
//int main(void)
//{
//char	*line;
//int		i;
//int		fd1;
//int		fd2;
//int		fd3;
//fd1 = open("tests/test.txt", O_RDONLY);
//fd2 = open("tests/test2.txt", O_RDONLY);
//fd3 = open("tests/test3.txt", O_RDONLY);
//i = 1;
//while (i < 7)
//{
//	line = get_next_line(fd1);
//	printf("\nline [%02d]: %s", i, line);
//	free(line);
//	line = get_next_line(fd2);
//	printf("\nline(1) [%02d]: %s", i, line);
//	free(line);
//	line = get_next_line(fd3);
//	printf("\nline(2) [%02d]: %s", i, line);
//	free(line);
//	i++;
//}
//close(fd1);
//close(fd2);
//close(fd3);
//return (0);
//}
int main(void)
{
	int		fd,i;
	char	*line;
	i = 1;
	fd = open("variable_nls.txt", O_RDONLY | O_CREAT);
	while (i <= 13)
	{
		line = get_next_line(fd);
		if (i == 1)
			printf("line [%02d]: %s", i, line);
		else
			printf("\nline [%02d]: %s", i, line);
		free(line);
		i++;
	}
	free(line);
	close(fd);
	return (0);
}
