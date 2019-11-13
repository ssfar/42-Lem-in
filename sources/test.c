# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"

void			hash_data(void *dest, const size_t size, const char *key)
{
	size_t			i;
	size_t			j;
	unsigned char	*d;

	i = 0;
	j = 0;
	d = bzero(dest, size);
	while (key[i])
	{
		if (j == size)
			j = 0;
		d[j++] ^= key[i++];
	}
}

unsigned int	hash_to_int(const char *key)
{
	unsigned int	v;

	hash_data(&v, sizeof(v), key);
	return (v % 1024);
}


int main(int ac, char **av)
{
	char *str = "0\0q";
	char *str2 = "0";
	printf("str %d\n", hash_to_int(str));
	printf("str2 %d\n", hash_to_int(str2));
}