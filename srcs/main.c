#include "ft_regex.h"

int	main(int argc, char **argv)
{
	t_regex regex;

	if (argc != 3)
	{
		printf("Usage : ./regex str pattern");
		return (-1);
	}

	// TODO 
	//	- plusieurs chars qui se suivent dans le pattern doivent etre process en tant que string pour pouvoir utiliser l'operateur |


	printf("Get_Matches return %d\n", get_matches(&regex, argv[1], argv[2]));
	free_regex(&regex);
	return (0);
}
