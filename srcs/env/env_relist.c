/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_relist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:23:47 by jweingar          #+#    #+#             */
/*   Updated: 2024/10/15 11:19:58 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_env(char **env)
{
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

int	count_entries(t_env	*envlst)
{
	int	count;

	count = 0;
	while (envlst != NULL)
	{
		count++;
		envlst = envlst->next;
	}
	return (count);
}

char	*ft_make_env_str(char *key, char *value)
{
	char	*str;
	char	*new_str;

	if (value == NULL)
	{
		str = ft_strdup(key);
		return (str);
	}
	else
	{
		str = ft_strjoin(key, "=");
		if (str == NULL)
			return (NULL);
		new_str = ft_strjoin(str, value);
		free(str);
		if (new_str == NULL)
			return (NULL);
		return (new_str);
	}
}

char	**ft_remake_env(t_shell *mshell)
{
	char	**env;
	char	**orig_env;
	t_env	*envlst;
	int		count;

	free_array(mshell->env);
	envlst = mshell->envlst;
	count = count_entries(envlst);
	env = (char **)malloc((count + 1) * sizeof(char *));
	if (env == NULL)
		return (NULL);
	orig_env = env;
	env[count] = NULL;
	while (envlst != NULL)
	{
		*env = ft_make_env_str(envlst->key, envlst->value);
		env++;
		envlst = envlst->next;
	}
	return (orig_env);
}
