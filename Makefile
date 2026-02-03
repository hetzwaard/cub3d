# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: selcyilm <selcyilm@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2025/02/21 23:23:50 by selcyilm      #+#    #+#                  #
#    Updated: 2026/02/03 14:56:24 by mahkilic      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus
CFLAGS = -Wall -Werror -Wextra -flto -O3 -ffast-math -Wunreachable-code -Ofast
CC = cc
LIBMLX	= ./include/MLX42
MLX42	= ./include/MLX42/build/libmlx42.a
LIBFT	= ./include/libft/libft.a
HEADERS	= -I ./include/libft/ -I ./include -I $(LIBMLX)/include/ -I ./include/MLX42/include/MLX42/
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRC_DIR = src
OBJ_DIR = obj
OBJ_DIR_BONUS = obj_bonus

COMMON_SRCS = ./parser/fn_parser.c ./parser/fn_parser_dir_util.c \
./parser/fn_parser_identifiers.c  ./parser/fn_parser_start.c \
./parser/fn_parser_color_util.c  ./parser/fn_parser_file.c ./parser/fn_parser_map.c \
main.c ./parser/fn_parser_map_prapare.c ./parser/fn_parser_map_util.c \
./parser/fn_parser_map_wall_check.c ./parser/fn_parser_free.c \
./parser/fn_parser_file_utils.c \
./error/fn_error_message.c ./game/fn_game_collision.c \
./game/fn_game_crosshair.c ./game/fn_game_draw.c \
./game/fn_game_floor_draw.c ./game/fn_game_floor_utils.c \
./game/fn_game_init.c ./game/fn_game_input.c \
./game/fn_game_jump.c ./game/fn_game_loop.c ./game/fn_game_move.c \
./game/fn_game_post.c ./game/fn_game_ray.c \
./game/fn_game_render.c ./game/fn_game_rotate.c ./game/fn_game_shade.c \
./game/fn_game.c ./game/fn_game_time.c ./game/fn_game_free.c \
./game/fn_game_texture.c ./game/fn_game_settings.c \
./game/fn_game_wall_draw.c ./game/fn_game_wall_loop.c

MANDATORY_SRCS = $(COMMON_SRCS) ./game/fn_game_extras.c ./game/fn_build_mode.c

BONUS_SRCS = ./bonus/fn_build_mode.c ./bonus/fn_game_bonus_doors.c \
./bonus/fn_game_bonus_init.c ./bonus/fn_game_bonus_keys.c \
./bonus/fn_game_bonus_minimap_render.c \
./bonus/fn_game_bonus_minimap_utils.c ./bonus/fn_game_bonus_minimap_fov.c \
./bonus/fn_game_bonus_render.c ./bonus/fn_game_bonus_sprite_data.c \
./bonus/fn_game_bonus_sprite_draw.c ./bonus/fn_game_bonus_sprite_render.c \
./bonus/fn_game_bonus_sprite_stripe.c

OBJS = $(MANDATORY_SRCS:%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS = $(COMMON_SRCS:%.c=$(OBJ_DIR_BONUS)/%.o) \
$(BONUS_SRCS:%.c=$(OBJ_DIR_BONUS)/%.o)

all: $(MLX42) libft $(NAME)

$(MLX42):
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@$(MAKE) -s -C ./include/libft all

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(OBJ_DIR_BONUS)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(LIBS) $(HEADERS) -o $(NAME)

$(NAME_BONUS): $(OBJ_DIR_BONUS) $(OBJS_BONUS)
	$(CC) $(OBJS_BONUS) $(CFLAGS) $(LIBFT) $(LIBS) $(HEADERS) -o $(NAME_BONUS)

bonus: $(MLX42) libft $(NAME_BONUS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR_BONUS):
	@mkdir -p $(OBJ_DIR_BONUS)

clean:
	@$(MAKE) -s -C include/libft/ clean
	@rm -rf $(LIBMLX)/build
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)

fclean: clean
	@$(MAKE) -s -C include/libft/ fclean
	@rm -rf $(NAME) $(NAME_BONUS)

norm:
	norminette src include include/libft

re: fclean all

.PHONY: all, clean, fclean, re, bonus, libft
