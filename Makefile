# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adupin <adupin@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/24 13:17:37 by alexphil          #+#    #+#              #
#    Updated: 2023/10/27 14:42:35 by adupin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the executable
NAME 			= 	minishell

# Compiler, compiler flags and linking flags
# Readline include give access to rl_replace_line
ifeq ($(USER), alexphil)
	READLINE_DIR = /Users/$(USER)/homebrew/opt/readline
else
	READLINE_DIR = /Users/$(USER)/Applications/homebrew/opt/readline
endif
CC				= 	cc
CFLAGS 			= 	-Wall -Wextra -Werror -Iincludes -Ilibft/include -I$(READLINE_DIR)/include -g 
DFLAGS      	=   -fsanitize=address
LFLAGS			=	-lreadline -lhistory -L $(READLINE_DIR)/lib

# Directories for sources files, object files, and the libft library
SRCS_DIR		= 	srcs
LEXER_DIR		=   $(SRCS_DIR)/lexer
PARSER_DIR		=   $(SRCS_DIR)/parser
EXPANDER_DIR	=   $(SRCS_DIR)/expander
EXECUTOR_DIR	=   $(SRCS_DIR)/executor
BUILTINS_DIR 	=   $(SRCS_DIR)/builtins
UTILS_DIR		=	$(SRCS_DIR)/utils
ERRORS_DIR		=	$(SRCS_DIR)/errors
LIBFT_DIR 		= 	libft
BUILD_DIR 		= 	build

# Define the source files
MAIN_FILE		=	main.c
LEXER_FILES		= 	lexer.c \
					lexer_utils.c \
					lexer_free.c \
					nodes.c
PARSER_FILES	=	parser.c \
					counters.c \
					cmds.c \
					redirects.c \
					print.c
EXPANDER_FILES	=	expander.c
EXECUTOR_FILES	=
BUILTINS_FILES 	=	builtins.c \
					export.c \
					ms_echo.c
UTILS_FILES		=	xmalloc.c \
					environ.c
ERRORS_FILES	=	

# Defining the paths of the sources files 
SRC_MAIN		= 	$(addprefix $(SRCS_DIR)/,$(MAIN_FILE))
SRC_LEXER   	=	$(addprefix $(LEXER_DIR)/, $(LEXER_FILES))
SRC_PARSER  	=	$(addprefix $(PARSER_DIR)/, $(PARSER_FILES))
SRC_EXPANDER  	=	$(addprefix $(EXPANDER_DIR)/, $(EXPANDER_FILES))
SRC_EXECUTOR 	=	$(addprefix $(EXECUTOR_DIR)/, $(EXECUTOR_FILES))
SRC_BUILTINS	=	$(addprefix $(BUILTINS_DIR)/, $(BUILTINS_FILES))
SRC_UTILS		=	$(addprefix $(UTILS_DIR)/, $(UTILS_FILES))
SRC_ERRORS		=	$(addprefix $(ERRORS_DIR)/, $(ERRORS_FILES))

# Deriving objects from .c files in the build directory
OBJS 			= 	$(patsubst $(SRCS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_MAIN)) \
					$(patsubst $(LEXER_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_LEXER)) \
					$(patsubst $(PARSER_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_PARSER)) \
					$(patsubst $(EXPANDER_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_EXPANDER)) \
					$(patsubst $(EXECUTOR_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_EXECUTOR)) \
					$(patsubst $(BUILTINS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_BUILTINS)) \
					$(patsubst $(UTILS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_UTILS)) \
					$(patsubst $(ERRORS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_ERRORS))

# Display toolbox
RED				=	\x1b[31m
YELLOW			=	\x1b[33m
GREEN			=	\x1b[32m
NO_COLOR		=	\x1b[0m
BOLD			= 	\x1b[1m
BOLD_OFF		=	\x1b[21m

# Rules to build the objects from the sources 
$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(LEXER_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(PARSER_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(EXPANDER_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(EXECUTOR_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(BUILTINS_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(ERRORS_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the executable from the objects and the libft library
$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	@echo "$(YELLOW)Linking $(NAME)... $(NO_COLOR)"
	@$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^
	@echo "$(GREEN)$(BOLD)Enjoy!$(BOLD_OFF)$(NO_COLOR)"

# Rule to build the libft library
$(LIBFT_DIR)/libft.a:
	@make -C $(LIBFT_DIR)

# Phony target to build the libft library
libft:
	@make -C $(LIBFT_DIR)

# Phony target to build the libft library and the executable
all: libft $(NAME)

# Phony target to clean the object files
clean:
	@echo "$(RED)Deleting objects...$(NO_COLOR)"
	@rm -rf $(BUILD_DIR)
	@make -C $(LIBFT_DIR) clean

# Phony target to remove the executable and build/debug objects
fclean: clean
	@echo "$(RED)Deleting executables...$(NO_COLOR)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@rm -rf *.dSYM

# Phony target to perform a full re-build
re: fclean all

# Rule to build with debug flags
debug: CFLAGS += $(DFLAGS) 
debug: re

# --silent flag disables echoing of commands on both MacOS and Linux
#MAKEFLAGS += --silent

# Phony targets for make
.PHONY: all libft clean fclean re debug