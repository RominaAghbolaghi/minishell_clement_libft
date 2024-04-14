# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: romina <romina@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 13:55:38 by cbiteau           #+#    #+#              #
#    Updated: 2024/04/11 11:26:12 by romina           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC 		= clang
CFLAGS	= -Wall -Werror -Wextra -g
LIBFT	= libft/libft.a
AUTHOR	= Clement & Romina - The Mini Crushers
DATE	= 14/03/2024

SRCS		= 	input_manager/buffer_manager.c input_manager/escape_code.c \
				input_manager/history.c input_manager/input_handle2.c \
				input_manager/input_handle3.c input_manager/input_handle.c \
				input_manager/input_manager.c input_manager/input_utils.c \
				input_manager/prompt.c \
				parser/dollar.c parser/lexer_parts.c parser/double_quote.c \
				parser/error_detector.c parser/error_detector2.c \
				parser/find_bin.c parser/dyn_parsing.c \
				parser/lexer_utils.c parser/make_word.c parser/command.c \
				parser/parser.c parser/destroyer.c parser/lexer.c \
				parser/command_parts.c \
				errors.c var.c \
				builtin/cd.c builtin/cd1.c builtin/exit.c builtin/exit2.c \
				builtin/echo.c builtin/env.c builtin/unset.c builtin/pwd.c \
				builtin/export.c builtin/export2.c builtin/export3.c\
				exec/prepare_exec.c exec/redirection.c exec/build_args.c\
				exec/redirection_utils.c exec/exec_utils.c exec/exec_utils2.c \
				exec/execution_rules.c exec/exec.c exec/child.c \
				exec/build_args_util.c minishell.c

MAIN		= main.c

OBJ_MAIN	= $(addprefix objs/, ${MAIN:.c=.o})
OBJS		= $(addprefix objs/, ${SRCS:.c=.o})
OBJS_TESTS	= $(addprefix objs_tests/, ${SRCS_TESTS:.c=.o})

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

OK_STRING    = "[OK]"
ERROR_STRING = "[KO]"
WARN_STRING  = "[WARN]"
COM_STRING   = "Compiling"

define run
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
if [ $$RESULT -ne 0 ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
elif [ -s $@.log ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
else  \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
fi; \
cat $@.log; \
rm -f $@.log; \
exit $$RESULT
endef

all:	header $(NAME)

header:
	@printf "%b" "$(OK_COLOR)"
	@echo "        ___  _____ ___  ___      _        "
	@echo "       /   |/ __  \|  \/  |     | |       "
	@echo "      / /| |\`' / /'| .  . | __ _| | _____ "
	@echo "     / /_| |  / /  | |\/| |/ _\` | |/ / _ \\"
	@echo "     \___  |./ /___| |  | | (_| |   <  __/"
	@echo "         |_/\_____/\_|  |_/\__,_|_|\_\___|"
	@echo
	@printf "%b" "$(OBJ_COLOR)Name:	$(WARN_COLOR)$(NAME)\n"
	@printf "%b" "$(OBJ_COLOR)Author:	$(WARN_COLOR)$(AUTHOR)\n"
	@printf "%b" "$(OBJ_COLOR)Date: 	$(WARN_COLOR)$(DATE)\n\033[m"
	@echo

$(NAME): 	$(LIBFT) ${OBJS} ${OBJ_MAIN}
			@$(call run,$(CC) $(CFLAGS) -o $@ ${OBJS} ${OBJ_MAIN} -L./libft -lft)

objs/%.o: 	srcs/%.c
			@mkdir -p $(dir $@)
			@$(call run,$(CC) $(CFLAGS) -c $< -o $@)

$(LIBFT):
			@$(call run,make -sC ./libft libft.a)

clean:		header
			@rm -rf objs
			@make -sC ./libft clean
			@printf "%-53b%b" "$(COM_COLOR)clean:" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"

fclean:		header clean
			@rm -rf $(NAME)
			@make -sC ./libft fclean
			@printf "%-53b%b" "$(COM_COLOR)fclean:" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"

re:			fclean all

.PHONY:		all clean fclean re libft header
