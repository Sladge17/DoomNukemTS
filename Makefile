NAME = DoomNukemTS
FLAG = -Wall -Wextra -Werror -g
# FLAG = -g

HEADER_DIR = includes/
HEADER = -I $(HEADER_DIR)

SRC_DIR = src/
SRC_LIST =	main.c\
			init.c\
			vlist.c\
			llist.c\
			bsp_tree.c\
			draw_map.c\
			draw_line.c\
			utils.c
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

SDL = -F Frameworks\
	-framework SDL2\
	-framework SDL2_image\
	-framework SDL2_mixer\
	-rpath Frameworks

SDL_HEADER = -F Frameworks\
			-I Frameworks/SDL2.framework/Headers\
			-I Frameworks/SDL2_image.framework/Headers\
			-I Frameworks/SDL2_mixer.framework/Headers

all: $(NAME)

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(HEADER) $(OBJ) $(SDL)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER_DIR)*.h
	@mkdir -p $(OBJ_DIR)
	@gcc -c $(HEADER) $(SDL_HEADER) $< -o $@ $(FLAG)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re