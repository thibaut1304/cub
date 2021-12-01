
#include "../includes/cub.h"

/*
** PARse each line of the map and save the length of the longest one.
*/

/*
** Check if string sent has only numeric values.
*/

int		is_num(char *num)
{
	int i;

	i = 0;
	while (num[i])
	{
		if (num[i] >= '0' && num[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

/*
** Display error message and lead to the end of the program.
*/

int		is_error(char *str)
{
	printf("Error\n%s\n", str);
	return (0);
}

/*
** Free the content used during the parsing analysis of each line.
*/

int		free_split(char ***split, int ret)
{
	int i;

	i = -1;
	while ((*split)[++i])
	{
		free((*split)[i]);
		(*split)[i] = NULL;
	}
	free(*split);
	*split = NULL;
	return (ret);
}

/*
** Check if map file has the correct extension.
*/

int		cub_ext(char *map_file)
{
	int i;

	i = 0;
	while (map_file[i])
		i++;
	i -= 4;
	if (!ft_strcmp(&map_file[i], ".cub"))
		return (1);
	return (is_error("File extension is not ending with .cub"));
}
