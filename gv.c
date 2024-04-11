char	*ft_read(char *buffer, int fd)
{
	int		read_chars;
	char	*temp_buffer;

	temp_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (temp_buffer == NULL)
		return (NULL);
	read_chars = 1;
	while (read_chars != 0 && !ft_strchr(buffer))
	{
		read_chars = read(fd, temp_buffer, BUFFER_SIZE);
		if (read_chars == -1)
			return (free (temp_buffer), NULL);
		// if (temp_buffer == NULL)
		// 	break ;
		temp_buffer[read_chars] = '\0';
		buffer = ft_strjoin(buffer, temp_buffer);
		// printf("#####\n");
		// printf("%s\n", buffer);
		// printf("%s\n", temp_buffer);
		// printf("%d\n", ft_strchr(buffer));
		// printf("%d\n", read_chars);
	}
	free(temp_buffer);
	// temp_buffer = NULL;
	return (buffer);
}

char	*ft_clean(char *buffer)
{
	char	*clean;
	int		i;

	i = ft_strchr(buffer);
	clean = (char *)malloc(sizeof(char) * (i+1));
	if (!clean)
		return (NULL);
	ft_strlcpy(clean, buffer, i + 1);
	// printf("#####\n");
	// printf("%s\n", clean);
	return (clean);
}

char	*ft_final(char *buffer, char *line)
{
	char	*next;
	int		i;
	int		j;

	// if (!buffer)
	// 	return (NULL);
	i = ft_strlen(buffer);
	j = ft_strlen(line);
	// if (j == 0)
	// 	return (buffer);
	// else
	// {
		next = (char *)malloc(sizeof(char) * (i - j + 1));
		if (!next)
			return (NULL);
		ft_strlcpy(next, buffer + j, (i - j + 1));
		free(buffer);
		// printf("#####\n");
		// printf("%s\n", buffer);
	// }
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	// char		*tmp;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), NULL);
	buffer = ft_read(buffer, fd);
	if (!buffer)
		return (free(buffer), NULL);
	// if (ft_strchr(buffer) == 0)
	// 	//printf("#####\n");
	// 	return (buffer);
	line = ft_clean(buffer);
	// if (ft_strlen(line) == 0)
	// 	line = buffer;
	buffer = ft_final(buffer, line);
		// printf("%s\n", line);/
	return (line);
}

// char	*get_next_line(int fd)
// {
// 	static char	*buffer;
// 	char		*line;
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (free(buffer), NULL);
// 	buffer = ft_read(buffer, fd);
// 	if (!buffer)
// 		return (free(buffer), NULL);
// 	line = ft_clean(buffer);
// 	if (ft_strlen(line) == 0)
// 		return (buffer);
// 	buffer = ft_final(buffer, line);
// 	return (line);
// }

 int	main()
 {
 	int		fd;
 	char	*next_line;
 	int		count;

 	count = 0;
 	fd = open("example.txt", O_RDONLY);
 	while (count != 5)
 	{
 		// printf("#!!!########\n");
 		next_line = get_next_line(fd);
 		// printf("#########");
 		// if (next_line == NULL)
 		// 	break;
 		count++;
 		// printf("@!###########\n");
 		printf("[%d]:%s", count, next_line);
 		free(next_line);
 		next_line = NULL;
 	}
   	close(fd);
 	return (0);
 }

 #include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	if (s[i] == '\n')
		return (i + 1);
	return (0);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen((char *)src);
	if (dstsize && dst)
	{
		while (i < dstsize - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (j);
}

// void	ft_strcpy(char *dst, char *src)
// {
// 	int	i;

// 	i = 0;
// 	while (src[i])
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// }

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		// if (!s1)
		// 	return (NULL);
		s1[0] = '\0';
	}
	// if (!s1)
	// 	return (s2);
	// if (!s2)
	// 	return (s1);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, ft_strlen(s1) + 1);
	ft_strlcpy(ptr + ft_strlen(s1), s2, (ft_strlen(s2) + 1));
	// ft_strcpy(ptr, s1);
	// ft_strcpy(ptr + ft_strlen(s1), s2);
	ptr[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (ptr);