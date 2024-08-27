/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:51:47 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/27 14:36:07 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_pwd(char **argv, t_env *envlst)
{
	char	*pwd;

	((void)argv, (void)envlst);
	if (argv[1] != NULL)
		return (perror("pwd: too many arguments"), 1);
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (1);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
