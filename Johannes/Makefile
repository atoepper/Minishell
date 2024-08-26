# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/02 14:26:28 by atoepper          #+#    #+#              #
#    Updated: 2024/08/26 11:11:55 by jweingar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILATION ###
CC      = cc -O2
FLAGS  = -Wall -Wextra -Werror -g

### EXECUTABLE ###
NAME   = test_minishell

### INCLUDES ###
OBJ_PATH  = objs
HEADER = ../incl
SRC_PATH  = ../srcs
LIBFT = ../libft
LIBFT_A = $(LIBFT)/libft.a

### SOURCE FILES ###
SOURCES = 	main_Johannes.c \
			builtins/echo.c \
			execution/exec_external.c \
			execution/exec_builtin.c \
			execution/execute.c \
			builtins/exit.c \
			builtins/pwd.c \
			builtins/cd.c	
#			execution/execute.c \
#			expander/expand.c \
#			parsing/parse.c \
#			tokenizing/tokenize.c

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

all: tmp $(NAME)

$(LIBFT_A):
	@make -C $(LIBFT)

lib:
	@echo "$(GREEN)Creating lib files$(CYAN)"
	@make -C $(LIBFT)

$(NAME): $(LIBFT_A) $(OBJS) 
	@$(CC) $(FLAGS) -L $(LIBFT) -o $@ $^ -lft -lreadline
#	@echo "$(GREEN)Project successfully compiled$(WHITE)"

tmp:
	@mkdir -p $(OBJ_PATH)/builtins
	@mkdir -p $(OBJ_PATH)/execution
#@mkdir -p $(OBJ_PATH)/expander
#@mkdir -p $(OBJ_PATH)/parsing
#@mkdir -p $(OBJ_PATH)/tokenizing
#@mkdir -p $(OBJ_PATH)/signals

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)/minishell.h tmp
	@ $(CC) $(FLAGS) -c -o $@ $<
#	@ echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

run: all
	@./$(NAME)

clean:
#	@ echo "$(GREEN)Supressing libraries files$(CYAN)"
	@ make clean -C $(LIBFT)
	@ rm -rf $(OBJ_PATH)

fclean:
#	@ echo "$(GREEN)Supressing libraries files$(CYAN)"
	@ rm -rf $(OBJ_PATH)
	@ rm -f $(NAME)
	@ make fclean -C $(LIBFT)

re: fclean 
	@ $(MAKE) all

.PHONY: tmp, re, fclean, clean, run