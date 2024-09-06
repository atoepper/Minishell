/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:06:36 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/06 11:40:13 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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
	init_environment(mshell, envp);
	create_prompt(mshell);
	mshell->in = dup(0);
	mshell->out = dup(1);
	tcgetattr(STDIN_FILENO, &(mshell->startterm));
	sigtermset(0);
	return (1);
}

void	ft_renewshell(t_shell *mshell)
{
		create_prompt(mshell);
		ft_clear_tokenlist(&(mshell->token_list));
		free_ast(mshell->ast);
		mshell->exit_status = mshell->error;
		mshell->error = 0;
		free(mshell->line);
}