/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:24:07 by rponomar          #+#    #+#             */
/*   Updated: 2025/02/13 14:24:53 by rponomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

//	700 - X/Open 7, incorporating POSIX 2017
//	800 - X/Open 8, incorporating POSIX 2024
# define _XOPEN_SOURCE 700
# define _DEFAULT_SOURCE
# define FD_MAX 1023

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct sigaction	t_sa;

typedef struct s_token
{
	struct s_token	*prev;
	struct s_token	*next;
	char			*f_str;
	int				end;
	int				ao_and;
	int				ao_exit_status;
	int				ao_or;
	int				brace_close;
	int				brace_open;
	int				child_1_exit_status;
	int				child_2_exit_status;
	int				enclsr;
	int				execute;
	int				exp_env;
	int				exp_inv;
	int				exp_les;
	int				exp_qd;
	int				exp_qs;
	int				exp_wldcrd;
	int				optr;
	int				pipe;
	int				redir_file_heredoc;
	int				redir_input;
	int				redir_input_heredoc;
	int				redir_output_append;
	int				redir_output_trunc;
	int				w_arg;
	int				w_bltin;
	int				w_cmd;
	int				w_redir_file;
	int				w_redir_fd;
	int				w_redir_lim;
	int				word;
}	t_tkn;

typedef struct s_error_list
{
	char	argc[100];
	char	cmd_notfound[100];	
	char	empty_arg[100];
	char	empty_env_path[100];
	char	empty_host[100];
	char	empty_prompt[100];
	char	empty_user[100];
	char	fd_num_exceeded[100];
	char	fd_maxnum_overflow[100];
	char	heredoc_eof[100];
	char	invalid_name[100];
	char	is_dir[100];	
	char	many_args[100];
	char	numeric_required[100];	
	char	no_file[100];
	char	not_dir[100];	
	char	overflow[100];
	char	perm_denied[100];
	char	syntax_err[100];
	char	unmatched_quote[100];
	char	unset_home[100];	
	char	unset_oldpwd[100];
	char	wldcrds_cwd_only[100];
}	t_err;

typedef struct s_tracer
{
	t_err			*err_list;
	t_sa			sigacts[2];
	t_tkn			*tkn_head;
	t_tkn			*tkn_tracer;
	t_tkn			*tkn_heredoc_tracer;
	char			*f_chdir;
	char			*f_cmd;
	char			**f_cmd_args;
	char			*f_cmd_path;
	char			*f_cwd;
	char			*f_cwd_prev;
	char			**f_env;
	char			*f_home;
	char			*f_host;
	char			*f_line;
	char			*f_path;
	char			*f_path_start;
	int				*f_pids;
	int				**f_pipes;
	char			*f_prog;
	char			*f_prompt;
	int				f_redir_fds[101];
	char			*f_user;
	char			*f_wldcrd_mask;
	int				ac;
	char			**av;
	int				cmd_num;
	char			*err;
	int				do_exit;
	unsigned int	exit_status;
	char			exit_les[4];
	int				hd_fd;
	char			hd_filemask[100];
	char			hd_filename[100];
	char			hd_filename_0[100];
	char			hd_prompt[100];
	int				pid_current;
	int				pipes_num;
	int				redir_fd_stdin;
	int				redir_fd_stderr;
	int				redir_fd_stdout;	
	int				syntax;
	int				token_max_enclsr;	
	int				token_qty;
	long long		qb;
	int				qb_on;
	long long		qd;
	int				qd_on;
	long long		qs;
	int				qs_on;
}	t_tr;

void	ft_add_str_malloc(char **dst, char *add, size_t add_len, t_tr *t);
int		ft_atoi_fd(char *str, t_tr *t);
void	ft_bltin_chdir(t_tkn *tkn, t_tr *t);
void	ft_bltin_echo(t_tkn *tkn, t_tr *t);
void	ft_bltin_env(t_tkn *tkn, t_tr *t);
void	ft_bltin_exit(t_tkn *tkn, t_tr *t);
void	ft_bltin_export(t_tkn *tkn, t_tr *t);
void	ft_bltin_pwd(t_tkn *tkn, t_tr *t);
void	ft_bltin_unset(t_tkn *tkn, t_tr *t);
void	ft_chdir_canon_curpath(int *condition, char **f_curpath, t_tr *t);
void	ft_chdir_empty(int *condition, t_tkn *tkn, t_tr *t);
void	ft_chdir_home(int *condition, t_tkn *tkn, t_tr *t);
void	ft_chdir_oldpwd(int *condition, t_tkn *tkn, t_tr *t);
void	ft_chdir_path_max(int *condition, char **f_curpath, t_tr *t);
void	ft_chdir_set_curpath(int *cond, char **f_curpath, t_tkn *tkn, t_tr *t);
void	ft_check_argc(t_tr *t);
void	ft_close_catched_stds(t_tr *t);
void	ft_close_pipes(int flag_read, int flag_write, int ***pipes, t_tr *t);
void	ft_count_cmds(int encl, t_tkn *tkn, t_tr *t);
void	ft_ctx(int condition, t_tr *t, char *file_name, int line);
void	ft_err(int condition, t_tr *t, char *file_name, int line);
void	ft_err_start(int condition, char *prog_name, t_tr *t);
void	ft_get_cwd_names(char ***f_names, t_tr *t);
void	ft_e(int condition, char *cmd, char *arg, t_tr *t);
void	ft_err(int condition, t_tr *t, char *file_name, int line);
void	ft_exec(char ***f_dst, char *cmd_line, t_tr *t);
void	ft_execute(int enclsr_level, t_tkn *tkn_start, t_tr *t);
int		ft_execute_builtin(t_tkn *tkn, t_tr *t);
void	ft_execute_cmds_levels(int i, int encl, t_tkn **ptr_tkn, t_tr *t);
void	ft_execute_pipe(int encl, t_tkn **ptr_tkn, t_tr *t);
void	ft_execute_pipe_catch_exit_status(int num_executed, t_tr *t);
void	ft_execute_pipe_child_cmd(t_tkn **ptr_tkn, t_tr *t);
void	ft_execute_pipe_child_cmd_call_execve(t_tkn **tkn, t_tr *t);
void	ft_execute_pipe_child_simplify_path(t_tr *t);
void	ft_execute_pipe_cmds(int encl, t_tkn **ptr_tkn, t_tr *t);
void	ft_expand_assign_tags(int encl, t_tkn *tkn, t_tr *t);
void	ft_expand_delete_null(t_tkn **tkn, t_tr *t);
void	ft_expand_if_wildcards(t_tkn *tkn, t_tr *t);
void	ft_expand_quotes(int encl, t_tkn *tkn, t_tr *t);
int		ft_expand_quotes_parse(char *exp, char **f_s, t_tr *t);
void	ft_expand_split(int encl, t_tkn **ptr_tkn, t_tr *t);
int		ft_expand_split_tokens(char *exp, char **f_s, int encl, t_tr *t);
void	ft_expand_var(int encl, t_tkn **ptr_tkn, t_tr *t);
void	ft_expand_var_heredoc(int encl, t_tkn *tkn, t_tr *t);
int		ft_expand_var_passby(char *exp, char **f_s, t_tr *t);
int		ft_expand_var_quotes(char *exp, char **f_s, t_tr *t);
void	ft_expand_wildcards(int encl, t_tkn *tkn, t_tr *t);
int		ft_expand_wildcards_mask(t_tkn *tkn, t_tr *t);
void	ft_expand_wildcards_process_tkn(t_tkn **tkn, t_tr *t);
void	ft_expand_wildcards_split(char *wc, char ***f_arr, t_tr *t);
void	ft_free_2d_char(char ***arr);
void	ft_free_2d_int(int ***arr);
void	ft_free_all(t_tr *t);
void	ft_free_close_fd(int *fd, t_tr *t);
void	ft_free_int(int **ptr);
void	ft_free_nonexit(t_tr *t);
void	ft_free_pipes(t_tr *t);
void	ft_free_str(char **str);
void	ft_free_tokens(t_tr *t);
char	*ft_getenv(char **dst, char *env_name, t_tr *t);
void	ft_get_tokens(t_tr *t);
int		ft_heredoc_all(t_tr *t);
void	ft_heredoc_file(char *mode, t_tr *t);
void	ft_heredoc_fork_readfile(char *lim, t_tr *t);
void	ft_heredoc_if_sigint(t_tr *t);
int		ft_invalid_line(t_tr *t);
int		ft_invalid_fields(t_tr *t);
void	ft_invalid_fields_andor(int *fail, t_tkn *tkn_head, t_tr *t);
void	ft_invalid_fields_pipe(int *fail, t_tkn *tkn_head, t_tr *t);
void	ft_invalid_fields_redirection(int *fail, t_tkn *tkn_head, t_tr *t);
int		ft_is_blanc_str(char *str);
int		ft_is_builtin(char *str);
int		ft_is_directory(char *f_str, t_tr *t);
int		ft_is_exec_file(char *name, t_tr *t);
int		ft_is_match_wildcards(char *wc, char **f_arr, char *fn);
int		ft_is_split(int encl, t_tkn *tkn, char *str, t_tr *t);
int		ft_is_valid_file_path(t_tkn *tkn, t_tr *t);
int		ft_is_valid_redir_directory(t_tkn *tkn, t_tr *t);
void	ft_malloc_str(int conditon, char **str, int *memsize, t_tr *t);
void	ft_move_next_execute(int encl, t_tkn **ptr_tkn);
int		ft_redir(t_tkn **ptr_tkn, t_tr *t);
void	ft_redir_close_files(t_tr *t);
void	ft_redir_delete_tkns(t_tkn *tkn, t_tr *t);
int		ft_redir_file(int fd_redir, t_tkn *tkn, t_tr *t);
void	ft_reset_qds(t_tr *t);
void	ft_reset_std(t_tr *t);
void	ft_set_errno_messages(int errnum, t_tr *t);
void	ft_set_error_list(t_err *e, t_tr *t);
void	ft_set_tracker(int argc, char *argv[], char *envp[], t_tr *t);
void	ft_set_tracker_catch_std(t_tr *t);
void	ft_set_tracker_prog_name(char *prog_name, t_tr *t);
void	ft_set_tracker_shell_level(t_tr *t);
void	ft_set_tracker_start_path(t_tr *t);
void	ft_set_tracker_prompt(t_tr *t);
int		ft_sig_exit_status(t_tr *t);
void	ft_signal_all_ignore(t_tr *t);
void	ft_signal_all_ignore_start(char *prog_name, t_tr *t);
void	ft_signal_handler_sigint_dflt(t_tr *t);
void	ft_signal_handler_sigint_heredoc(t_tr *t);
void	ft_signal_handler_sigint_ignr(t_tr *t);
void	ft_signal_handler_sigint_main(t_tr *t);
void	ft_signal_handler_sigint_rline(t_tr *t);
void	ft_signal_handler_sigquit_dflt(t_tr *t);
void	ft_signal_handler_sigquit_ignr(t_tr *t);
void	ft_signal_handler_sigquit_main(t_tr *t);
void	ft_signal_mask_not_exit(t_sa *s, t_tr *t);
void	ft_tkn_delimiter(int *got_token, char **s, t_tr *t, t_tkn *tkn);
void	ft_tkn_operator_one(int *got_token, char **s, t_tr *t, t_tkn *tkn);
void	ft_tkn_operator_two(int *got_token, char **s, t_tr *t, t_tkn *tkn);
void	ft_tkn_quotes(int got_token, char **s, t_tr *t, t_tkn *tkn);
void	ft_tkn_redir_fd(int *got_token, char **s, t_tr *t, t_tkn *tkn);
void	ft_tkn_word_quoted(int got_token, char **s, t_tr *t, t_tkn *tkn);
void	ft_tkn_word_unquoted(int got_token, char **s, t_tr *t, t_tkn *tkn);
void	ft_trim_str_malloc(char **str, char ch_inlcuded, t_tr *t);
void	ft_unlink_heredoc(t_tr *t);
void	ft_update_env(char *env_name, char *update_str, t_tr *t);
int		ft_quotes_status(char *exp, t_tr *t);
void	ft_update_prompt_pwd(t_tr *t);
void	ft_w(int condition, char *cmd, t_tr *t);

void	ft_print_tokens(int line, char *file, t_tr *t);

#endif

