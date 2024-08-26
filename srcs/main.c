/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:22:17 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/22 15:02:54 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include <readline/readline.h>

int	init_environment(t_shell *mshell, char **envp)
{
	int i;
	char	*key;
	char	*value;
	t_env	*new_env;

	i = 0;
	while (envp[i])
	{
		value = ft_getvalue(envp[i]);
		key = ft_getkeyword(envp[i++]);
		if (!key || !value)
		{	
			free(key);
			free(value);
			return (-1);
		}
		new_env = ft_new_env(key, value);
		if (!new_env)
		{
			free(key);
			free(value);
			return (-1);
		}
		ft_add_env(&mshell->envlst, new_env);
	}
	return(0);
}

int	init_shell(t_shell *mshell, char **envp)
{
	ft_memset(mshell, 0, sizeof(t_shell));
	/* init environment */
	init_environment(mshell, envp);
	mshell->in = dup(0);
	mshell->out = dup(1);
	/* tcgetattr */
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	mshell;
	((void)argc, (void)argv, (void)envp); 
	/* init data */
	init_shell(&mshell, envp);
	// ft_printenvlist(&mshell);
	while(1)
	{
		/* init signals */
		/* readline */
		mshell.line = readline("\033[1;34mminishell>\033[0m ");
		if (!mshell.line)
			return(free(mshell.line), 0);
		/* Testing */
		printf("%s\n", mshell.line);
		if (!ft_strncmp(mshell.line, "exit", 5))
			return(free(mshell.line), 0);
		/* update history */
		add_history(mshell.line);
		/* tokenize */
		ft_tokenize(&mshell);
		ft_printlist(&mshell.token_list);
		/* parse */
		/* handle errors */
		/* execute parse tree */		
		ft_clear_tokenlist(&mshell.token_list);
		free(mshell.line);
	}
	ft_clear_envlist(&mshell.envlst);
	return (0);
}