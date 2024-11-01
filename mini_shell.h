/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:05:26 by skreik            #+#    #+#             */
/*   Updated: 2024/11/01 14:56:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# ifndef INITIAL_SIZE
#  define INITIAL_SIZE 1024
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include "Libft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
#include <termios.h>

# ifndef GLOBALS_H
#  define GLOBALS_H

extern int global_var; // Declare the global variable

# endif

typedef enum
{
	T_APPEND,
	T_HEREDOC,
	T_OUTPUT,
	T_INPUT,
	T_NUMBER,
	T_OPERATOR,
	T_PARENTHESIS,
	T_IDENTIFIER,
	T_WHITESPACE,
	T_UNKNOWN,
	T_ARGUMENT,
	T_PIPE,
	T_REDIRECTION,
	T_ENV,
	T_PATH,
	T_BRACES,
	T_TILDE,
	T_QUOTED_STRING,
	T_SEMICOLON,
	T_AMPERSAND,
	T_LOGICAL_AND,
	T_LOGICAL_OR,
	T_SUBSHELL,
	T_COMMAND_SEPARATOR,
	T_QUOTE,
	T_PERIODS,
}							t_type;

typedef struct s_env_signals
{
	t_type					type;
	char					**env;
	struct s_env_signals	*next;
	struct s_env_signals	*prev;
}							t_env_signals;

typedef struct s_input
{
	t_type					type;
	char *value;          // dynamically allocated
	struct s_input *next; // Pointer to the next token in the list
	struct s_input *prev; // Pointer to the previous token in the list
}							t_input;

typedef struct
{
	t_input *head; // Points to the first token in the list
	t_input *tail; // Points to the last token in the list
}							t_tokenlist;

typedef struct s_fd
{
	int						fd_1;
	int						fd_2;
}							t_fd;

typedef struct s_quoted
{
	char					*single;
	char					*doubles;
}							t_quoted;

typedef struct s_parser
{
	char					*command;
	char					**input;
	char					**operations;
	int						*redirection;
	char					*delimeter;
	char					**args;
	char					*infile;
	char					**outfile;
	struct s_parser			*prev;
	struct s_parser			*next;
}							t_parser;

typedef struct s_env_var
{
	const char				*name;
	int						length;
}							t_env_var;

typedef struct s_env
{
	char					**env;
	int						exit_code;
}							t_env;

// typedef struct s_fd{
// 	int	fd_1;
// 	int	fd_2;
// }t_fd;

// void                        ctrl_c_press_here(int signal);
void						ctrl_c_press(int signal_nb);
t_input						*create_token(t_type type, const char *value);
void						free_token(t_input *token);
t_tokenlist					*create_token_list(void);
void						add_token(t_tokenlist *list, t_input *token);
void						free_token_list(t_tokenlist *list);
void						print_tokens(const t_tokenlist *list);
void						handle_pipe(const char **p,
								t_tokenlist *token_list);
void						handle_redirection(const char **p,
								t_tokenlist *token_list);
void						handle_argument(const char **p,
								t_tokenlist *token_list);
void						handle_operator(const char **p,
								t_tokenlist *token_list);
void						handle_tilde(const char **p,
								t_tokenlist *token_list);
void						handle_env_variable(const char **p,
								t_tokenlist *token_list);
void						handle_parenthesis(const char **p,
								t_tokenlist *token_list);
void						handle_number(const char **p,
								t_tokenlist *token_list);
char						*ft_find_str(const char **str, char c);
void						handle_quote(const char **p,
								t_tokenlist *token_list);
void						handle_braces(const char **p,
								t_tokenlist *token_list);
void						handle_identifier(const char **p,
								t_tokenlist *token_list);
void						handle_unknown(const char **p,
								t_tokenlist *token_list);
void						handle_period(const char **p,
								t_tokenlist *token_list);
void						handle_path(const char **p,
								t_tokenlist *token_list);
t_tokenlist					*tokenize_input(const char *input);
int							ft_isprintable(char c);
t_parser					*create_parser(void);
// void parse_tokens(t_parser **parser, t_tokenlist *list);
void						print_2d_array(char **array);
void						ft_redirection(t_parser *node);
int builtin_env(t_parser *list, t_env *myenv);
void builtin_pwd(t_parser *parser, t_env *env);
int							builtin_unset(char **input, t_env *myenv);
t_env						*init_env(char **env);
void						builtin_echo(t_parser *list, t_env env);
// void builtin_echo_helper(char **input, char quote, t_env env);
void						ft_free_env(t_env **myenv);
int							builtin_cd(t_parser *parser, t_env *myenv);
void						add_or_update_to_env(char *name, char *value,
								t_env *env);
void						builtin_exit(t_parser *parser, t_env *myenv);
void						builtin_export(t_parser *list, t_env *env);
char						**add_string_to_2d_array(char **array,
								char *new_string);
int							is_executable(char *cmd);
int							ft_checkft(t_parser *parser);
int							ft_handle_redirections(t_parser *parser, int re);
void						ft_redirection_delimiter(t_parser *node);
void						cmds_exec(t_parser *parser, t_env *env);
char						*ft_getenv(t_env *myenv, char *str);
void						update_pwd(t_env *myenv);
void						update_env_level(t_env *myenv);
void						free_parser(t_parser *parser);
int							parse_tokens(t_parser **parser, t_tokenlist *list,
								t_env env);
bool						check_balanced_quotes(const char *input);
void						handle_quote1(const char **p);
char						*remove_quotes_new(const char *str);
char						*remove_quotes(const char *str);
int							handle_heredoc(char **heredoc_content);
char						*get_path_1(t_env env, char *cmd);
void						print_expanded_input(char **input,
								bool inside_single_quotes, t_env env);
bool	cmd_is_dir(char *cmd);
int check_args_nb(t_parser *list);
void replace_with_str(char ***array, char *new_str);
void print_env_sorted(t_env *env);
int check_value(char *str);
int check_input(char *str);
void check_semicolon(char *name, char **value);
int ft_haschar(char *str, char c);
char *ft_escape_char(char *str);
char *process_variable(char *input, t_env *env);
char *ft_trim_string(char *str);
int ft_doublecharlen(t_env *env);
void free_name_and_value(char *new_name, char *new_value);
void handle_memory_errors(char *new_name, char *new_value);
void free_env(t_env *env);
char *concatenate_value(char *current_value, char *new_value);
void replace_or_append_value(char **env_entry, char *new_name, char *new_value);
int find_and_update_env(int check_input_status, char *new_name, char *new_value, t_env *env);
void parse_export_input(char *input, char **name, char **value);
char *itoa(int num);
char *get_env_value(t_env *env, const char *var);
int check_input_end(char *str);
char *remove_quotes_new_new(const char *str);
#endif
