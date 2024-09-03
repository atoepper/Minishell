# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 14:20:11 by atoepper          #+#    #+#              #
#    Updated: 2024/09/03 15:08:17 by jweingar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS =  \
		ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_freearray.c \
		ft_hextoi.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_ishex.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdup.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strndup.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_printf.c \
		ft_putchar_printf.c \
		ft_puthexlow_printf.c \
		ft_puthexup_printf.c \
		ft_putnbr_printf.c \
		ft_putptr_printf.c \
		ft_putstr_printf.c \
		ft_putuint_printf.c \
		get_next_line_bonus.c \
		get_next_line_utils_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c
INCL = libft.h
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra -fPIE
AR = ar -rcs

all: $(NAME)

$(NAME): $(OBJS)
		@$(AR) $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean $(NAME)

.PHONY:  all bonus clean fclean re