/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmota <marmota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:54:10 by pestevao          #+#    #+#             */
/*   Updated: 2022/02/18 13:18:28 by marmota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>

typedef struct s_global
{
	int		last_exit;
	char	*env[9999];
	int		env_c;
	int		sigprint;
}			t_global;

typedef struct s_parser
{
	int		i;
	int		j;
	int		count_token[9999];
	int		count_cmd;
	int		open_quote;
	int		open_apos;
	int		max_token;
	char	***cmds;
	int		**is_redir;
}			t_parser;

t_global	g_v;

//	minishell.c
void			cmd_history(char *cmd);

//	scanner.c
int				built_cmds(t_parser *cmd, int cmd_n);
int				get_redir(t_parser *cmd, int cmd_n, int flag);
void			cmd_scanner(t_parser *cmd);
void			scan_cmd(char *cmd);
int				get_redir_to_execve(t_parser *cmd, int cmd_n, int i, char *ret);

// scanner1.c
int				get_cmd_token(t_parser *cmd, int cmd_n);
int				copy_path(t_parser *cmd, int cmd_n, int i, char *ret);
char			*search_path(t_parser *cmd, int cmd_n, int token, int x);
int				list_files(t_parser *cmd, int cmd_n, int token, char *path);
int				create_process(t_parser *cmd, int cmd_n, int j);

//	parser.c
void			fill_memory(t_parser *p);
void			create_memory(t_parser *p);
void			destroy_memory(t_parser *p);
void			init_struct(t_parser *p);
int				ft_isalpha(int c);

void			write_char(t_parser *p, char c, int w);
void			handle_quote(t_parser *p);
void			handle_apos(t_parser *p);
int				is_redirection(char c);
void			handle_pipe(t_parser *p, char *str, int w);

void			handle_redirection(t_parser *p, char *str, int w);
void			handle_space(t_parser *p, char *str);
char			*parser_getenv(char *env);
void			clean_replace(char *replace);
void			handle_env(t_parser *p, char *str);

void			handle_exit(t_parser *p);
void			handle_dollar(t_parser *p, char *str);
void			print_matrix(t_parser *p);
void			parse_cmds(char *str, t_parser *p);
void			count_cmds(char *str);

//	utils
unsigned int	ft_strlen(const char *str);
char			*ft_strcat(char *dest, char *src);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_itoa(int n);
char			*ft_strdup(const char *s1);
int				count_words(const char *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
int				detect_flags(t_parser *cmd, int cmd_n, int i);
char			*get_filename(t_parser *cmd, int cmd_n, int i);
void			fill_builtin_mem(char **cmds_list);
int				do_not_redir(t_parser *cmd, int cmd_n);

//	builtins
char			*get_cmd(t_parser *cmd, int cmd_n);
void			run_cd(t_parser *cmd, int cmd_n);
void			run_pwd(void);
void			run_env(void);
void			run_exit(char *cmd);
void			run_export(void);
void			run_unset(char *str);
void			parse_echo(t_parser *cmd, int cmd_n);
void			parse_export(t_parser *cmd, int cmd_n);
void			parse_unset(t_parser *cmd, int cmd_n);

//	execute
char			*get_cmd_path(t_parser *cmd, int cmd_n);
void			get_arr_to_execve(char *str[], t_parser *cmd, int cmd_n);
int				execute_cmds(t_parser *cmd, int cmd_n);
void			execute_built_cmd(t_parser *cmd, int cmd_id, int cmd_n);
void			exec_redir(t_parser *cmd);

//	pipes
int				search_pipes(t_parser *cmd);
void			pipeline(t_parser *cmd, int cmd_n, int pipe_cnt);
void			execute_pipes(t_parser *cmd, int cmd_n, int pipe_n, int *fd);

//	redirection
void			redirections(t_parser *cmd, int cmd_n);
void			open_file(t_parser *cmd, int cmd_n, int token);
void			redir_input(int fd);
void			redir_output(int fd);
int				exec_heredoc(char *eof);

//	parse_errors
int				parse_errors(t_parser *p);
void			setup_sig(void);
void			exec_error(void);

//  signals
void			setup_stty();
void			handle_signal(int sig);

// export
void			export_set_env(char *str);

#endif
