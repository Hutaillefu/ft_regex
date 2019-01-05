#include "ft_regex.h"

#include <stdio.h>

int	main(void)
{
	t_regex regex;

	printf("Get_Matches return %d\n", 
		get_matches(&regex, "Hello World !", "[a-z-+0-9]"));
	return (0);
}
