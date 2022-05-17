#include "libft.h"

int	ft_strarray_size(char **strarr)
{
	int	size;

	size = 0;
	while (strarr[size] != 0)
		size++;
	return (size);
}