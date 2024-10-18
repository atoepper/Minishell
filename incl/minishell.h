/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:20:04 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/18 10:20:51 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* INCLUDES */

# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
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
# include <stdlib.h>

/* ENUMS */

// token_type
# define EXPANDER		0b10000000000000000000000000000000
# define PIPE			0b01000000000000000000000000000000
# define REDIRECT		0b00100000000000000000000000000000
# define WORD			0b00010000000000000000000000000000
# define DQUOTE			0b00001000000000000000000000000000
# define SQUOTE			0b00000100000000000000000000000000

// redirection
# define READ			0b00000010000000000000000000000000
# define HEREDOC		0b00000001000000000000000000000000
# define WRITE			0b00000000100000000000000000000000
# define WRITE_APPEND	0b00000000010000000000000000000000

// word linking
# define RIGHT_JOIN		0b00000000001000000000000000000000

// additional grammar flags
# define PROGRAM		0b00000000000100000000000000000000
# define COMMAND_TERM	0b00000000000010000000000000000000
# define COMMAND		0b00000000000001000000000000000000
# define REDIR_ITER		0b00000000000000100000000000000000
# define REDIR_TERM		0b00000000000000010000000000000000

# ifndef ECHOCTL
#  define ECHOCTL 0x00000040
# endif

enum e_process_mode
{
	NO_CHILD,
	WITH_CHILD,
	EXECUTE_CHILD,
	IN_HEREDOC,
};

enum e_err_type
{
	NO_ERR,
	MALLOC,
	SYNTAX,
	PARSE,
	OPEN_QUOTES,
	NO_FILE,
	NO_FILE_RED,
	CD_ARG,
	EXIT_ARG,
	EXIT_ARG_NUM
};

/* STRUCTURES */

typedef struct s_token
{
	int					type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_ast_node
{
	int					type;
	char				*value;
	char				**argv;
	struct s_ast_node	*child;
	struct s_ast_node	*next;
	int					pid;
	int					exit_status;
	int					fd[2];
}	t_ast_node;

struct		s_shell;

typedef int	(*t_function_ptr)(char **argv, struct s_shell *mshell, int fd);

typedef struct s_builtin
{
	char			*name;
	t_function_ptr	func;
}	t_builtin;

typedef struct s_shell
{
	char			*line;
	char			*prompt;
	int				in;
	int				out;
	int				exit_status;
	int				error;
	bool			is_exit_prog;
	int				exit_prog_val;
	enum e_err_type	err_type;
	char			*last_output;
	struct termios	startterm;	
	t_token			*token_list;
	t_token			*curr_token;
	t_env			*envlst;
	t_ast_node		*ast;
	t_builtin		**lst_builtins;
	char			**env;
}	t_shell;

/* BUILTINS */
int				ft_echo(char **argv, t_shell *mshell, int fd);
int				ft_print_env(char **envp);
int				ft_exit(char **argv, t_shell *mshell, int fd);
int				ft_pwd(char **argv, t_shell *mshell, int fd);
int				ft_cd(char **argv, t_shell *mshell, int fd);
int				ft_env(char **argv, t_shell *mshell, int fd);
int				ft_export(char **argv, t_shell *mshell, int fd);
int				ft_unset(char **argv, t_shell *mshell, int fd);

/* ENVIRONMENT */
char			*ft_find_value_by_key(t_env *list, char *keyword);
char			*ft_getvalue(char *str);
t_env			*ft_new_env(char *key, char *value);
void			ft_add_env(t_env **envlist, t_env *new_env);
void			ft_del_env(t_env *env);
void			ft_clear_envlist(t_env **envlist);
char			*ft_getkeyword(char *str);
void			ft_change_envvalue(t_env *envlist, char *key, char *new_value);
void			ft_remove_env(t_env **envlist, char *key);
void			ft_printenvlist(t_shell *mshell);
char			**ft_remake_env(t_shell *mshell);
void			print_env(char **env);
char			*ft_find_key(t_env *list, char *keyword);

/* EXECUTION */
int				exec_external(t_ast_node *node_command_term,
					char **argv, t_shell *mshell);
char			*ft_join_path_and_name(char *path, char *name);
char			*search_function_in_path(char *name, t_shell *mshell);
int				search_file_in_directory(const char *directory, char *name);
int				exec_builtin(t_ast_node *node_command_term,
					char **argv, t_shell *mshell);
t_function_ptr	functionpath_builtins(char *name, t_shell *mshell);
t_builtin		**fill_lst_builtins(void);
t_builtin		**alloc_lst_builtins(void);
void			free_lst_builtin(t_builtin	**lst_builtins);
int				exec_function(t_ast_node *node_command_term, t_shell *mshell);
int				execute_programm(t_shell *mshell);
int				execute_command_term(t_shell *mshell,
					t_ast_node *node_command_term);
int				execute_command(t_shell *mshell,
					t_ast_node *node_command, int in_fd);
int				input_read(t_ast_node *node_command_term,
					char *input, t_shell *mshell);
int				input_heredoc(t_ast_node *node_command_term,
					char *input, t_shell *mshell);
int				ouput_write(t_ast_node *node_command_term,
					char *path, t_shell *mshell);
int				ouput_write_append(t_ast_node *node_command_term,
					char *path, t_shell *mshell);
char			*read_fd_to_str(t_ast_node *node_command_term);
int				write_str_to_fd(char *str, int fd);
int				add_re_in_to_pipe(t_ast_node *node_command_term,
					t_shell *mshell);
int				add_re_out_to_pipe(t_ast_node *node_command_term,
					t_shell *mshell);
int				add_str_to_pipe(t_ast_node *node_command_term, char *str);
bool			add_str_to_redirections(t_ast_node *node_command_term,
					char *str, t_shell *mshell);
int				exec_external_child(t_ast_node *node_command_term,
					char **argv, char *path, t_shell *mshell);
void			print_and_save_str(t_shell *mshell, char *str);
int				check_if_red_out(t_ast_node *node_command_term);
int				create_pipe(int *pipe_fd);
void			add_pipe_to_output(t_ast_node *node_command_term, t_shell *mshell);

/* INIT */
int				init_shell(t_shell *mshell, char **envp);
void			create_prompt(t_shell *mshell);
int				init_environment(t_shell *mshell, char **envp);
void			ft_renewshell(t_shell *mshell);

/* ERROR */
void			ft_set_error(t_shell *mshell, int errno,
					enum e_err_type err_type);
void			print2errorfile(char *str);
int				set_error_exe(t_shell *mshell, int errno);
void			ft_process_error(t_shell *mshell);

/* EXPANDER */
char			*ft_expand(char *value, t_shell *mshell, int type);
int				expander(t_shell *mshell);

/* TOKENIZING */
t_token			*ft_newtoken(char *value, int type);
void			ft_addtoken(t_token **tokenlist, t_token *newtoken);
void			ft_clear_tokenlist(t_token	**tokenlist);
void			ft_deltoken(t_token *token);
t_token			*ft_linetolist(t_shell *mshell, char *line, int *error);
int				ft_tokenize(t_shell *mshell);
int				ft_joinwords(t_token **list);
void			ft_printlist(t_token **tokenlist);

/* PARSING */
t_ast_node		*parse_program(t_shell *mshell);
t_ast_node		*parse_command_term(t_shell *mshell);
t_ast_node		*parse_element(t_shell *mshell);
t_ast_node		*create_ast_node(int type, char *value);
void			add_child_node(t_ast_node *parent, t_ast_node *child);
void			add_branch(t_ast_node *parent, t_ast_node *child);
void			free_ast(t_ast_node *node);
int				ft_count_args(t_ast_node **command);
int				ft_create_argv(t_ast_node *command);

/* GARBAGE_COLLECTION */
int				clear_garbage(t_shell *mshell);

/* SIGNALS */
void			set_sig_term(int mode);
void			sigint_handler(int signo);
void			sigint_handler_newline(int signo);
void			set_signal(int mode);
void			set_termios(int mode);

/* UTILS */
void			ft_skipspaces(char **line);
int				ft_nextchar(char *str, char c);
int				ft_wordlength(char *line);
bool			ft_isseparator(const char c);
bool			ft_string_is_empty(char *str);
int				ft_end_of_varname(char *str);
bool			ft_iskeyword(char *str);
void			free_array(char **arr);
bool			is_output_without_nl(t_shell *mshell);
int				ft_find_equal(char *str);

#endif