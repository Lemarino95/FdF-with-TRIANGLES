/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_readmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:29:27 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/17 12:08:41 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			words++;
		while (str[i] && str[i] != c)
		{
			i++;
		}
	}
	return (words);
}

static char	**freesplit(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

// Converts each point of the map file in an int and returns it as a matrix.
int	**cartography(char *map_file)
{
	t_read	mapping;
	int		i;
	int		j;
	int		**map;

	i = 0;
	map = NULL;
	mapping.fd = open(map_file, O_RDONLY);
	while ((mapping.line = get_next_line(mapping.fd)))
	{
		j = 0;
		map = ft_realloc(map, ((i + 1) * sizeof(int *)));
		mapping.line = ft_strtrim(mapping.line, "\n");
		mapping.splitted_line = ft_split(mapping.line, ' ');
		map[i] = malloc(count_words(mapping.line, ' ') * sizeof(int));
		while (mapping.splitted_line[j])
		{
			map[i][j] = ft_atoi(mapping.splitted_line[j]);
			j++;
		}
		i++;
	}
	freesplit(mapping.splitted_line);
	close (mapping.fd);
	return (free(mapping.line), map);
}

int	get_height(char *map_file)
{
	int		height;
	int		fd;
	char	*line;

	height = 0;
	fd = open(map_file, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

int	get_width(char *map_file)
{
	int		width;
	int		fd;
	char	*line;

	width = 0;
	fd = open(map_file, O_RDONLY);
	line = get_next_line(fd);
	width = count_words(line, ' ');
	free(line);
	close(fd);
	return (width);
}

/* int	main(int argc, char *argv[])
{
	int i = 0;
	int j;
	int **map= cartography(argv[1]);
	int	height = get_height(argv[1]);
	int width = get_width(argv[1]);
	printf("%d*%d\n", height, width);
	if (argc > 1)
	{
		while (i < height)
		{
			j = 0;
			while (j < width)
				{
					printf("%2d", map[i][j]);
					j++;
					printf(" ");
				}
			printf("\n");
			i++;
		}
	}
} */