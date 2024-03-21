# Compiler
NAME			= libft.a
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
AR				= ar
ARFLAGS			= -rcs
MKDIR			= mkdir -p
RM				= rm -rf

# Sources
INCLUDE_FILES	= libft.h
SRC_FILES		= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	   			  ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
				  ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
				  ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
				  ft_lstadd_front.c ft_itoa.c ft_strdup.c ft_substr.c ft_strjoin.c \
				  ft_strtrim.c ft_split.c ft_calloc.c ft_strmapi.c ft_striteri.c \
				  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				  ft_lstnew.c ft_atoi.c ft_lstsize.c ft_lstlast.c ft_lstmap.c \
				  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \

# Objects
OBJS_DIR		= objs/
OBJ_FILES		= $(SRC_FILES:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))

all : $(OBJS_DIR) $(NAME)

$(OBJS_DIR) :
	@$(MKDIR) $(OBJS_DIR)

$(NAME) : $(OBJS) Makefile
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(OBJS_DIR)%.o : %.c $(INCLUDE_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS_DIR)

fclean : clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 
