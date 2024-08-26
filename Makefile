# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/02 14:26:28 by atoepper          #+#    #+#              #
#    Updated: 2024/08/26 11:31:07 by atoepper         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILATION ###
CC      = gcc -O2
FLAGS  = -Wall -Wextra -Werror -g

### EXECUTABLE ###
NAME   = minishell

### INCLUDES ###
OBJ_PATH  = objs
HEADER = incl
SRC_PATH  = srcs
LIBFT = libft

### SOURCE FILES ###
SOURCES = main.c \
			builtins/cd.c \
			builtins/echo.c \
			builtins/env.c \
			builtins/exit.c \
			builtins/pwd.c \
			env/env.c \
			env/envlist.c \
			execution/execute.c \
			execution/exec_builtin.c \
			execution/exec_external.c \
			expander/expand.c \
			parsing/parse.c \
			tokenizing/tokenize.c \
			tokenizing/linetolist.c \
			tokenizing/token_utils.c \
			utils/utils.c 

### OBJECTS ###

SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

### COLORS ###
NOC         = \033[0m
RED         = \033[1;31m
GREEN       = \033[1;32m
BLUE        = \033[1;34m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

### RULES ###

all: lib tmp $(NAME)

lib:
	@echo "$(GREEN)Creating lib files$(CYAN)"
	@make -C $(LIBFT)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -L $(LIBFT) -o $@ $^ -lft -lreadline
	@echo "$(GREEN)Project successfully compiled"

tmp:
	@mkdir -p $(OBJ_PATH)/builtins
	@mkdir -p $(OBJ_PATH)/env
	@mkdir -p $(OBJ_PATH)/execution
	@mkdir -p $(OBJ_PATH)/expander
	@mkdir -p $(OBJ_PATH)/parsing
	@mkdir -p $(OBJ_PATH)/tokenizing
	@mkdir -p $(OBJ_PATH)/signals
	@mkdir -p $(OBJ_PATH)/utils

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)/$(NAME).h tmp
	@$(CC) $(FLAGS) -c -o $@ $<
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

clean:
	@echo "$(GREEN)Supressing libraries files$(CYAN)"
	@make clean -C $(LIBFT)
	@rm -rf $(OBJ_PATH)

fclean:
	@echo "$(GREEN)Supressing libraries files$(CYAN)"
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean 
	@$(MAKE) all

.PHONY: temporary, re, fclean, clean