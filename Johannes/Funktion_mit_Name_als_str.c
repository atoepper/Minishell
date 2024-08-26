/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Funktion_mit_Name_als_str.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:19:56 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/15 13:29:32 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

typedef struct {
    char *name;
    void (*func)(int);
} s_FunctionMap;

void	ecko(int nb)
{
	printf("%i\n", nb);
}

void	plus(int nb)
{
	printf("%i\n", nb + nb);
}

void	ft_call(s_FunctionMap	*functions, char *name, int nb)
{
	int i;

	i = 0;
	while (functions[i].name != NULL)
	{
		if (ft_strncmp(name, functions[i].name, 6) == 0)
		{
			functions[i].func(nb);
			break;
		}
		else
			i++;
	}
}

int	main(void)
{
	s_FunctionMap	functions[3];
	char *name;
	
	functions[0].name = "ecko";
	functions[0].func = &ecko;
	functions[1].name = "plus";
	functions[1].func = &plus;
	functions[2].name = NULL;
	functions[2].func = NULL;
	
		
	name = "ecko";
	printf("name: %s = ", name);
	ft_call(functions, name, 5);
	name = "plus";
	printf("name: %s = ", name);
	ft_call(functions, name, 5);
	return (0);
}
