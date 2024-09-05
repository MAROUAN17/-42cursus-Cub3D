#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include "MLX42/include/MLX42/MLX42.h"

#define HEIGHT 1000
#define WIDTH 1800
#define FOV_ANGLE 60
#define TILE_PX 60

typedef struct s_point {
	double x;
	double y;
}			t_point;

typedef struct s_ray {
	double		x;
	double		y;
	double		angle;
	double		h_xintersept;
	double		h_yintersept;
	double		v_xintersept;
	double		v_yintersept;
	int			p_isFacingDown;
	int			p_isFacingUp;
	int			p_isFacingRight;
	int			p_isFacingLeft;
}					t_ray;

typedef struct player_struct {
	mlx_t		*mlx;
	char		**map;
	int	map_height;
	int	map_width;
	mlx_image_t *map_img;
	mlx_image_t *white_img;
	mlx_image_t *player_img;
	mlx_image_t *view_img;
	char		key;
	double		p_fov_angle;
	double		player_x;
	double		player_y;
	double		turnDirection;
	double		playerAngle;
	double		moveSpeed;
	double		rotationSpeed;
	t_ray		*rays;
}					t_player;

void	*ft_memset(void *b, int c, size_t len);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
double	degrees2rad(double degrees);
double	find_closest_horizontal_yintersec(t_player *player);
double	find_closest_horizontal_xintersec(t_player *player, double yintersept, double ray_angle);
double	find_closest_vertical_yintersec(t_player *player, double xintersept, double ray_angle);
double	find_closest_vertical_xintersec(t_player *player);
double	calculate_xstep(double ray_angle);
double	calculate_ystep(double ray_angle);
double	calculate_smallest_distance(t_player *player, t_ray *ray, t_point *wall1, t_point *wall2);
double	cast_rays(t_player *player);
void	move_player(mlx_key_data_t keydata, void *player);
void	render_empty(void *player);
void	render_draw_line(void *v_player); 
void	render_2dmap(t_player *player, char **map);
void	render(void *v_player); 
void	draw_rectangle(mlx_image_t *img, int x, int y, int color, int p);
t_point	calculating_horizontal_intersections(t_player *player, t_ray *ray);
t_point	calculating_vertical_intersections(t_player *player, t_ray *ray);
t_point	finding_wall_horizontal(t_player *player, t_ray *ray, double xstep, double ystep);
t_point	finding_wall_vertical(t_player *player, t_ray *ray, double xstep, double ystep);