/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:19:21 by atoepper          #+#    #+#             */
/*   Updated: 2024/01/30 13:56:22 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*save_remainder(char *text_read)
{
	int		i;
	int		j;
	char	*remainder;

	i = 0;
	while (text_read[i] && text_read[i] != '\n')
		i++;
	if (!text_read[i])
	{
		free(text_read);
		return (NULL);
	}
	remainder = (char *)malloc(sizeof(char)
			* (ft_strlen(text_read) - i + 1));
	if (!remainder)
		return (NULL);
	i++;
	j = 0;
	while (text_read[i])
		remainder[j++] = text_read[i++];
	remainder[j] = '\0';
	free (text_read);
	return (remainder);
}

char	*extract_line(char *text_read)
{
	int		linelen;
	char	*line;

	if (!text_read[0])
		return (NULL);
	linelen = ft_linelen(text_read);
	if (ft_strchr(text_read, '\n'))
		line = (char *)malloc(sizeof(char) * (linelen + 2));
	else
		line = (char *)malloc(sizeof(char) * (linelen + 1));
	if (line == NULL)
		return (NULL);
	copy_line(line, text_read);
	return (line);
}

char	*add_new_line(int fd, char *text_read)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE +1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(text_read, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(text_read);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		text_read = ft_strjoin_gnl(text_read, buffer);
	}
	free (buffer);
	return (text_read);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*text_read[1024];

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	text_read[fd] = add_new_line(fd, text_read[fd]);
	if (!text_read[fd])
		return (NULL);
	line = extract_line(text_read[fd]);
	text_read[fd] = save_remainder(text_read[fd]);
	return (line);
}
