# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/24 13:17:37 by alexphil          #+#    #+#              #
#    Updated: 2023/09/27 11:42:02 by alexphil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the executable
NAME 			= 	minishell

# Compiler, compiler flags and linking flags
CC				= 	cc
CFLAGS 			= 	-Wall -Wextra -Werror -Iincludes -Ilibft/include
DFLAGS      	=   -g -fsanitize=address
LFLAGS			=	-lreadline

# Directories for sources files, object files, and the libft library
SRCS_DIR		= 	srcs
LEXER_DIR		=   $(SRCS_DIR)/lexer
PARSER_DIR		=   $(SRCS_DIR)/parser
EXPENDER_DIR	=   $(SRCS_DIR)/expender
EXECTOR_DIR		=   $(SRCS_DIR)/executor
LIBFT_DIR 		= 	libft
BUILD_DIR 		= 	build

# Define the source files
MAIN_FILE		=	main.c
LEXER_FILES		= 	
PARSER_FILES	=	
EXPENDER_FILES	=
EXECUTOR_FILES	=

# Define the path of the sources files 
SRC_MAIN		= 	$(addprefix $(SRCS_DIR)/,$(MAIN_FILE))
SRC_LEXER   	=	$(addprefix $(LEXER_DIR)/, $(LEXER_FILES))
SRC_PARSER  	=	$(addprefix $(PARSER_DIR)/, $(PARSER_FILES))
SRC_EXPANDER  	=	$(addprefix $(EXPANDER_DIR)/, $(EXPENDER_FILES))
SRC_EXECUTOR 	=	$(addprefix $(EXECUTOR_DIR)/, $(EXECUTOR_FILES))

# Derive object files from .c files in the build directory
OBJS 			= 	$(patsubst $(SRCS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_MAIN)) \
					$(patsubst $(LEXER_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_LEXER)) \
					$(patsubst $(PARSER_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_PARSER)) \
					$(patsubst $(EXPANDER_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_EXPAND)) \
					$(patsubst $(EXECUTOR_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_EXECUTE))

# Rules to build the objects from the sources 
$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(LEXER_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(PARSER_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(EXPENDER_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(EXECUTOR_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the executable from the objects and the libft library
$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

# Rule to build the libft library
$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

# Phony target to build the libft library
libft:
	make -C $(LIBFT_DIR)

# Phony target to build the libft library and the executable
all: libft $(NAME)

# Phony target to clean the object files
clean:
	rm -rf $(BUILD_DIR)
	make -C $(LIBFT_DIR) clean

# Phony target to remove the executable and build/debug objects
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	rm -rf *.dSYM

# Phony target to perform a full re-build
re: fclean all

# Rule to build with debug flags
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: re

# --silent flag disables echoing of commands on both MacOS and Linux
MAKEFLAGS += --silent

# Phony targets for make
.PHONY: all libft clean fclean re debug