#include "cub3d.h"
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

#define mapWidth 5
#define mapHeight 9
#define screenWidth 640
#define screenHeight 480

int	ft_close(t_game *g)
{
	mlx_destroy_window(g->mlx, g->win);
	exit(0);
}

void	ft_write_hex_c(size_t a, int w, t_game *game)
{
	//unsigned int	b;
	char			*hex;
	char			*hex2;
	char			*start;

	hex = "0123456789ABCDEF";
	hex2 = ft_strdup(hex);
	hex2[0] = hex[a];
	hex2[1] = '\0';
	if (ft_strlen(hex2) < 2 && w == 1)
		hex2 = ft_strjoin("0", hex2);
	start = NULL;
		printf("hex2 = %s", hex2);
	if (game->c_col.init == 0)
	{
		game->c_col.init++;
		hex2[0] = hex[a];
		hex2[1] = '\0';
		game->c_col.col = ft_strjoin("0x", hex2);
	}
	else 
	{
		printf("\nc_col tiene %s y tiene que añadirle %s\n", game->c_col.col, hex2);
		game->c_col.col = ft_strjoin(game->c_col.col, hex2);
	}
}

void	ft_hex_c(size_t nb, int a, t_game *game)
{
	//printf("numero = %zu\n", nb);
	if (nb >= 0 && nb < 16)
		ft_write_hex_c(nb % 16, a, game);
	if (nb >= 16)
	{
		ft_hex_c(nb / 16, a, game);
		ft_write_hex_c(nb % 16, a, game);
	}
}

void	ft_color_hex_c(t_game *game)
{
	game->c_col.init = 0;
	printf("test numero r= %d\n", game->c_col.r);
	if (game->c_col.r < 16)
		ft_hex_c(game->c_col.r, 1, game);
	else 
		ft_hex_c(game->c_col.r, 0, game);
	printf("**********\n");
	if (game->f_col.g < 16)
		ft_hex_c(game->c_col.g, 1, game);
	else 
		ft_hex_c(game->c_col.g, 0, game);
	if (game->c_col.b < 16)
		ft_hex_c(game->c_col.b, 1, game);
	else 
		ft_hex_c(game->c_col.b, 0, game);
	printf("\ncol = %s\n", game->c_col.col);

}

void	ft_write_hex_f(size_t a, int w, t_game *game)
{
	//unsigned int	b;
	char			*hex;
	char			*hex2;
	char			*start;

	hex = "0123456789ABCDEF";
	hex2 = ft_strdup(hex);
	hex2[0] = hex[a];
	hex2[1] = '\0';

	if (ft_strlen(hex2) < 2 && w == 1)
		hex2 = ft_strjoin("0", hex2);
	start = NULL;
		printf("*hex2 = %s*\n", hex2);
	if (game->f_col.init == 0)
	{
		game->f_col.init++;
		//hex2[0] = hex[a];
		//hex2[1] = '\0';
		game->f_col.col = ft_strjoin("0x", hex2);
	}
	else 
	{
		printf("\nf_col tiene %s y tiene que añadirle %s\n", game->f_col.col, hex2);
		game->f_col.col = ft_strjoin(game->f_col.col, hex2);
	}
}

void	ft_hex_f(size_t nb, int a, t_game *game)
{
	//printf("numero = %zu\n", nb);
	if (nb >= 0 && nb < 16)
		ft_write_hex_f(nb % 16, a, game);
	if (nb >= 16)
	{
		ft_hex_f(nb / 16, a, game);
		ft_write_hex_f(nb % 16, a, game);
	}
}

void	ft_color_hex(t_game *game) //! quitar los leaks de los strduo y strjoin
{
	game->f_col.init = 0;
	printf("test numero r= %d\n", game->f_col.r);
	if (game->f_col.r < 16)
		ft_hex_f(game->f_col.r, 1, game);
	else 
		ft_hex_f(game->f_col.r, 0, game);
	if (game->f_col.g < 16)
		ft_hex_f(game->f_col.g, 1, game); 
	else 
		ft_hex_f(game->f_col.g, 0, game);
	if (game->f_col.b < 16)
		ft_hex_f(game->f_col.b, 1, game);
	else 
		ft_hex_f(game->f_col.b, 0, game);
	printf("\ncol = %s\n", game->f_col.col);

}

int	ft_strlen_space(char *str)
{
	int	i;

	i = 0;
	while(str[i] && str[i] != ' ')
		i++;
	return (i);
}

void	t_map_trim(char **str)
{
	int		i;
	char	*ptr;

	i = 0;
	while (str[i])
	{
		ptr = ft_strtrim(str[i], " ");
		free (str[i]);
		str[i] = ptr;
		i++;
	}
}

int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_matrix_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("color[%d] = %s\n", i, str[i]);
		i++;
	}
	return (i);
}


char	*ft_check_format(char *str, char *to_find)
{
	int	a;
	int	b;

	b = 0;
	a = 0;
	if (ft_strlen(to_find) == 0)
		return (str);
	while (str[a])
	{
		if (str[a + b] == to_find[b])
		{
			while (to_find[b])
			{
				b++;
				if (str[a + b] != to_find[b])
					break ;
			}
			if (b == (int)ft_strlen(to_find))
				return (str + a);
			b = 0;
		}
		a++;
	}
	printf("Error\nInvalid file, use *.cub\n");
	return (0);
}

char	*ft_strstr(char *str, char *to_find)
{
	int i;
	int j;

	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (&str[i]);
			++j;
		}
		++i;
	}
	return (0);
}

char	*ft_find_str_matrix(char *str, char **mat)
{
	int	i;

	i = 0;
	while(mat[i])
	{
		if (ft_strstr(mat[i], str))
			return(ft_strstr(mat[i], str));
		i++;
	}
	return (NULL);
}

char	*ft_find_str_matrix2(char *str, char **mat)
{
	int	i;
	int	j;
	int	lenstr;

	i = 0;
	j = 0;
	lenstr = (int)ft_strlen(str);
	while(mat[i])
	{
		if (mat[i][j] == str[j])
		{
			printf("char %c, ", mat[i][j]);
			j++;
			if (j == lenstr)
				return(mat[i] + j);
		}
		else
			j = 0;
		if (!j)
		i++;
	}
	return (NULL);
}

void	ft_count_lines(t_game *g, int i, int fd)
{
	char	*ptr;

	ptr = "AA";
	while (1)
	{	
		if (ptr == NULL)
			break ;
		ptr = get_next_line(fd);
		free(ptr);
		i++;
	}
	i--;
	g->mh = i;
}
void	ft_fill_map(t_game *g, int i, int fd)
{
	char	*ptr;

	ptr = "AA";
	while (1)
	{
		ptr = get_next_line(fd);
		if (ptr == NULL || i == g->mh)
			break ;
		g->mw = (int)ft_strlen(ptr);
		g->file[i] = ptr;
		i++;
	}
}

int	ft_read_file(t_game *g, char *name)
{
	int		fd;
	int		i;

	i = 0;
	g->no_check = 0;
	g->so_check = 0;
	g->ea_check = 0;
	g->we_check = 0;
	g->c_check = 0;
	g->f_check = 0;
	if (!ft_check_format(name, ".cub"))
		return (0);
	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nWrong fd.\n");
		return (0);
	}
	else
	{
		ft_count_lines(g, i, fd);
		close (fd);
		fd = open(name, O_RDONLY);
		g->file = (char **)malloc(sizeof(char *) * (g->mh + 1));
		if (!g->file)
			return (0);
		g->file[g->mh] = NULL;
		ft_fill_map(g, i, fd);
	}
	close (fd);
	return (1);
}

void	ft_remove_end_line(t_game *game)
{
	int		i;
	int		j;
	size_t	size;
	char	*ptr;

	i = 0;
	j = 0;
	while (i < game->mh)
	{
		size = ft_strlen(game->file[i]);
		if (size > 1)
		{
			ptr = malloc(size);
			ft_strncpy(ptr, game->file[i], size - 1);
			ptr[size - 1] = '\0';
			free(game->file[i]);
			game->file[i] = ptr;
		}
		i++;
	}
	
}

char	**ft_get_map(t_game *game)
{
	char	**map;
	int		i;
	int		j;
	int		size;
	int		check;

	i = 0;
	size = 0;
	check = 0;
	printf("Holaaaa\n");
	while (game->file_save[i] && game->file_save[i][0] && game->file_save[i][0] != '1')
	{
		printf("*%s*\n", game->file_save[i]);
		i++;
	}
	j = i;
	while (game->file_save[i])
	{
		if (ft_strstr(game->file_save[i], "1"))
			check = 1;
		size++;
		i++;
	}
	if (!check)
	{
		printf("Error, invalid map\n");
		return(NULL);
	}
	printf("Dddddd\n");
	map = (char **)malloc(sizeof(char *) * (size + 1));
	i = j;
	size = 0;
	while (game->file[i])
	{
		printf("---%s---\n", game->file[i]);
		map[size] = ft_strdup(game->file[i]);
		size++;
		i++;
	}
	map[size] = NULL;
	return (map);
}

void	ft_file_copy(t_game	*game)
{
	int	i;

	i = 0;
	game->file_save = (char **)malloc(sizeof(char *) * (game->mh + 1));
	if (!game->file)
		return ;
	while(game->file[i])
	{
		game->file_save[i] = ft_strdup(game->file[i]);
		i++;
	}
	game->file_save[i] = NULL;
	//game->file[game->mh] = NULL;
	
}

int	ft_get_map2(t_game *game) //comprobar que no hay mas lineas despues del mapa
{
	int	i;

	i = 0;
	ft_file_copy(game);
	t_map_trim(game->file_save);
	printf("\n*******\n");
	while (game->file_save[i] && game->file_save[i][0] && game->file_save[i][0] != '1' )
	{
		i++;
	}
	printf("\nllega aqui\n");
	while (game->file_save[i])
	{
	printf("C\n");
		if (ft_strchr(game->file_save[i], '\n'))
		{
			printf("Error, invalid map\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_get_map3(t_game *game)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (game->file_save[i][0] && game->file_save[i][0] != '1')
	{
		printf("BBB\n");
		if (ft_strstr(game->file_save[i], "NO "))
		{
			game->no_check = 1;
			n++;
		}
		if (ft_strstr(game->file_save[i], "EA "))
			game->ea_check = 1;
		if (ft_strstr(game->file_save[i], "WE "))
			game->we_check = 1;
		if (ft_strstr(game->file_save[i], "SO "))
			game->so_check = 1;
		if (ft_strstr(game->file_save[i], "F "))
			game->f_check = 1;
		if (ft_strstr(game->file_save[i], "C "))
			game->c_check = 1;
		i++;
	}
	printf("i = %d\n", n);
	if (game->so_check + game->ea_check + game->we_check + game->no_check + game->c_check + game->f_check != 6)
	{
		printf("Error, invalid map\n");
		return (1);
	}
	return (0);
}

int	ft_check_tex(t_game *game)
{
	//printf("%x\n", -3);
	if (game->no_tex)
		game->no.img = mlx_xpm_file_to_image(game->mlx, game->no_tex, &game->no.w, &game->no.h);
	if (!game->no.img || !game->no_tex)
		return (-1);
	if (game->so_tex)
		game->so.img = mlx_xpm_file_to_image(game->mlx, game->so_tex, &game->so.w, &game->so.h);
	if (!game->so.img || !game->so_tex)
		return (-1);
	if (game->we_tex)
		game->we.img = mlx_xpm_file_to_image(game->mlx, game->we_tex, &game->we.w, &game->we.h);
	if (!game->we.img || !game->we_tex)
		return (-1);
	if (game->ea_tex)
		game->ea.img = mlx_xpm_file_to_image(game->mlx, game->ea_tex, &game->ea.w, &game->ea.h);
	if (!game->ea.img || !game->ea_tex)
		return (-1);
	return (0);
}

int	ft_check_color_com(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',' && (int)ft_strlen(str) > i)
			if (str[i + 1] < '0' || str[i + 1] > '9')
			return (1);
		i++;
	}
	return (0);
}

int ft_get_color_f(t_game *game)
{
	char	**col_mat;

	if (ft_check_color_com(game->col_f))
		return (-1);
	col_mat = ft_split(game->col_f, ',');
	if (!col_mat || ft_matrix_len(col_mat) != 3)
		return (-1);
	printf("rumero col_mat[0] = %s\n", col_mat[0]);
	if (!ft_str_isdigit(col_mat[0]) || !ft_str_isdigit(col_mat[1]) || !ft_str_isdigit(col_mat[2]))
		return (-1);
	game->f_col.r = ft_atoi(col_mat[0]);
	game->f_col.g = ft_atoi(col_mat[1]);
	game->f_col.b = ft_atoi(col_mat[2]);
	free_matrix(col_mat);
	if (game->f_col.r > 255 || game->f_col.r < 0)
		return (-1);
	if (game->f_col.g > 255 || game->f_col.g < 0)
		return (-1);
	if (game->f_col.b > 255 || game->f_col.b < 0)
		return (-1);
	//printf("f_r = %d", game->f_col.r);
	return (0);
}

int ft_get_color_c(t_game *game)
{
	char	**col_mat;	

	if (ft_check_color_com(game->col_c))
		return (-1);
	col_mat = ft_split(game->col_c , ',');
	if (!col_mat || ft_matrix_len(col_mat) != 3)
		return (-1);
	if (!ft_str_isdigit(col_mat[0]) || !ft_str_isdigit(col_mat[1]) || !ft_str_isdigit(col_mat[2]))
		return (-1);
	game->c_col.r = ft_atoi(col_mat[0]);
	game->c_col.g = ft_atoi(col_mat[1]);
	game->c_col.b = ft_atoi(col_mat[2]);
	free_matrix(col_mat);
	if (!col_mat)
		return (-1);
	if (game->c_col.r > 255 || game->c_col.r < 0)
		return (-1);
	if (game->c_col.g > 255 || game->c_col.g < 0)
		return (-1);
	if (game->c_col.b > 255 || game->c_col.b < 0)
		return (-1);
	return (0);
}



int	ft_file_split(t_game *game)
{
	int	i;

	i = 0;
	game->no_tex = ft_find_str_matrix2("NO ", game->file);
	game->so_tex = ft_find_str_matrix2("SO ", game->file);
	game->we_tex = ft_find_str_matrix2("WE ", game->file);
	game->ea_tex = ft_find_str_matrix2("EA ", game->file);
	if (ft_check_tex(game) == -1)
	{
		printf("\nError with textures\n");
		return (-1);
	}
	game->col_f = ft_find_str_matrix2("F ", game->file);

	game->col_c = ft_find_str_matrix2("C ", game->file);
	if (!game->col_f || !game->col_c ||(ft_get_color_c(game) == -1) || (ft_get_color_f(game) == -1))
	{
		printf("\nError with colors\n");
		return (-1);
	}
	ft_color_hex(game);
	ft_color_hex_c(game);
	printf("*llega aqui x 2*\n");
	if (ft_get_map2(game))
		return (-1);
	game->map = ft_get_map(game);//
	if (!game->map)
		return (-1);
	if (ft_get_map3(game))
		return (-1);
	game->mv = 0;
	return (0);
}

// int	worldMap[mapWidth][mapHeight]=
// {
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

int	worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1}
};

int	key_event(int key_code, t_data *m)
{
	if (key_code == 53)
		exit(0);
	if (key_code == 124)
	{
		printf("->\n");
		double oldDirX = m->dirX;
		m->dirX = m->dirX * cos(-m->rotSpeed) - m->dirY * sin(-m->rotSpeed);
		m->dirY = oldDirX * sin(-m->rotSpeed) + m->dirY * cos(-m->rotSpeed);
	    double oldPlaneX = m->planeX;
      	m->planeX = m->planeX * cos(-m->rotSpeed) - m->planeY * sin(-m->rotSpeed);
      	m->planeY = oldPlaneX * sin(-m->rotSpeed) + m->planeY * cos(-m->rotSpeed);
		printf("dirX: %f\n", m->dirX);
		printf("dirY: %f\n", m->dirY);
	}
	else if (key_code == 123)
	{
		printf("<-\n");
		double oldDirX = m->dirX;
		m->dirX = m->dirX * cos(m->rotSpeed) - m->dirY * sin(m->rotSpeed);
		m->dirY = oldDirX * sin(m->rotSpeed) + m->dirY * cos(m->rotSpeed);
	    double oldPlaneX = m->planeX;
      	m->planeX = m->planeX * cos(m->rotSpeed) - m->planeY * sin(m->rotSpeed);
      	m->planeY = oldPlaneX * sin(m->rotSpeed) + m->planeY * cos(m->rotSpeed);
		printf("dirX: %f\n", m->dirX);
		printf("dirY: %f\n", m->dirY);
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->lineLength + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	verLine(t_data *m, int x)
{
	while (m->drawStart < m->drawEnd)
	{
		my_mlx_pixel_put(m, x, m->drawStart, m->color);
		m->drawStart += 1;
	}
}

void	init_variables(t_data *m)
{
	m->posX = 2;
	m->posY = 2;
	m->dirX = 1;
	m->dirY = 1;
	m->planeX = 0;
	m->planeY = 0.66;
	m->time = 0;
	m->oldTime = 0;
	m->rotSpeed = 25;
}

int	main(int argc, char **argv)
{
	int x;
	//t_data	m;
	t_game game;
    int     i;


    i = 0;
    if (argc < 2)
		return (0);
	if (ft_read_file(&game, argv[1]) == 0)
        return (0);
    while (i < game.mh)
        i++;
	x = 0;
	game.mlx = mlx_init();
	ft_remove_end_line(&game);
	if (ft_file_split(&game) == -1)
		return (-1);
	if (ft_map_check(&game) == -1)
		return (-1);
	init_variables(&game.m);
	game.win = mlx_new_window(game.mlx, screenWidth, screenHeight, "Cub3d");
	game.m.img = mlx_new_image(game.mlx, screenWidth, screenHeight);
	game.m.addr = mlx_get_data_addr(game.m.img, &game.m.bits_per_pixel, &game.m.lineLength, &game.m.endian);
	while (x < screenWidth)
	{
		game.m.cameraX = 2 * x / (double)screenWidth - 1;
		game.m.rayDirX = game.m.dirX + game.m.planeX * game.m.cameraX;
		game.m.rayDirY = game.m.dirY + game.m.planeY * game.m.cameraX;
		game.m.mapX = (int)game.m.posX;
		game.m.mapY = (int)game.m.posY;
		if (game.m.rayDirX == 0)
			game.m.deltaDistX = exp(30);
		else
			game.m.deltaDistX = fabs(1.0 / game.m.rayDirX);
		if (game.m.rayDirY == 0)
			game.m.deltaDistY = exp(30);
		else
			game.m.deltaDistY = fabs(1.0 / game.m.rayDirY);
		game.m.hit = 0;
		if (game.m.rayDirX < 0)
		{
			game.m.stepX = -1;
			game.m.sideDistX = (game.m.posX - game.m.mapX) * game.m.deltaDistX;
		}
		else
		{
			game.m.stepX = 1;
			game.m.sideDistX = (game.m.mapX + 1.0 - game.m.posX) * game.m.deltaDistX;
		}
		if (game.m.rayDirY < 0)
		{
			game.m.stepY = -1;
			game.m.sideDistY = (game.m.posY - game.m.mapY) * game.m.deltaDistY;
		}
		else
		{
			game.m.stepY = 1;
			game.m.sideDistY = (game.m.mapY + 1.0 - game.m.posY) * game.m.deltaDistY;
		}
		while (game.m.hit == 0)
		{
			if (game.m.sideDistX < game.m.sideDistY)
			{
				game.m.sideDistX += game.m.deltaDistX;
				game.m.mapX += game.m.stepX;
				game.m.side = 0;
			}
			else
			{
				game.m.sideDistY += game.m.deltaDistY;
				game.m.mapY += game.m.stepY;
				game.m.side = 1;
			}
			if (worldMap[game.m.mapY][game.m.mapX] > 0)
				game.m.hit = 1;
		}
		if (game.m.side == 0)
			game.m.perpWallDist = (game.m.sideDistX - game.m.deltaDistX);
		else
			game.m.perpWallDist = (game.m.sideDistY - game.m.deltaDistY);
		game.m.lineHeight = (int)(screenHeight / game.m.perpWallDist);
		game.m.drawStart = -game.m.lineHeight / 2 + screenHeight / 2;
		if(game.m.drawStart < 0)
			game.m.drawStart = 0;
		game.m.drawEnd = game.m.lineHeight / 2 + screenHeight / 2;
		if(game.m.drawEnd >= screenHeight)
			game.m.drawEnd = screenHeight - 1;
		game.m.color = 0x0000FF;
		if (game.m.side == 1)
			game.m.color = game.m.color / 2;
		verLine(&game.m, x);
		x ++;
	}
	mlx_put_image_to_window(game.mlx, game.win, game.m.img, 0, 0);
	mlx_hook(game.win, 2, 0, &key_event, &game);
	mlx_hook(game.win, 17, 0, ft_close, &game);
    mlx_loop(game.mlx);
}