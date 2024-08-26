/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:22:17 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/26 12:00:04 by atoepper         ###   ########.fr       */
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

void	create_prompt(t_shell *mshell)
{
	char	*cwd;
	char	*tmp;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (mshell->prompt)
		free (mshell->prompt);
	tmp = ft_strjoin ("minishell \033[1;34m", cwd);
	mshell->prompt = ft_strjoin(tmp, "\033[0m % ");
	free (cwd);
	free (tmp);
}

int	init_shell(t_shell *mshell, char **envp)
{
	ft_memset(mshell, 0, sizeof(t_shell));
	/* init environment */
	init_environment(mshell, envp);
	create_prompt(mshell);
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
		mshell.line = readline(mshell.prompt);
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
		create_prompt(&mshell);
		ft_clear_tokenlist(&mshell.token_list);
		free(mshell.line);
	}
	ft_clear_envlist(&mshell.envlst);
	return (0);
}
