/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:19:56 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/07 09:20:18 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc == 0)
		return(1);
	printf("%s\n", argv[0]);
	ft_print_env(envp);
	ft_pwd();
	ft_exit(0);
	return (0);
}