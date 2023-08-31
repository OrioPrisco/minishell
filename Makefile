# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 11:29:48 by OrioPrisc         #+#    #+#              #
#    Updated: 2023/08/31 15:22:15 by dpentlan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	cc

SRC				=	minishell.c \
					split_to_tokens.c \
					validate_tokens.c \
					get_env_var.c \
					expand_vars.c \
					split_dquoted_tokens.c \
					merge_tokens.c \
					tokens_utils.c \
					tokens_utils_2.c \
					parse_line.c \
					prompt_utils.c \
					error_utils.c \
					history.c \
					signal_utils.c \
					ast_utils.c \
					utils.c \
					fd_utils.c \
					fd_utils_2.c \
					fd_utils_3.c \
					pipe_loop.c \
					fork_utils.c \
					fork_utils_2.c \
					heredoc_utils.c \
					access_utils.c \
					access_utils_2.c \
					child_proc_utils.c \
					path_utils.c\
					wildcards.c \

NAME			=	minishell

OBJ_FOLDER		=	objs/

CFLAGS			=	-Wall -Wextra -Werror -g

SRC_FOLDER		=	srcs/

HEADERS_FOLDER	=	includes/\
					libft/includes/\

LIBS			=	libft/libft.a\
					libft/libftprintf.a\
					libft/libgetnextline.a\

#here to ensure things get pull properly
SUBMODULES		=	libft/.git\
					libft/ftprintf/.git\
					libft/getnextline/.git\

LFLAGS			=	-Llibft -lreadline -lftprintf -lvector -lgetnextline -lft

DEPENDS		:=	$(patsubst %.c,$(OBJ_FOLDER)%.d,$(SRC))
OBJS		:=	$(patsubst %.c,$(OBJ_FOLDER)%.o,$(SRC))
COMMANDS	:=	$(patsubst %.c,$(OBJ_FOLDER)%.cc,$(SRC))

all: $(NAME) compile_commands.json

-include $(DEPENDS)

$(SUBMODULES) :
	git submodule update --init --recursive libft

%.a: $(SUBMODULES)
	make -C $(@D)

$(NAME): $(LIBS) $(OBJS) $(SUBMODULES)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $@

COMP_COMMAND = $(CC) -c $(CFLAGS) $(addprefix -I,$(HEADERS_FOLDER)) -MMD -MP $< -o $@
CONCAT = awk 'FNR==1 && NR!=1 {print ","}{print}'

$(OBJ_FOLDER)%.o $(OBJ_FOLDER)%.cc: $(SRC_FOLDER)%.c Makefile $(SUBMODULES)
	$(COMP_COMMAND)
	@printf '{\n\t"directory" : "$(shell pwd)",\n\t"command" : "$(COMP_COMMAND)",\n\t"file" : "$<"\n}' > $(OBJ_FOLDER)$*.cc

compile_commands.json : $(COMMANDS) Makefile
	@echo "Making compile_commands.json"
	@echo "[" > compile_commands.json
	@$(CONCAT) $(COMMANDS) >> compile_commands.json
	@echo "]" >> compile_commands.json

clean: $(SUBMODULES)
	rm -f $(OBJS) $(DEPENDS) $(COMMANDS)
	for lib in $(shell dirname $(LIBS)); do \
		make -C $$lib clean; \
	done

fclean: clean $(SUBMODULES)
	rm -f $(NAME) compile_commands.json
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re bonus
.SUFFIXES:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules
