# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rponomar <rponomar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 18:28:54 by rponomar          #+#    #+#              #
#    Updated: 2025/02/06 13:40:40 by rponomar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

ifeq ($(origin CC), default)
CC = cc
endif
ifeq ($(origin CC), envirnoment override)
CC = cc
endif

FLAGS_WWW = -Wall -Wextra -g
FLAGS_OPTIM = -O0
FLAGS_LIBS = -lreadline
override CFLAGS += $(FLAGS_LIBS) $(FLAGS_OPTIM) $(FLAGS_WWW)

ifndef VERBOSE
MAKEFLAGS += --no-print-directory
endif

SRCS =	\
ft_minishell_00_main.c	\
ft_minishell_01_signals_start.c	\
ft_minishell_02_cleanup.c	\
ft_minishell_03_error_message.c	\
ft_minishell_04_error_message.c	\
ft_minishell_05_error_list.c	\
ft_minishell_06_tracker.c	\
ft_minishell_07_argc_prog_shlvl.c	\
ft_minishell_08_signals.c	\
ft_minishell_09_signals_default_ignore.c	\
ft_minishell_10_signals_all.c	\
ft_minishell_11_signals_exit_status.c	\
ft_minishell_12_path.c	\
ft_minishell_13_prompt.c	\
ft_minishell_14_prompt_update.c	\
ft_minishell_15_invalid_line.c	\
ft_minishell_16_tokens.c	\
ft_minishell_17_tokens.c	\
ft_minishell_18_tokens.c	\
ft_minishell_19_fields.c	\
ft_minishell_20_fields.c	\
ft_minishell_21_heredoc.c	\
ft_minishell_22_heredoc_sig.c	\
ft_minishell_23_execute.c	\
ft_minishell_24_execute_pipe.c	\
ft_minishell_25_expand_var.c	\
ft_minishell_26_expand_var.c	\
ft_minishell_27_expand_var_heredoc.c	\
ft_minishell_28_expand_split.c	\
ft_minishell_29_expand_split.c	\
ft_minishell_30_expand_wildcards.c	\
ft_minishell_31_wildcards_mask.c	\
ft_minishell_32_cwd_filenames.c	\
ft_minishell_33_wildcards_delete_token.c	\
ft_minishell_34_expand_quotes.c	\
ft_minishell_35_redir.c \
ft_minishell_36_redir_stdin_stdout.c \
ft_minishell_37_redir_delete_tkns.c \
ft_minishell_38_redir_close_files.c \
ft_minishell_39_execute_bltin.c	\
ft_minishell_40_execute_cmds.c	\
ft_minishell_41_execute_cmds_level.c	\
ft_minishell_42_execute_pipe_cmd.c	\
ft_minishell_43_execute_pipe_execve.c	\
ft_minishell_44_execute_pipe_cmd.c	\
ft_minishell_45_execute_is_directory_is_execfile.c	\
ft_minishell_46_execute_exit_status.c	\
ft_minishell_47_bltin_chdir.c	\
ft_minishell_48_bltin_chdir_oldpwd_home_empty.c	\
ft_minishell_49_bltin_chdir_curpath.c	\
ft_minishell_50_bltin_chdir_curpath.c	\
ft_minishell_51_bltin_chdir_max_path.c	\
ft_minishell_52_bltin_echo.c	\
ft_minishell_53_bltin_env.c	\
ft_minishell_54_bltin_exit.c	\
ft_minishell_55_bltin_export.c	\
ft_minishell_56_bltin_pwd.c	\
ft_minishell_57_bltin_unset.c	\
ft_minishell_58_utils_malloc.c	\
ft_minishell_59_utils_exec.c	\
ft_minishell_60_utils_env_quotes.c	\
ft_minishell_61_utils_nextexec_atoifd_printtkn.c	\
ft_minishell_62_utils_free.c	\
ft_minishell_63_utils_errno_msg_std_close.c	\
ft_minishell_64_utils_empty_str.c

OBJS = $(SRCS:.c=.o)
HDRS = ft_minishell.h

LIB_DIR_LIBFT = ./libs/libft/
LIB_LIBFT = $(addprefix $(LIB_DIR_LIBFT), libft.a)

INCLUDES = -I. -I$(LIB_DIR_LIBFT)

START = ft_minishell_start_msg
START_BONUS = ft_minishell_start_msg_bonus

.PHONY:	all
all: $(NAME)

$(START):	$(SRCS) $(HDRS) Makefile
	@printf "\n\t\t\033[33m  MINISHELL:\tcompiling...\033[0m\n\n"

$(OBJS):	%.o:	%.c	
	@$(CC) $(CFLAGS) $(FLAGS_WWW) $(FLAGS_OPTIM) -c $< $(INCLUDES) -o $@ && printf "\033[33m  compiling, assembling OBJ:\t$(basename $(notdir $@))\033[0m\n"
	@touch $(START)

$(LIB_LIBFT):
	@$(MAKE) -C $(LIB_DIR_LIBFT)
	@touch $(START)

$(NAME):	$(START) $(LIB_LIBFT) $(OBJS) $(HDRS) Makefile
	@touch $(START)
	@$(CC) $(OBJS) $(CFLAGS) $(LIB_LIBFT) $(HEADERS) -o $(NAME) && printf "\n\033[33m\tlinking EXECUTABLE:\t$(notdir $@)\033[0m\n\n"
	@printf "\t\t\033[32mMINISHELL:\tcompiled\033[0m\n\n\n"

.PHONY:	clean
clean:
	@printf "\n\n\t\t\033[33m  MINISHELL:\tcleaning...\033[0m\n"
	@rm -f $(OBJS) $(START) $(START_BONUS)
	@$(MAKE) -C $(LIB_DIR_LIBFT) clean
	@printf "\t\t\033[32m  MINISHELL:\tcleaning finished\033[0m\n"	

.PHONY:	fclean
fclean:	clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIB_DIR_LIBFT) fclean
	@printf "\n\t\t\033[32m  MINISHELL:\tfclean finished\033[0m\n\n\n"

.PHONY:	re
re:	fclean all