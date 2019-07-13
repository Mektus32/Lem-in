#include "lem_in.h"
// ищем длину инта, для прохождение по строке
int		ft_len_int(int num)
{
	int	len;

	len = 0;
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	if (num == 0)
		return (1);
	return (len);
}

int ft_max_mass(int *mass)
{
	int max;
	int i;

	i = 0;
	max = mass[i++];
	while (mass[i])
	{
		if(mass[i] > max)
			max = mass[i];
		i++;
	}
	return (max);
}
