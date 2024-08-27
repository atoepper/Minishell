/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_export_unset_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:55:26 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/27 12:38:51 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	mshell;
	char	*argv2[] = {"export", "test270824=new", "XDG_MENU_PREFIX=test", NULL};
	char	*argv3[] = {"export", "test270824=old", "hallo=Johannes", NULL};
	char	*argv4[] = {"unset", NULL};
	char	*argv5[] = {"unset", "test270824", "dafsdfas", "hallo", NULL};

	((void)argc, (void)argv, (void)envp); 
	/* init data */
	init_shell(&mshell, envp);
	ft_env(argv, mshell.envlst);
	printf("\n\n\n-----------------------------------------------------------------------\n\n\n");
	ft_export(argv2, mshell.envlst);
	ft_env(argv, mshell.envlst);
	printf("\n\n\n-----------------------------------------------------------------------\n\n\n");
	ft_export(argv3, mshell.envlst);
	ft_env(argv, mshell.envlst);
	printf("\n\n\n-----------------------------------------------------------------------\n\n\n");
	ft_unset(argv4, mshell.envlst);
	ft_unset(argv5, mshell.envlst);
	ft_env(argv, mshell.envlst);
	printf("\n\n\n-----------------------------------------------------------------------\n\n\n");
	clear_garbage(&mshell);
}