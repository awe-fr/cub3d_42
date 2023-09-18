#include "../../includes/cub3d_header.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	c;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	c = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[c] != '\0')
		str[i++] = s2[c++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (str);
}

char	*ft_strchr(char *str, int c)
{
	int		i;
	char	ch;

	i = 0;
	ch = c;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ch)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int atoi_hexa(char *str)
{
	int result;
	int i;

	result = 0;
	i = 0;
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'F'))
	{
		if (str[i] >= 'A' && str[i] <= 'F')
			result += ((str[i] - 55) * pow(16, ft_strlen(str) - i - 1));
		else
			result += ((str[i] - 48) * pow(16, ft_strlen(str) - i - 1));
		i++;
	}
	return (result);
}

int	get_color(t_xpm *xpm, char **xpm_char, int x, int y)
{
	char val;
	int i;
	int z;
	int result;
	char *color;
	int k;

	i = 0;
	z = 4;
	k = 0;
	val = xpm_char[y][x];
	color = malloc(sizeof(char) * 7);
	while ((xpm->colors[i][0] != val) && (xpm->colors[i] != NULL))
		i++;
	while (xpm->colors[i][z] != 0)
	{
		color[k++] = xpm->colors[i][z++];
	}
	color[k] = '\0';
	result = atoi_hexa(color);
	free(color);
	return result;
}