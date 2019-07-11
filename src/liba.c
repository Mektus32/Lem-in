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