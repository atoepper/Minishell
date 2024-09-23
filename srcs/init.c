/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:06:36 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/23 15:15:20 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	init_environment(t_shell *mshell, char **envp)
{
	int		i;
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
			return (free(value), -1);
		}
		new_env = ft_new_env(key, value);
		if (!new_env)
		{
			free(key);
			return (free(value), -1);
		}
		ft_add_env(&mshell->envlst, new_env);
	}
	return (0);
}

void	create_prompt(t_shell *mshell)
{
	char	*cwd;
	char	*tmp;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (mshell->prompt)
		free (mshell->prompt);
	tmp = ft_strjoin ("\033[0mminishell \033[1;34m", cwd);
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
	set_sig_term(NO_CHILD);
	mshell->is_exit_prog = FALSE;
	mshell->lst_builtins = fill_lst_builtins();
	mshell->error = 0;
	return (0);
}



void	ft_renewshell(t_shell *mshell)
{
	create_prompt(mshell);
	ft_clear_tokenlist(&(mshell->token_list));
	free_ast(mshell->ast);
	mshell->exit_status = mshell->error;
	mshell->error = 0;
	free(mshell->line);
	free(mshell->last_output);
	mshell->last_output = NULL;
}
