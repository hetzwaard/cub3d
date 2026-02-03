/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 23:23:46 by selcyilm      #+#    #+#                 */
/*   Updated: 2026/02/03 14:58:27 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <libft/include/libft.h>
# include <fcntl.h>
# include <MLX42/include/MLX42/MLX42.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/types.h>

# define PARSER_EXIT_SUCCESS 0
# define PARSER_EXIT_FAILURE 1

# define RGBA_DEF 0

# ifndef WHITESPACES
#  define WHITESPACES " \t\n\r\v\f"
# endif

// GAME SETTINGS //
# define GAME_WIN_W 1920
# define GAME_WIN_H 1080
# define GAME_PI 3.141592653589793
# define GAME_FOV_DEFAULT 85
# define GAME_FOV_MIN 30.0
# define GAME_FOV_MAX 120.0
# define GAME_MOVE_SPEED 3.0
# define GAME_RUN_MULT 1.6
# define GAME_ROT_SPEED 2.4
# define GAME_ACCEL_GROUND 30.0
# define GAME_ACCEL_AIR 5.0
# define GAME_FRICTION 10.0
# define GAME_MOUSE_SENS 0.0015
# define GAME_JUMP_VEL 3.0
# define GAME_JUMP_GRAVITY 10.0
# define GAME_PITCH_MAX 1.0471975511965976
# define GAME_RENDER_CUTOFF_W 1280
# define GAME_RENDER_CUTOFF_H 720
# define GAME_RENDER_SCALE_HI 0.5
# define GAME_RENDER_SCALE_LO 0.5
# define GAME_TARGET_FPS 60.0
# define GAME_BLUR_NUM 3
# define GAME_BLUR_DEN 4
# define GAME_ENABLE_BLUR 0
# define GAME_ENABLE_MINIMAP 0

// HUD and Textures //
# define CROSS_SIZE 5
# define CROSS_COLOR 0xFFFFFFFF
# define HUGE_DIST 1e30
# define COLLISION_RADIUS 0.2
# define DOOR_REACH 1.0
# define GAME_LAVA_Z 0.0
# define GAME_LAVA_COLOR 0xFF0000FF
# define GAME_LAVA_PITCH -0.12
# define GAME_FLOOR_STEP 2
# define KEY_COLOR 0xFF00FFFF
# define SPRITE_COLOR 0xFF66FFFF
# define WALL_N 0xFFFFFF00
# define WALL_S 0xFFFFFF00
# define WALL_E 0xFFFF00FF
# define WALL_W 0xFFFF00FF

// MINIMAP
# define MINI_WALL 0x00FFFFFF
# define MINI_VOID 0x111111FF
# define MINI_EMPTY 0xAAAAAAFF
# define MINI_DOOR 0xAA8800FF
# define MINI_OPEN 0x66AA66FF
# define MINI_SPRITE 0x22DDFFFF
# define MINI_LAVA 0xCC3300FF
# define MINI_KEY 0xFFD700FF
# define MINI_TILE 20
# define MINI_MARGIN 6
# define MINI_RADIUS 4
# define MINI_PLAYER 0xFFFFFFFF
# define MINI_FOV 0xD0D0D0FF
# define MINI_FOV_ALPHA 200
# define MINI_FOV_RAYS 240
# define MINI_FOV_STEP 2
# define MINI_FOV_STAMP 1

typedef enum e_error
{
	ERR_ARGC,
	ERR_F_EXTENTION,
	ERR_FILE_CONTENT,
	ERR_OPEN,
	ERR_ALLOC,
	ERR_INVALID_MAP,
	ERR_INVALID_WALL,
	ERR_INVALID_START,
	ERR_FILE_INEXISTS,
	ERR_TEX_SIZE,
	ERR_LOAD_MAP,
	ERR_UNKNOWN_ELEM,
	ERR_MLX,
	ERR_SIZE
}	t_error;

typedef enum e_parser_state
{
	PARSER_FILE,
	PARSER_IDENTIFIER,
	PARSER_MAP,
	PARSER_ERROR,
	PARSER_DONE
}	t_parser_state;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_config
{
	t_list		*content_of_file;
	char		*filename;
	char		*north_tex_path;
	char		*south_tex_path;
	char		*east_tex_path;
	char		*west_tex_path;
	xpm_t		*north_texture;
	xpm_t		*south_texture;
	xpm_t		*east_texture;
	xpm_t		*west_texture;
	ssize_t		floor_rgb;
	ssize_t		ceil_rgb;
}	t_config;

typedef struct s_map
{
	int		start_index;
	int		height;
	int		width;
	int		wall_count;
	int		player_count;
	int		space_count;
	int		start_pos_count;
	bool	invalid_char;
	bool	has_lava;
	t_list	*map;
	t_point	start_pos;
	char	**map_2d;
	int		*row_len;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
	double	pitch;
	double	vx;
	double	vy;
	double	z;
	double	vz;
}	t_player;

typedef struct s_move
{
	double	fwd;
	double	right;
	double	speed;
	double	wx;
	double	wy;
	double	ws;
}	t_move;

typedef struct s_mouse
{
	double	last_x;
	double	last_y;
	bool	active;
}	t_mouse;

typedef struct s_sprite
{
	double	x;
	double	y;
}	t_sprite;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*wall;
	int32_t		win_w;
	int32_t		win_h;
	int32_t		render_w;
	int32_t		render_h;
	double		render_scale;
	int			map_w;
	int			map_h;
	double		fov_deg;
	double		fov_rad;
	double		move_speed;
	double		rot_speed;
	double		mouse_sens;
	double		last_time;
	double		dt;
	double		frame_time;
	double		accum;
	double		*zbuffer;
	uint32_t	*prev_frame;
	t_sprite	*sprites;
	int			sprite_count;
	bool		minimap_enabled;
	bool		blur_enabled;
	int			keys;
	bool		*door_unlocked;
	xpm_t		*key_xpm;
	t_player	player;
	t_mouse		mouse;
}	t_game;

typedef struct s_app
{
	t_map		*map;
	t_config	*config;
	t_game		*game;
}	t_app;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	dist;
	double	wall_x;
	double	wall_y;
}	t_ray;

typedef struct s_ray_ctx
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_ray_ctx;

typedef struct s_column
{
	uint32_t	*buf;
	int			w;
	int			x;
}	t_column;

typedef struct s_floor_draw
{
	t_app		*app;
	t_column	col;
	int			step;
}	t_floor_draw;

typedef struct s_bounds
{
	int	start;
	int	end;
}	t_bounds;

typedef struct s_wall_bounds
{
	t_bounds	b;
	int			line_h;
	int			center;
}	t_wall_bounds;

typedef struct s_wall_draw
{
	t_column		col;
	t_wall_bounds	wb;
}	t_wall_draw;

typedef struct s_wall_loop
{
	double	raw_start;
	double	step;
	double	tex_pos;
	int		y;
	int		tex_w;
	int		tex_h;
}	t_wall_loop;

typedef struct s_floor
{
	t_app	*app;
	t_ray	*ray;
	int		center;
	double	cam_h;
}	t_floor;

typedef struct s_rect
{
	int	x;
	int	y;
	int	w;
	int	h;
}	t_rect;

typedef struct s_minimap
{
	int	start_x;
	int	start_y;
	int	off_x;
	int	off_y;
}	t_minimap;

typedef struct s_sprite_ctx
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		pitch;
	double	det;
}	t_sprite_ctx;

typedef struct s_sprite_cast
{
	double	ty;
	int		screen_x;
	int		h;
	int		w;
	int		start_x;
	int		end_x;
	int		start_y;
	int		end_y;
}	t_sprite_cast;

typedef struct s_sprite_line
{
	int	x;
	int	y_start;
	int	y_end;
}	t_sprite_line;

typedef struct s_sprite_draw
{
	t_game			*g;
	t_sprite_cast	*cast;
	xpm_t			*xpm;
	uint32_t		color;
	double			shade;
}	t_sprite_draw;

typedef struct s_tex_state
{
	int		y;
	int		y_end;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_tex_state;

typedef struct s_hud
{
	int		count;
	int		x;
	int		step;
	double	shade;
}	t_hud;

typedef struct s_fov_state
{
	double	ca;
	double	sa;
	double	cs;
	double	ss;
	double	half;
	double	step;
}	t_fov_state;

/* PARSER */

typedef t_parser_state	(*t_parser_fn)(t_config *, t_map *);

int				fn_parser(t_config *config, t_map *map, char **av);
t_parser_state	fn_parser_start(t_config *config, t_map *map);
t_parser_state	fn_parser_file(t_config *config, t_map *map);
t_parser_state	fn_parser_identifiers(t_config *config, t_map *map);
t_parser_state	fn_parser_map(t_config *config, t_map *map);
bool			is_valid_file(char *file, char *f_extention);
bool			is_valid_texture_file(t_config *config);
bool			add_color(t_config *config, char **split);
bool			is_color(char *str);
bool			add_direction(t_config *config, char **line);
bool			is_direction(char *str);
bool			fn_map_prapare(t_config *config, t_map *map);
void			fn_map_copy(t_config *config, t_map *map);
char			**fn_map_trimmed(char **map);
char			**fn_map_to_array(t_list *map);
bool			fn_map_wall_check(char **map);
void			fn_parser_free(t_config *config, t_map *map);
void			fn_map_free(t_map *map);
void			fn_config_free(t_config *config);

/* ERROR */
void			fn_error(t_error err_num);

/* GAME */
int				game_start(t_app *app);
int				game_floor_pitch(t_game *g);
int				game_init_textures(t_app *app);
void			game_free(t_app *app);
void			game_set_fov(t_game *game, double fov_deg);
void			game_init_defaults(t_game *game);
void			game_init_map(t_app *app);
void			game_init_player(t_app *app);
void			game_set_render_scale(t_game *game);
void			game_time_update(t_game *game);
bool			game_frame_ready(t_game *game);
void			game_handle_keys(t_app *app);
void			game_handle_mouse(t_app *app);
void			game_apply_movement(t_app *app, double fwd, double right,
					double speed);
void			game_try_move(t_app *app, double nx, double ny);
void			game_jump_start(t_app *app);
void			game_jump_update(t_app *app);
bool			game_is_wall(t_app *app, int mx, int my);
void			game_wrap_angle(double *angle);
void			game_clamp_pitch(double *pitch);
void			game_rotate(t_game *game, double rot);
void			game_ray_init(t_game *g, t_ray *ray, int x, t_ray_ctx *ctx);
void			game_ray_cast(t_app *app, t_ray *ray);
void			game_fill_column(t_column *col, int y_start,
					int y_end, uint32_t color);
void			game_draw_column(t_app *app, int x, t_ray *ray);
void			game_draw_wall(t_wall_draw *w, t_app *app, t_ray *ray);
void			game_draw_wall_loop(t_wall_draw *w, xpm_t *xpm,
					int tex_x, int shade_i);
void			game_draw_crosshair(t_game *g);
void			game_render(t_app *app);
void			game_draw_floor(t_app *app, int x, t_bounds *b, t_ray *ray);
void			game_post_blur(t_game *game);
void			game_loop(void *param);
double			game_plane_dist(t_floor *f, double plane_h, int y);
double			game_shade_factor(t_ray *ray);
uint32_t		game_wall_color(t_app *app, t_ray *ray, double tex_y);
uint32_t		game_shade_color(uint32_t color, double shade);
uint32_t		game_floor_color(t_floor *f, int y);

/* BONUS */
bool			is_bonus_mode(void);
int				bonus_pitch_offset(t_game *g);
int				bonus_count_sprites(t_app *app);
char			bonus_cell_at(t_app *app, int x, int y);
void			game_bonus_init(t_app *app);
void			game_bonus_free(t_app *app);
void			game_bonus_render(t_app *app);
void			game_bonus_keyhook(mlx_key_data_t key, void *param);
void			bonus_store_sprites(t_app *app, t_sprite *sprites);
void			bonus_put_pixel(t_game *g, int x, int y, uint32_t color);
void			bonus_fill_rect_color(t_game *g, t_rect rect, uint32_t color);
void			bonus_fill_rect_clipped(t_game *g, t_rect rect, t_rect box,
					uint32_t color);
void			bonus_draw_sprite_stripe(t_game *g, t_sprite_line *line,
					uint32_t color);
void			bonus_sprite_draw(t_sprite_draw *draw);
void			bonus_render_sprites(t_app *app);
void			bonus_update_keys(t_app *app);
void			bonus_render_hud(t_app *app);
void			bonus_draw_fov(t_app *app);
void			bonus_render_minimap(t_app *app);
uint32_t		bonus_shade_color(uint32_t color, double shade);
uint32_t		bonus_sprite_color(t_game *g, char type);
uint32_t		bonus_minimap_color(char c);

#endif