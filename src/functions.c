#include "../include/kernel.h"

//GENERAL USE FUNCTIONS

void	memset_k(void *s, int c, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		((unsigned char *) s)[i] = c;
		i++;
	}
}

void	memcpy_k(void *dest, const void *src, size_t n)//written with k to aviod built-in warning
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
}

void	bzero_k(void *s, size_t n)
{
	size_t			i;

	i = 0;
	if (s == 0)
		return ;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}


size_t strlen(const char *str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

