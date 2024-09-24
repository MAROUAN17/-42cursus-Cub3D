/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:02:04 by oait-laa          #+#    #+#             */
/*   Updated: 2024/09/24 15:20:36 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_header_b.h"

void free_2d_arr(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void render_2dmap(t_player *player, char **map)
{
	int x = 0;
	int y = 0;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_rectangle(player->map_img, x * TILE_PX, y * TILE_PX, 0x000000FF, TILE_PX);
			else if (map[y][x] == 'I')
			{
				player->sprite->x = x * TILE_PX;
				player->sprite->x = y * TILE_PX;
			}
			else
			{
				if (player->player_x == -1 && player->player_y == -1 && (player->map[y][x] == 'N' || player->map[y][x] == 'S' || player->map[y][x] == 'W' || player->map[y][x] == 'E'))
				{	
					player->player_x = x * TILE_PX;
					player->player_y = y * TILE_PX;
				}
				draw_rectangle(player->map_img, x * TILE_PX, y * TILE_PX, 0xFFFFFFFF, TILE_PX);
			}
			x++;
		}
		y++;
	}
}

int main(int ac, char **av)
{
	mlx_t		*mlx;
	int			map_width;
	int			map_height;
	t_player	player;
	t_ray		rays[WIDTH];
	t_sprite	sprite[NUM_SPRITE];
	mlx_texture_t	*textures[5];

	(void)ac;
	player.p_fov_angle = degrees2rad(60);
	map_width = 0;
	map_height = 0;
	player.player_x = -1;
	player.player_y = -1;
	player.map = store_2d_array(&player, av[1], &map_height, &map_width);
	if (!player.map)
		return (1);
	int i = 0;
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false)))
	{
		free_2d_arr(player.map);
		perror(strerror(mlx_errno));
		return (EXIT_FAILURE);
	}

	mlx_image_t *map_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	player.map_img = map_img;
	while (i < WIDTH)
	{
		rays[i].map_img = map_img;
		rays[i].h_xintersept = 0;
		rays[i].h_yintersept = 0;
		rays[i].v_xintersept = 0;
		rays[i].v_yintersept = 0;
		rays[i].p_isFacingDown = 0;
		rays[i].p_isFacingUp = 0;
		rays[i].p_isFacingRight = 0;
		rays[i].p_isFacingLeft = 0;
		rays[i].horizontal_wall = 0;
		rays[i].vertical_wall = 0;
		i++;
	}
	// player.playerAngle = M_PI / 2;
	player.moveSpeed = 6.0;
	player.rotationSpeed = degrees2rad(2.5);
	// get_textures(&player, av[1]);
	player.map_height = map_height;
	player.map_width = map_width;
	player.rays = rays;
	player.mlx = mlx;
	textures[0] = mlx_load_png("./textures/MonedaD1.png");
	textures[1] = mlx_load_png("./textures/MonedaD2.png");
	textures[2] = mlx_load_png("./textures/MonedaD3.png");
	textures[3] = mlx_load_png("./textures/MonedaD4.png");
	textures[4] = mlx_load_png("./textures/MonedaD5.png");
	int j = 0;
	while (j < NUM_SPRITE)
	{
		sprite[j].x = 0;
		sprite[j].y = 0;
	// 	sprite[j].texture = mlx_load_png("./textures/MonedaD1.png");
		sprite[j].visible = 0;
		sprite[j].an_textures = textures; 
		j++;
	}
	player.sprite = sprite;
	// player.north_texture = mlx_load_png("./textures/bochi.png");
	// player.south_texture = mlx_load_png("./textures/bochi2.png");
	// player.west_texture = mlx_load_png("./textures/osaka.png");
	// player.east_texture = mlx_load_png("./textures/osaka2.png");
	// mlx_texture_t *texture = mlx_load_png("./textures/white_image.png");
	// player.white_img = mlx_texture_to_image(player.mlx, texture);
	// mlx_texture_t *texture2 = mlx_load_png("./textures/dot.png");
	// player.player_img = mlx_texture_to_image(player.mlx, texture2);
	// mlx_texture_t *texture3 = mlx_load_png("./textures/red_dot.png");
	// player.view_img = mlx_texture_to_image(player.mlx, texture3);
	// render_2dmap(&player, player.map);
	// cast_rays(&player);
	mlx_image_to_window(mlx, player.map_img, 0, 0);
	mlx_key_hook(mlx, &move_player, &player);
	mlx_loop_hook(mlx, &render, &player);
	// float n_point_y = find_closest_horizontal_yintersec(player.player_y);
	// float n_point_x = find_closest_horizontal_xintersec(player.player_x, player.player_y, n_point_y);
	// int xstep = calculate_xstep();
	// printf("player x -> %d\n", player.player_x);
	// printf("player y -> %d\n", player.player_y);
	// printf("closest horizontal intersection point x -> %f\n", n_point_x);
	// printf("closest horizontal intersection point y -> %f\n", n_point_y);
	// printf("xstep -> %d\n", xstep);
	// mlx_image_t *img = mlx_new_image(mlx, map_width * TILE_PX, map_height * TILE_PX);
	// if (mlx_image_to_window(mlx, img, 0, 0) == -1)
	// {
	// 	mlx_close_window(mlx);
	// 	perror(strerror(mlx_errno));
	// 	return (EXIT_FAILURE);
	// }
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_2d_arr(player.map);
	return (EXIT_SUCCESS);
}
