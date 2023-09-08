#include "../../includes/cub3d_header.h"

char	*get_flat(int xpm)
{
	char	*xpm_flat;
	char	*buff;
	int		zero;

	xpm_flat = (char *)malloc(1 * sizeof(char));
	buff = (char *)malloc(sizeof(char) * 2);
	if (!(buff || xpm))
		return (NULL);
	xpm_flat[0] = '\0';
	zero = 1;
	while (zero != 0)
	{
		zero = read(xpm, buff, zero);
		buff[zero] = '\0';
		xpm_flat = ft_strjoin(xpm_flat, buff);
	}
	free(buff);
	return (xpm_flat);
}

char	**ft_image_to_char(int xpm)
{
	char	**xpm_plan;
	char	*xpm_flat;

	if (xpm < 0)
		exit(0);
	xpm_flat = get_flat(xpm);
	xpm_plan = ft_split(xpm_flat, '\n');
	free(xpm_flat);
	return (xpm_plan);
}
