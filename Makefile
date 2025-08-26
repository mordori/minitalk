# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/25 13:37:28 by myli-pen          #+#    #+#              #
#    Updated: 2025/08/25 23:22:38 by myli-pen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_1		=server
NAME_2		=client

LIBFT		=$(DIR_LIBFT)libft.a

CC			=cc
CFLAGS		=-Wall -Wextra -Werror -Wunreachable-code -O3
LDFLAGS		=
MAKEFLAGS	+= --no-print-directory

DIR_INC		=inc/
DIR_SRC		=src/
DIR_LIB		=lib/
DIR_OBJ		=obj/
DIR_DEP		=dep/
DIR_SERVER	=server/
DIR_CLIENT	=client/

DIR_LIBFT		=$(DIR_LIB)libft/
DIR_INC_LIBFT	=$(DIR_LIBFT)$(DIR_INC)

DIR_INC_SERVER	=$(DIR_INC)$(DIR_SERVER)
DIR_SRC_SERVER	=$(DIR_SRC)$(DIR_SERVER)
DIR_OBJ_SERVER	=$(DIR_OBJ)$(DIR_SERVER)

DIR_INC_CLIENT	=$(DIR_INC)$(DIR_CLIENT)
DIR_SRC_CLIENT	=$(DIR_SRC)$(DIR_CLIENT)
DIR_OBJ_CLIENT	=$(DIR_OBJ)$(DIR_CLIENT)

HEADERS		=$(addprefix -I , \
				$(DIR_INC_SERVER) $(DIR_INC_CLIENT) $(DIR_INC_LIBFT))
SRCS_1		=$(addprefix $(DIR_SRC_SERVER), \
				server.c server_utils.c)
SRCS_2		=$(addprefix $(DIR_SRC_CLIENT), \
				client.c client_utils.c)
OBJS_1		=$(patsubst $(DIR_SRC_SERVER)%.c, $(DIR_OBJ_SERVER)%.o, $(SRCS_1))
OBJS_2		=$(patsubst $(DIR_SRC_CLIENT)%.c, $(DIR_OBJ_CLIENT)%.o, $(SRCS_2))
OBJS		=$(OBJS_1) $(OBJS_2)
DEPS		=$(patsubst $(DIR_OBJ)%.o, $(DIR_DEP)%.d, $(OBJS))

BLUE		=\033[1;34m
YELLOW		=\033[1;33m
GREEN		=\033[1;32m
RED			=\033[1;31m
COLOR		=\033[0m

all: $(LIBFT) $(NAME_1) $(NAME_2)

$(LIBFT):
	@echo "$(GREEN) [+]$(COLOR) compiling libft.a"
	@make -C $(DIR_LIBFT)

$(NAME_1): $(OBJS_1)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME_1) $(OBJS_1) $(LIBFT)
	@echo "$(YELLOW) [✔] $(NAME_1) created$(COLOR)"

$(NAME_2): $(OBJS_2)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME_2) $(OBJS_2) $(LIBFT)
	@echo "$(YELLOW) [✔] $(NAME_2) created$(COLOR)"

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@mkdir -p $(dir $@) $(patsubst $(DIR_OBJ)%, $(DIR_DEP)%, $(dir $@))
	@$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(patsubst $(DIR_OBJ)%.o, $(DIR_DEP)%.d, $@) $(HEADERS)
	@echo "$(GREEN) [+]$(COLOR) compiling $@"

clean:
	@if [ -d "$(DIR_OBJ)" ]; then \
		rm -rf $(DIR_OBJ) $(DIR_DEP); \
		echo "$(RED) [-]$(COLOR) removed $(DIR_OBJ)"; \
		echo "$(RED) [-]$(COLOR) removed $(DIR_DEP)"; \
	fi
	@make -C $(DIR_LIBFT) clean

fclean: clean
	@make -C $(DIR_LIBFT) fclean
	@if [ -e "$(NAME_1)" ]; then \
		rm -f $(NAME_1); \
		echo "$(RED) [-]$(COLOR) removed $(NAME_1)"; \
	fi
	@if [ -e "$(NAME_2)" ]; then \
		rm -f $(NAME_2); \
		echo "$(RED) [-]$(COLOR) removed $(NAME_2)"; \
	fi

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJS) $(DEPS)

-include $(DEPS)
