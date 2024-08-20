/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:20:04 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/20 13:26:08 by jweingar         ###   ########.fr       */
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
# include <stdarg.h>
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

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

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
}	t_shell;

typedef int	(*t_function_ptr)(char **argv);

typedef struct s_builtin
{
	char			*name;
	t_function_ptr	func;
}	t_builtin;

/* BUILTINS */
int		ft_echo(char **argv);
int		ft_print_env(char **env);
int		ft_exit(int exitvalue);
int		ft_pwd(void);
int		ft_cd(const char *path);

/* EXECUTION */
int				exec_external(char **argv);
char			*ft_join_path_and_name(char *path, char *name);
char			*search_function_in_path(char *name);
int				search_file_in_directory(const char *directory, char *name);
int				exec_builtin(char **argv);
t_function_ptr	functionpath_builtins(char *name);
t_builtin		**fill_lst_builtins(void);
t_builtin		**alloc_lst_builtins(void);
void			free_lst_builtin(t_builtin	**lst_builtins);
int				exec_function(char **argv);
char			*read_fd_to_str(int fd);

/* EXPANDER */

/* TOKENIZING */

/* PARSING */

/* SIGNALS */

#endif