/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_read_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:55:26 by jweingar          #+#    #+#             */
/*   Updated: 2024/09/03 11:06:34 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	redirection_test(char *input, char *output, int out_typ)
{
	int		fd_input;
	int		fd_output;
	char	buf[2];
	int		count_read;
	int		count_write;

	(void)out_typ;
	buf[1] = '\0';
	if (ft_strncmp(input, output, ft_strlen(input)) == 0)
		return (perror("input file is output file"), 1);
	fd_input = open(input, O_RDONLY, 0644);
	if (fd_input == -1)
		return (perror("open"), 1);
	if (out_typ == 0)
		fd_output = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (out_typ == 1)
		fd_output = open(output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return(printf("wrong out_typ\n"), close(fd_input), 1);	
	count_read = read(fd_input, buf, 1);
	printf("count: %i, buf: %s\n", count_read, buf);
	while (count_read == 1)
	{
		count_write = write(fd_output, buf, 1);
		printf("write: %s, %i\n", buf, count_write);
		count_read = read(fd_input, buf, 1);
	}
	close(fd_input);
	close(fd_output);
	return (0);
}

int	main(void)
{
	char	input[] = "../../testing/testas3.txt";
	char	output1[] = "../../testing/test1.txt";
	char	output2[] = "../../testing/test2.txt";
	//int		out_typ = 2; // 0 = >, 1 == >>

	redirection_test(input, output1, 0);
	redirection_test(input, output2, 1);
	return (0);	
}