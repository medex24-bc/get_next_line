/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrharoui <mrharoui@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 08:51:21 by mrharoui          #+#    #+#             */
/*   Updated: 2025/02/08 09:11:51 by mrharoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_extract(char *tmp)
{
	char	*keep_tmp;

	keep_tmp = ft_strdup(ft_strchr(tmp, '\n') + 1);
	free(tmp);
	tmp = keep_tmp;
	return (tmp);
}

char	*ft_strchr(char *s, int c)
{
	if (!s && c != '\0')
		return (0);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_free(char **tmp, char **buff, ssize_t b, char *str)
{
	if (*tmp && **tmp && b == 0)
	{
		str = ft_strdup(*tmp);
		free(*tmp);
		*tmp = NULL;
		free(*buff);
		*buff = NULL;
		return (str);
	}
	if (ft_strchr(*tmp, '\n') != NULL)
	{
		str = ft_substr(*tmp, 0, (ft_strlen(*tmp)
					- ft_strlen(ft_strchr(*tmp, '\n'))) + 1);
		*tmp = ft_extract(*tmp);
		return (str);
	}
	free(*tmp);
	*tmp = NULL;
	free(*buff);
	*buff = NULL;
	return (NULL);
}

char	*ft_verify(char *tmp, char *buff, int read_bytes)
{
	char	*ptr_free;
	size_t	len;

	ptr_free = NULL;
	buff[read_bytes] = '\0';
	if (tmp)
	{
		ptr_free = ft_strdup(tmp);
		free(tmp);
		len = ft_strlen(ptr_free) + ft_strlen(buff);
		tmp = (char *)malloc((sizeof(char) * len) + 1);
		if (tmp == NULL)
			return (NULL);
		ft_memcpy(tmp, ptr_free, ft_strlen(ptr_free) + 1);
		tmp[ft_strlen(ptr_free)] = '\0';
		ft_memcpy(ft_strchr(tmp, '\0'), buff, ft_strlen(buff));
		tmp[len] = '\0';
		free(ptr_free);
	}
	else if (!tmp)
	{
		free(tmp);
		tmp = ft_strdup(buff);
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*tmp[MAX_FD];
	char		*buff;
	char		*final_string;
	ssize_t		read_bytes;

	final_string = NULL;
	buff = NULL;
	read_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	while (read_bytes != 0 && fd < MAX_FD)
	{
		if ((ft_strchr(tmp[fd], '\n') != NULL))
			return (ft_free(&tmp[fd], &buff, read_bytes, final_string));
		buff = (char *)malloc(BUFFER_SIZE + 1);
		if (buff == NULL)
			return (NULL);
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		tmp[fd] = ft_verify(tmp[fd], buff, read_bytes);
		free(buff);
		buff = NULL;
	}
	return (ft_free(&tmp[fd], &buff, read_bytes, final_string));
}

/*int main(void)
{
    int	fd1 = 0;
	int fd2 = 0;
	int fd3 = 0;
	char *string = NULL;

    fd1 = open("./files/file1.txt", O_RDONLY);
	fd2 = open("./files/file3.txt", O_RDONLY);
	fd3 = open("./files/file4.txt", O_RDONLY);

	if (fd1 != -1)
	{
		string = get_next_line(fd1);
		printf("%s", string);
	}
	if (fd2 != -1)
	{
		string = get_next_line(fd2);
		printf("%s", string);
	}
	if (fd3 != -1)
	{
		string = get_next_line(fd3);
		printf("%s", string);
	}

/// DEUXIEME FOIS

	if (fd1 != -1)
	{
		string = get_next_line(fd1);
		printf("%s", string);
	}
	if (fd2 != -1)
	{
		string = get_next_line(fd2);
		printf("%s", string);
	}
	if (fd3 != -1)
	{
		string = get_next_line(fd3);
		printf("%s", string);
	}
	else
	{
		printf("Erreur d'ouverture du fichier\n");
        return (1);
	}
	return (0);
}*/
