# Colors
RESET			= "\033[0m"
BLACK    		= "\033[30m"    # Black
RED      		= "\033[31m"    # Red
GREEN    		= "\033[32m"    # Green
YELLOW   		= "\033[33m"    # Yellow
BLUE     		= "\033[34m"    # Blue
MAGENTA  		= "\033[35m"    # Magenta
CYAN     		= "\033[36m"    # Cyan
WHITE    		= "\033[37m"    # White

# Compiler
EXEC			= minishell
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -MMD -MP -g3
CFLAGS_DEBUG	= CFLAGS -g3
MAKE			= make -sC
MKDIR			= mkdir -p
RM				= rm -rf

# Includes
INCLUDE_DIR 	= include
INCLUDES		= -I$(INCLUDE_DIR)

# Sources
SRC_DIR			= src
SRC_FILES		= main.c \
				  debug.c \
				  lexer.c \
				  parser.c \
				  utils.c \
				  lexer_utils.c

# Libs
LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a
INCLUDES		+= -I$(LIBFT_DIR)
LDLIBS  	    = -lft -lreadline -L$(LIBFT_DIR)

# Object files
OBJ_DIR			= objs
OBJ_FILES		= $(SRC_FILES:.c=.o)
OBJS			= $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

# Dependencies
DEPS			= $(OBJ_FILES:.o=.d)
-include		$(DEPS)

all : $(LIBFT) $(OBJ_DIR) $(EXEC)

$(LIBFT) :
	@echo $(CYAN) " - Making libft..." $(RESET)
	@$(MAKE) $(LIBFT_DIR)
	@echo $(YELLOW) " - Made libft!" $(RESET)

$(OBJ_DIR) :
	@$(MKDIR) $(OBJ_DIR)

$(EXEC) : $(OBJS) Makefile
	@echo $(GREEN) " - Compiling $(EXEC)..." $(RESET)
	@$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o $(EXEC)
	@echo $(YELLOW) " - Compiling FINISHED" $(RESET)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	@$(RM) $(OBJ_DIR)
	@echo $(RED) " - Cleaned!" $(RESET)

fclean : clean
	@$(RM) $(EXEC)
	@$(MAKE) $(LIBFT_DIR) fclean
	@echo $(RED) " - Full Cleaned!" $(RESET)

re: fclean all

.PHONY: all clean fclean re
