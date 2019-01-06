#include "ft_regex.h"

#include <stdio.h>

int	main(void)
{
	t_regex regex;

	printf("Get_Matches return %d\n", 
		get_matches(&regex,
		"Salut nazis nature noob naas n9f neant ",
		"n.[ao]+"));
	return (0);
}
