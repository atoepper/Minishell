/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:20:04 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/10 15:36:25 by jweingar         ###   ########.fr       */
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
}	t_ast_node;

typedef struct s_shell
{
	char			*line;
	char			*prompt;
	int				in;
	int				out;
	int				exit_status;
	int				error;
	struct termios	startterm;	
	t_token			*token_list;
	t_token			*curr_token;
	t_env			*envlst;
	t_ast_node		*ast;
	// bool			signint_child;
	// t_parse_err		parse_err;
	// bool			heredoc_sigint;
} t_shell;

typedef int	(*t_function_ptr)(char **argv, t_shell *mshell);

typedef struct s_builtin
{
	char			*name;
	t_function_ptr	func;
}	t_builtin;

/* BUILTINS */
int		ft_echo(char **argv, t_shell *mshell);
int		ft_print_env(char **envp);
int		ft_exit(char **argv, t_shell *mshell);
int		ft_pwd(char **argv, t_shell *mshell);
int		ft_cd(char **argv, t_shell *mshell);
int		ft_env(char **argv, t_shell *mshell);
int		ft_export(char **argv, t_shell *mshell);
int		ft_unset(char **argv, t_shell *mshell);

/* ENVIRONMENT */
char	*ft_find_value_by_key(t_env *list, char *keyword);
char	*ft_getvalue(char *str);
t_env	*ft_new_env(char *key, char *value);
void	ft_add_env(t_env **envlist, t_env *new_env);
void	ft_del_env(t_env *env);
void	ft_clear_envlist(t_env **envlist);
char	*ft_getkeyword(char *str);
void	ft_change_envvalue(t_env *envlist, char *key, char *new_value);
void	ft_remove_env(t_env **envlist, char *key);
void	ft_printenvlist(t_shell *mshell);

/* EXECUTION */
int				exec_external(char **argv, t_shell *mshell);
char			*ft_join_path_and_name(char *path, char *name);
char			*search_function_in_path(char *name);
int				search_file_in_directory(const char *directory, char *name);
int				exec_builtin(char **argv, t_shell *mshell);
t_function_ptr	functionpath_builtins(char *name);
t_builtin		**fill_lst_builtins(void);
t_builtin		**alloc_lst_builtins(void);
void			free_lst_builtin(t_builtin	**lst_builtins);
int				exec_function(t_ast_node *node_command_term, t_shell *mshell);
int				pipe_function(char *argvs[][6], t_shell *mshell, int in_fd);
int				execute_programm(t_shell *mshell);
int				execute_command_term(t_shell *mshell, t_ast_node *node_command_term, char *str);
int				execute_command(t_shell *mshell, t_ast_node *node_command, int in_fd);
char			*input_read(char *input, char *str);
char			*input_heredoc(char *input, char *str);
int				ouput_write(char *path, char *str);
int				ouput_write_append(char *path, char *str);
char			*read_fd_to_str(int fd);
int				write_str_to_fd(char *str, int fd);
int				add_redirection_to_pipe(t_ast_node *node_command_term, char *str, int fd);
int				add_str_to_redirections(t_ast_node *node_command_term, char *str);

/* INIT */
int		init_shell(t_shell *mshell, char **envp);
void	create_prompt(t_shell *mshell);
int		init_environment(t_shell *mshell, char **envp);
void	ft_renewshell(t_shell *mshell);

/* ERROR */
void	ft_set_error(t_shell *mshell, int errno, char *msg);

/* EXPANDER */
char	*ft_expand(char *value, t_shell *mshell);
int		expander(t_shell *mshell);

/* TOKENIZING */
t_token	*ft_newtoken(char *value, int type);
void	ft_addtoken(t_token **tokenlist, t_token *newtoken);
void	ft_clear_tokenlist(t_token	**tokenlist);
void	ft_deltoken(t_token *token);
void	ft_printlist(t_token **tokenlist);
t_token	*ft_linetolist(char *line, int *error);
int		ft_tokenize(t_shell *mshell);
int		ft_joinwords(t_token **list);

/* PARSING */
t_ast_node	*parse_program(t_shell *mshell);
t_ast_node	*parse_command_term(t_shell *mshell);
t_ast_node	*parse_command(t_shell *mshell);
t_ast_node	*parse_redir_iter(t_shell *mshell);
t_ast_node	*parse_redir_term(t_shell *mshell);
t_ast_node	*create_ast_node(int type, char *value);
void		add_child_node(t_ast_node *parent, t_ast_node *child);
void		free_ast(t_ast_node *node);
void		print_ast(t_ast_node *node, int indent);
int			ft_count_args(t_token **current);
char		**ft_create_argv(t_token **current, int argc);

/* GARBAGE_COLLECTION */
int		clear_garbage(t_shell *mshell);

/* SIGNALS */
void	sigtermset(int mode);
void	sigint_handler(int signo);
void	sigint_handler_print_newline(int signo);
void	set_signal(int mode);

/* UTILS */
void	ft_skipspaces(char **line);
int		ft_nextchar(char *str, char c);
int		ft_wordlength(char *line);
bool	ft_isseparator(const char c);
int		ft_end_of_varname(char *str);
bool	ft_iskeyword(char *str);
void	free_array(char **arr);

#endif