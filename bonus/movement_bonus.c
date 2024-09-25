/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:45:51 by maglagal          #+#    #+#             */
/*   Updated: 2024/09/25 17:47:50 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d_header_b.h"

int	check_corner(t_player *player, float new_x, float new_y)
{
	int	check_y;
	int	check_x;
	(void)new_x;

	check_y = (player->player_y + new_y) / TILE_PX;
	check_x = (player->player_x) / TILE_PX;
	if (player->map[check_y][check_x] != '1')
		return (1);
	return (0);
}

float normalize_rayAngle(float ray_angle)
{
	ray_angle = remainder(ray_angle, 2 * M_PI);
	if (ray_angle < 0)
		ray_angle = (2 * M_PI) + ray_angle;
	if (fabs(tan(ray_angle)) < 0.000001)
		ray_angle += 0.0001;
	return (ray_angle);
}

void	check_change_position(t_player *player, float angle)
{
	float new_x = cos(angle) * player->moveSpeed;
	float new_y = sin(angle) * player->moveSpeed;
	int	check_y;
	int	check_x;
	if (!check_corner(player, new_x, new_y))
	{
		new_x = 0;
		new_y = 0;
	}
	check_y = (player->player_y + new_y) / TILE_PX;
	check_x = (player->player_x + new_x) / TILE_PX;
	if (player->map[check_y][check_x] != '1')

	if (player->map[(int)((player->player_y + new_y) / TILE_PX)][(int)((player->player_x + new_x) / TILE_PX)] != '1')
	{
		player->player_x += new_x;
		player->player_y += new_y;
	}
}

void	move_player(mlx_key_data_t keydata, void *v_player)
{
	t_player	*player;

	player = (t_player *)v_player;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->w_key = 1;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->s_key = 1;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->a_key = 1;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->d_key = 1;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->turnLeft = 1;
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->turnRight = 1;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		player->w_key = 0;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		player->s_key = 0;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		player->a_key = 0;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		player->d_key = 0;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_RELEASE))
		player->turnLeft = 0;
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_RELEASE))
		player->turnRight = 0;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(player->mlx);
}

void rotate_player(t_player *player, float rotationAngle)
{
	player->playerAngle += rotationAngle;
	player->playerAngle = normalize_rayAngle(player->playerAngle);
}

void mouse_rotation(t_player *player)
{
	static int old_x = (WIDTH / 2);
    int x;
	int y;
    int deltaX;

    x = 0;
    y = 0;
	mlx_get_mouse_pos(player->mlx, &x, &y);
	deltaX = x - old_x;
	if (deltaX != 0 && x > 0 && x < WIDTH)
	{
		if (deltaX > 0)
			rotate_player(player, player->rotationSpeed * 1);
		else if (deltaX < 0)
			rotate_player(player, player->rotationSpeed * -1);
	}
	old_x = x;
}

