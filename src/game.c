#include "../include/game.h"
#include "../include/kernel.h"

static void	die(int x, int y, int *table)
{
	if (x >= VGA_WIDTH || y >= VGA_HEIGHT || table == 0)//may remove if slow
		return ;
	table[(y * VGA_WIDTH) + x] = 0;
}

static void	birth(int x, int y, int *table)
{
	if (x >= VGA_WIDTH || y >= VGA_HEIGHT || table == 0)//may remove if slow
		return ;
	table[(y * VGA_WIDTH) + x] = 1;
}

static void	copy_table(int *dest, int *src)
{
	int		i;

	i = 0;
	while (i < VGA_WIDTH * VGA_HEIGHT)
	{
		dest[i] = src[i];
		i++;
	}
}

static enum state		check_state(int x, int y, int *table)
{
	int		livings;
	int		i;
	int		j;

	livings = 0;
	i = y - (y != 0);
	while (i <= y + (y != VGA_HEIGHT))
	{
		j = x - (x != 0);
		while (j <= x + (x != VGA_WIDTH))
		{
			if (table[(i * VGA_WIDTH) + j] == 1 && !(i == y && j == x))
				livings++;
			j++;
		}
		i++;
	}
	if (livings == 3)
		return (LIVE);
	else if (livings == 2)
		return (STAY);
	return (DIE);
}
/*
void	print(int	*table)
{
	int		y;

	y = 0;
	while (y < VGA_HEIGHT)
	{
		int		x = 0;
		while (x < VGA_WIDTH)
		{
			if (table[(y * VGA_WIDTH) + x] == 0)
				printf("⬜");
			else
				printf("🟥");
			x++;
		}
		printf("%c", '\n');
		y++;
	}
	printf("%c", '\n');
}
*/

static void	print(int	*table)
{
	int		y;

	y = 0;
	while (y < VGA_HEIGHT)
	{
		int		x = 0;
		while (x < VGA_WIDTH)
		{
			if (table[(y * VGA_WIDTH) + x] == 0)
			{
				setColour(WHITE);
				terminal_putchar('0');
			}
			else
			{
				setColour(RED);
				terminal_putchar('0');
			}
			x++;
		}
		y++;
	}
	terminal_putchar('\n');
}

static void	generation(int *table)
{
	int		x;
	int		y;
	int		state;
	int		table2[VGA_WIDTH * VGA_WIDTH];

	y = 0;
	state = 0;
	copy_table(table2, table);
	while (y < VGA_HEIGHT)
	{
		x = 0;
		while (x < VGA_WIDTH)
		{
			state = check_state(x, y, table2);
			if (state == LIVE)
				birth(x, y, table);
			else if (state == DIE)
				die(x, y, table);
			else
			{

			}
			x++;
		}
		y++;
	}
}

static void	put_map(int *table, char *map)
{
	int		x;
	int		y;
	int		i;

	x = 0;
	y = 0;
	i = 0;
	while(y < VGA_HEIGHT && map[i] != 0)
	{
		x = 0;
		while (x < VGA_WIDTH)
		{
			if (map[i] == '0' || map [i] == '1')
			{
				table[(y * VGA_WIDTH) + x] = map[i] - '0';
				x++;
			}
			i++;
		}
		y++;
	}
}

void	game(void)//may add parameters for size later on
{
	int		table[VGA_WIDTH * VGA_WIDTH];
	char	*map = "00000000000000000000000000000000000000000000000000000000000000000000000000000000\
					00000000000000000000000000000000000000000000000000000000000000000000000000000000\
					00000000000000000000000000000010000000000000000000000000000000000000000000000000\
					00000000000000000000000000001010000000000000000000000000000000000000000000000000\
					00000000000000000011000000110000000000001100000000000000000000000000000000000000\
					00000000000000000100010000110000000000001100000000000000000000000000000000000000\
					00000011000000001000001000110000000000000000000000000000000000000000000000000000\
					00000011000000001000101100001010000000000000000000000000000000000000000000000000\
					00000000000000001000001000000010000000000000000000000000000000000000000000000000\
					00000000000000000100010000000000000000000000000000000000000000000000000000000000\
					00000000000000000011000000000000000000000000000000000000000000000000000000000000\
					00000000000000000000000000000000000000000000000000000000000000000000000000000000\
					00000000000000000000000000000000000000000000000000000000000000000000000000000000\
					00000000000000000000000000000000000000000000000000000000000000000000000000000000\
					00000000000000000000000000000000000000000000000000000000000000000000000000000000\
					00000000000000000000000000000000000000000000000000000000000000000000000000000000\
					00000000000000000000000000000000000000000000000000000000000000000000000000000000\
					00000000000000000000000000000000000000000000000000000000000000000000000000000000\
					00000000000000000000000000000000000000000000000000000000000000000000000000000000\
					00000000000000000000000000000000000000000000000000000000000000000000000000000000";
					
	bzero_k(table, VGA_WIDTH * VGA_WIDTH);
	put_map(table, map);
	while (true)
	{
		generation(table);
		print(table);
	}
	return ;
}
