NAME			=	minishell

#-------------------PATH-----------------------------

SOURCES			= srcs/

HEADER_PWD		= 


#-------------------COMPILATION----------------------

CC				=	cc
FLAGS			=	-Wall -Werror -Wextra
# FLAGS			=	-Wall -Werror -Wextra -g
# FLAGS			=	-Wall -Werror -Wextra -fsanitize=address

#-------------------SOURCES FILES----------------------
HEADERS			=	$(HEADER_PWD)minishell.h

H_LIB 			= 

MAIN			=	main.c
	
SRCS			=	
				
#-------------------OBJECTS----------------------

OBJS			=	$(SRCS:.c=.o) 

MAIN_OBJ		=	$(MAIN:.c=.o)

#-------------------HEADERS----------------------

I_HEADER		=	$(addprefix( -include, $(HEADERS)))

I_BONUS_HEADER	=	$(addprefix( -include, $(BONUS_HEADERS)))

#-------------------COLORS-----------------------

RED				=	\x1b[31m

YELLOW			=	\x1b[33m

GREEN			=	\x1b[32m

NO_COLOR		=	\x1b[0m

BOLD			= 	\x1b[1m

BOLD_OFF		=	\x1b[21m


#-------------------RULES-----------------------
all:	$(NAME)

%.o: %.c
	@printf "$(YELLOW)Generating $(NAME) objects... %-45.45s\r$(NO_COLOR)" $@
	@$(CC) $(FLAGS) $(I_HEADER) $(I_BONUS_HEADER) -c $< -o $@

$(NAME):	$(OBJS) $(MAIN_OBJ)
	@printf "$(GREEN)Linking $(NAME)... %45s\r$(NO_COLOR)" " "
	@$(CC) $(FLAGS) $(OBJS) $(MAIN_OBJ) -lreadline -o $(NAME)
	@echo "\n$(GREEN)$(BOLD)Enjoy!$(BOLD_OFF)$(NO_COLOR)"
	
clean:
	@echo "$(RED)Deleting objects...$(NO_COLOR)"
	@rm -rf $(OBJS) $(MAIN_OBJ)

fclean:	clean
	@echo "$(RED)Deleting executables...$(NO_COLOR)"
	@rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re