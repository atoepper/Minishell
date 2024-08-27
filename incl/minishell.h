/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:20:04 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/27 11:04:20 by jweingar         ###   ########.fr       */
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

// redirection
# define READ			0b00000000100000000000000000000000
# define HEREDOC		0b00000000010000000000000000000000
# define WRITE			0b00000000001000000000000000000000
# define WRITE_APPEND	0b00000000000100000000000000000000

// word_type
//  define PURE_WORD		0b00000000000000001000000000000000
//  define EXPANDED		0b00000000000000000100000000000000
# define DQUOTE			0b00000000000000000010000000000000
# define SQUOTE			0b00000000000000000001000000000000
//  define QUOTE			0b00000000000000000011000000000000

// linked_word_status
# define LEFT_IFS		0b00000000000000000000000010000000
# define RIGHT_IFS		0b00000000000000000000000001000000
# define LEFT_JOIN		0b00000000000000000000000000100000
# define RIGHT_JOIN		0b00000000000000000000000000010000
# define WORD_JOIN		0b00000000000000000000000000110000

typedef enum
{
	PROGRAM,
	PIPELINE,
	COMMAND_TERM,
	COMMAND,
	REDIR_ITER,
	REDIR_TERM,
	REDIR,
	EXEC_PATH,
	FILE_PATH,
} ast_node_type;

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
	ast_node_type		type;
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
	// char			**environ;
	// bool			heredoc_sigint;
} t_shell;

typedef int	(*t_function_ptr)(char **argv, char **envp);

typedef struct s_builtin
{
	char			*name;
	t_function_ptr	func;
}	t_builtin;

/* BUILTINS */
int		ft_echo(char **argv, char **envp);
int		ft_print_env(char **envp);
int		ft_exit(char **argv, char **envp);
int		ft_pwd(char **argv, char **envp);
int		ft_cd(char **argv, char **envp);
int		ft_env(char **argv, t_env *envlst);
int		ft_export(char **argv, t_env *envlst);
int		ft_unset(char **argv, char **envp);

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
int				exec_external(char **argv, char **envp);
char			*ft_join_path_and_name(char *path, char *name);
char			*search_function_in_path(char *name);
int				search_file_in_directory(const char *directory, char *name);
int				exec_builtin(char **argv, char **envp);
t_function_ptr	functionpath_builtins(char *name);
t_builtin		**fill_lst_builtins(void);
t_builtin		**alloc_lst_builtins(void);
void			free_lst_builtin(t_builtin	**lst_builtins);
int				exec_function(char **argv, char **envp);
char			*read_fd_to_str(int fd);

/* INIT */
int		init_shell(t_shell *mshell, char **envp);
void	create_prompt(t_shell *mshell);
int		init_environment(t_shell *mshell, char **envp);

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
t_ast_node	*parse_program(t_token **current_token);
t_ast_node	*parse_pipe(t_token **current_token);
t_ast_node	*parse_command_term(t_token **current_token);
t_ast_node	*parse_command(t_token **current_token);
t_ast_node	*parse_redir_iter(t_token **current_token);
t_ast_node	*parse_redir_term(t_token **current_token);
t_ast_node	*create_ast_node(ast_node_type type, char *value);
void		add_child_node(t_ast_node *parent, t_ast_node *child);
void		free_ast(t_ast_node *node);
void		print_ast(t_ast_node *node, int indent);

/* GARBAGE_COLLECTION */
int		clear_garbage(t_shell mshell)

/* SIGNALS */

/* UTILS */
void	ft_skipspaces(char **line);
int		ft_nextchar(char *str, char c);
int		ft_wordlength(char *line);
bool	ft_isseparator(const char c);
int		ft_end_of_varname(char *str);
bool	ft_iskeyword(char *str);
void	free_array(char **arr);

#endif