# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 06:51:59 by eluceon           #+#    #+#              #
#    Updated: 2021/05/16 23:38:43 by eluceon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NONE = \033[0;0m
RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address
RM = rm -rf

LIBFT = ./libs/libft/libft.a
LIBFTDIR = ./libs/libft/

NAME = minishell

OBJDIR = ./obj/
HEADERDIR = ./includes/

SRC_MAIN_DIR = ./srcs/main/
SRCS_MAIN = minishell.c
OBJ_MAIN = $(addprefix $(OBJDIR), $(SRCS_MAIN:.c=.o))
HEADER_MAIN = $(addprefix $(HEADERDIR), minishell.h)

SRC_SIGNAL_HANDLERS_DIR = ./srcs/signal_handlers/
SRCS_SIGNAL_HANDLERS = signal_handlers.c
OBJ_SIGNAL_HANDLERS = $(addprefix $(OBJDIR), $(SRCS_SIGNAL_HANDLERS:.c=.o))
HEADER_SIGNAL_HANDLERS = $(addprefix $(HEADERDIR), signal_handlers.h)

SRC_ENVIRONMENT_DIR = ./srcs/environment/
SRCS_ENVIRONMENT = set_environment.c
OBJ_ENVIRONMENT = $(addprefix $(OBJDIR), $(SRCS_ENVIRONMENT:.c=.o))
HEADER_ENVIRONMENT = $(addprefix $(HEADERDIR), environment.h)

# SRC_READ_LINE_DIR = ./srcs/environment/
# SRCS_READ_LINE = read_line.c
# OBJ_READ_LINE = $(addprefix $(OBJDIR), $(SRCS_READ_LINE:.c=.o))
# HEADER_READ_LINE = $(addprefix $(HEADERDIR), read_line.h)

# SRC_PARSING_DIR = ./srcs/parsing/
# SRCS_PARSING =
# OBJ_PARSING = $(addprefix $(OBJDIR), $(SRCS_PARSING:.c=.o))
# HEADER_PARSING = $(addprefix $(HEADERDIR), parsing.h)

# SRC_BUILTINS_DIR = ./srcs/builtins/
# SRCS_BUILTINS =
# OBJ_BUILTINS = $(addprefix $(OBJDIR), $(SRCS_BUILTINS:.c=.o))
# HEADER_BUILTINS = $(addprefix $(HEADERDIR), builtins.h)

# SRC_ERROR_DIR = ./srcs/error/
# SRCS_ERROR =
# OBJ_ERROR = $(addprefix $(OBJDIR), $(SRCS_ERROR:.c=.o))
# HEADER_ERROR = $(addprefix $(HEADERDIR), error.h)

# SRC_EXEC_DIR = ./srcs/exec/
# SRCS_EXEC =
# OBJ_EXEC = $(addprefix $(OBJDIR), $(SRCS_EXEC:.c=.o))
# HEADER_EXEC = $(addprefix $(HEADERDIR), get_next_line.h)

# SRC_UTILS_DIR = ./srcs/utils/
# SRCS_UTILS =
# OBJ_UTILS = $(addprefix $(OBJDIR), $(SRCS_UTILS:.c=.o))
# HEADER_UTILS = $(addprefix $(HEADERDIR), utils.h)

OBJ_ALL = $(OBJ_MAIN) $(OBJ_SIGNAL_HANDLERS) $(OBJ_ENVIRONMENT)

all: make_libft $(NAME)

make_libft:
	$(MAKE) -C $(LIBFTDIR)


$(NAME): $(OBJDIR) $(OBJ_ALL)
	$(CC) $(OBJ_ALL) $(LIBFT) -o $@
	@echo "$(PURPLE) $(NAME) has been created $(NONE)"

$(OBJDIR):
	mkdir -p $(OBJDIR)

##########################
##   Main compilation   ##
##########################

$(OBJ_MAIN): $(OBJDIR)%.o: $(SRC_MAIN_DIR)%.c $(HEADER_MAIN) $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(LIBFTDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN)for main has been created $(NONE)"

###################################
##    Environment compilation    ##
###################################

$(OBJ_ENVIRONMENT): $(OBJDIR)%.o: $(SRC_ENVIRONMENT_DIR)%.c\
					 $(HEADER_ENVIRONMENT) $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(LIBFTDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for environment has been created $(B&W)"

#######################################
##    Signal handlers compilation    ##
#######################################

$(OBJ_SIGNAL_HANDLERS): $(OBJDIR)%.o: $(SRC_SIGNAL_HANDLERS_DIR)%.c $(HEADER_SIGNAL_HANDLERS)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for signal handlers has been created $(B&W)"

#################################
##    Read_line compilation    ##
#################################

# $(OBJ_READ_LINE): $(OBJDIR)%.o: $(SRC_READ_LINE)%.c $(HEADER_READ_LINE)
# 	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
# 	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN)for read_line has been created $(NONE)"

############################
##   Error compilation    ##
############################

# $(OBJ_ERROR): $(OBJDIR)%.o: $(SRC_ERROR_DIR)%.c $(HEADER_ERROR)
# 	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
# 	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN) for error has been created $(NONE)"


############################
##    Exec compilation    ##
############################

# $(OBJ_EXEC): $(OBJDIR)%.o: $(SRC_EXEC_DIR)%.c $(HEADER_EXEC)
# 	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
# 	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for exec has been created $(B&W)"


clean:
	$(MAKE)	clean -C $(LIBFTDIR)
	$(RM) $(OBJDIR)
	@echo "$(RED) $(OBJDIR) has been deleted $(NONE)"

fclean: clean
	$(MAKE)	fclean -C $(LIBFTDIR)
	$(RM) $(NAME)
	@echo "$(RED) $(NAME) has been deleted $(NONE)"

re:	fclean all

.PHONY: all clean fclean re
