/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:20:04 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/08 14:04:17 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* INCLUDES */

# include "../libft/libft.h"

# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <signal.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

/* ENUMS */

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_O_PARENT,
	T_C_PARENT,
	T_AND,
	T_OR,
	T_NL,
}	t_token_type;

/* STRUCTURES */

typedef struct s_shell
{
	char			*line;
	int				in;
	int				out;
	int				exit_status;
	struct termios	startterm;	
	t_token			**token_list;
	t_token			*curr_token;
	// t_node			*ast;
	// bool			signint_child;
	// t_parse_err		parse_err;
	// char			**environ;
	// t_env			*envlst;
	// bool			heredoc_sigint;
} t_shell;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

/* BUILTINS */
int	ft_print_env(char **env);
int	ft_exit(int exitvalue);
int	ft_pwd(void);

/* EXECUTION */

/* EXPANDER */

/* TOKENIZING */

/* PARSING */

/* SIGNALS */

#endif