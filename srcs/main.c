#include "ft_regex.h"

#include <stdio.h>

int	main(void)
{
	t_regex regex;

	printf("Get_Matches return %d\n", 
		get_matches(&regex,
		"Cognac Con Christophe Caracasse",
		"C[oha]"));
	return (0);
}
