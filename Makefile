# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 06:51:59 by eluceon           #+#    #+#              #
#    Updated: 2021/05/18 15:36:42 by lmellos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NONE = \033[0;0m
RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror #-fsanitize=address # Need to delete flag -g and -fsanitize=address before defending the project
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

SRC_UTILS_DIR = ./srcs/utils/
SRCS_UTILS = duplicate_string_array.c
OBJ_UTILS = $(addprefix $(OBJDIR), $(SRCS_UTILS:.c=.o))
HEADER_UTILS = $(addprefix $(HEADERDIR), utils.h)

# SRC_TERMCAP_COMMANDS_DIR = ./srcs/termcap_commands/
# SRCS_TERMCAP_COMMANDS = termcap_commands.c
# OBJ_TERMCAP_COMMANDS = $(addprefix $(OBJDIR), $(SRCS_TERMCAP_COMMANDS:.c=.o))
# HEADER_TERMCAP_COMMANDS = $(addprefix $(HEADERDIR), termcap_commands.h)

 SRC_PARSING_DIR = ./srcs/parsing/
 SRCS_PARSING = parsing.c
 OBJ_PARSING = $(addprefix $(OBJDIR), $(SRCS_PARSING:.c=.o))
 HEADER_PARSING = $(addprefix $(HEADERDIR), parsing.h)

# SRC_BUILTINS_DIR = ./srcs/builtins/
# SRCS_BUILTINS =
# OBJ_BUILTINS = $(addprefix $(OBJDIR), $(SRCS_BUILTINS:.c=.o))
# HEADER_BUILTINS = $(addprefix $(HEADERDIR), builtins.h)

# SRC_error_handlers_HANDLERS_DIR = ./srcs/error_handlers/
# SRCS_error_handlers_HANDLERS =
# OBJ_error_handlers_HANDLERS = $(addprefix $(OBJDIR),\
								$(SRCS_error_handlers_HANDLERS:.c=.o))
# HEADER_error_handlers_HANDLERS = $(addprefix $(HEADERDIR), error_handlers.h)

# SRC_EXEC_COMMANDS_COMMANDS_DIR = ./srcs/exec_commands/
# SRCS_EXEC_COMMANDS =
# OBJ_EXEC_COMMANDS = $(addprefix $(OBJDIR), $(SRCS_EXEC_COMMANDS:.c=.o))
# HEADER_EXEC_COMMANDS = $(addprefix $(HEADERDIR), exec_commands.h)


OBJ_ALL = $(OBJ_MAIN) $(OBJ_SIGNAL_HANDLERS) $(OBJ_ENVIRONMENT) $(OBJ_UTILS) $(OBJ_PARSING)

all: make_libft $(NAME)

make_libft:
	$(MAKE) -C $(LIBFTDIR)


$(NAME): $(OBJDIR) $(OBJ_ALL)
	$(CC) -ltermcap $(OBJ_ALL) $(LIBFT) -o $@
	@echo "$(PURPLE) $(NAME) has been created $(NONE)"

$(OBJDIR):
	mkdir -p $(OBJDIR)

##########################
##   Main compilation   ##
##########################

$(OBJ_MAIN): $(OBJDIR)%.o: $(SRC_MAIN_DIR)%.c $(HEADER_MAIN) $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(LIBFTDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN)for Main has been created $(NONE)"

############################
##   Parser compilation   ##
############################

$(OBJ_PARSING): $(OBJDIR)%.o: $(SRC_PARSING_DIR)%.c $(HEADER_MAIN) $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(LIBFTDIR) $(LIBS) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN)for Main has been created $(NONE)"

###################################
##    Environment compilation    ##
###################################

$(OBJ_ENVIRONMENT): $(OBJDIR)%.o: $(SRC_ENVIRONMENT_DIR)%.c\
					 $(HEADER_ENVIRONMENT) $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(LIBFTDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for Environment has been created $(NONE)"

#######################################
##    Signal handlers compilation    ##
#######################################

$(OBJ_SIGNAL_HANDLERS): $(OBJDIR)%.o: $(SRC_SIGNAL_HANDLERS_DIR)%.c $(HEADER_SIGNAL_HANDLERS)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for Signal handlers has been created $(NONE)"

###############################
##     Utils compilation     ##
###############################

$(OBJ_UTILS): $(OBJDIR)%.o: $(SRC_UTILS_DIR)%.c $(HEADER_UTILS)  $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(LIBFTDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for Utils has been created $(NONE)"

########################################
##    termcap_commands compilation    ##
########################################

# $(OBJ_TERMCAP_COMMANDS): $(OBJDIR)%.o: $(SRC_TERMCAP_COMMANDS)%.c $(HEADER_TERMCAP_COMMANDS)
# 	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
# 	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN)for termcap_commands has been created $(NONE)"

#####################################
##   error_handlers compilation    ##
#####################################

# $(OBJ_error_handlers_HANDLERS): $(OBJDIR)%.o: $(SRC_error_handlers_HANDLERS_DIR)%.c $(HEADER_error_handlers_HANDLERS)
# 	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
# 	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN) for error_handlers has been created $(NONE)"


###################################
##   exec_commands compilation   ##
###################################

# $(OBJ_EXEC_COMMANDS): $(OBJDIR)%.o: $(SRC_EXEC_COMMANDS_DIR)%.c $(HEADER_EXEC_COMMANDS)
# 	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@
# 	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for exec has been created $(NONE)"

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
