/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:06:36 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/14 17:51:07 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

extern int g_signal_flag;

char	*ft_increase_shlvl(char *value)
{
	char	*new_level;

	new_level = ft_itoa(ft_atoi(value) + 1);
	free(value);
	return (new_level);
}

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
			return (free(key), free(value), -1);
		if (ft_strncmp(key, "SHLVL", 6) == 0)
			value = ft_increase_shlvl(value);
		new_env = ft_new_env(key, value);
		if (!new_env)
			return (free(key), free(value), -1);
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
	mshell->env = NULL;
	init_environment(mshell, envp);
	mshell->env = ft_remake_env(mshell);
	create_prompt(mshell);
	mshell->in = dup(0);
	mshell->out = dup(1);
	tcgetattr(STDIN_FILENO, &(mshell->startterm));
	set_sig_term(NO_CHILD);
	mshell->is_exit_prog = FALSE;
	mshell->exit_status = 0;
	mshell->err_type = NO_ERR;
	mshell->lst_builtins = fill_lst_builtins();
	mshell->error = 0;
	return (0);
}

void	ft_renewshell(t_shell *mshell)
{
	create_prompt(mshell);
	ft_clear_tokenlist(&(mshell->token_list));
	mshell->token_list = NULL;
	free_ast(mshell->ast);
	mshell->ast = NULL;
	mshell->exit_status = mshell->error;
	mshell->error = 0;
	mshell->err_type = NO_ERR;
	free(mshell->line);
	free(mshell->last_output);
	if (g_signal_flag == 1)
	{
		g_signal_flag = 0;
		mshell->exit_status = 130;
	}
	mshell->last_output = NULL;
}
