#include "ft_regex.h"

#include <stdio.h>

int	main(void)
{
	t_regex regex;

	printf("Get_Matches return %d\n", 
		get_matches(&regex,
		"soona noob",
		".*"));
	return (0);
}
