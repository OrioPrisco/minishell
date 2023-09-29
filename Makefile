# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: OrioPrisco <47635210+OrioPrisco@users      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 11:29:48 by OrioPrisc         #+#    #+#              #
#    Updated: 2023/09/29 12:55:15 by OrioPrisc        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	cc

SRC				=	minishell.c \
					tokens_utils.c \
					prompt_utils.c \
					error_utils.c \
					history.c \
					signal_utils.c \
					ast_utils.c \
					utils.c \
					redirects.c \
					pipe_loop.c \
					fork_utils.c \
					fork_utils_2.c \
					access_utils.c \
					builtins/builtin_chk_sel.c \
					builtins/builtin_commands.c \
					builtins/builtin_commands_2.c \
					builtins/builtin_export.c \
					builtins/builtin_cd.c \
					child_proc_utils.c \
					path_utils.c\
					parser/parse_redirect.c \
					parser/parse_pipe.c \
					parser/parse_text.c \
					parser/parse_wildcard.c \
					parser/wildcards.c \
					parser/lexer.c \
					parser/lex_var.c \
					parser/merge_tokens.c \
					parser/parser.c \
					parser/heredoc.c \
					ft_readline.c \
					env_var/get_var.c \
					env_var/utils.c \
					env_var/set_var.c \

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
	@mkdir -p $(@D)
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
