NAME	=	philo
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf
OBJ_DIR	=	./obj
SRC_DIR	=	./src
INC		=	./include

LIB_DIR	=	libft

LIB_FILES	=	ft_atosize.c
LIB			=	$(addprefix $(LIB_DIR)/, $(LIB_FILES))

SRC_FILES	=	philo.c exec_philo.c $(LIB)
SRCS		=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJS	=	$(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SRCS:.c=.o))


.PHONY: all debug
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I $(INC) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/$(*D)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

#Debug
debug: CFLAGS += -g -fsanitize=address
debug: re

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

git:
	git add .
	git commit -m "small bug fix"
	git push