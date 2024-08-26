/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:57:51 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/26 11:19:38 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_cd(char **argv)
{
	int	return_value;

	if (argv == NULL || argv[1] == NULL)
		return (1);
	return_value = chdir(argv[1]);
	if (chdir(argv[1]) != EXIT_SUCCESS)
		return(perror("chdir"), return_value);
	printf("rv: %i\n", return_value);
	return(return_value);
}
