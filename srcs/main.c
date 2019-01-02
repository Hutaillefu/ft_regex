#include "ft_regex.h"

int	main(void)
{
	t_regex regex;

	regex.str = "Get all word with beggining with a w";
	regex.pattern = "w[a-z]+";
	(void)regex;
	return (0);
}
