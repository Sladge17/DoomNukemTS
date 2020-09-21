NAME = DoomNukemTS
FLAG = -Wall -Wextra -Werror

HEADER_DIR = includes/
HEADER = -I $(HEADER_DIR)

SRC_DIR = src/
SRC_LIST = 
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

all: $(NAME)

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(HEADER) $(OBJ)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER_DIR)*.h
	@mkdir -p $(OBJ_DIR)
	@gcc -c $(HEADER) $< -o $@ $(FLAG)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re