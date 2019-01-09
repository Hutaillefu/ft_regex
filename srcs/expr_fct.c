#include "ft_regex.h"

int		collection_match(char *str, int index, char *dyn_str)
{
	char **tokens;
	int	i;
	unsigned char char_index;

	if (!str || index < 0 || !dyn_str)
		return (-1);

	tokens = ft_strsplit(dyn_str, '\n');
	i = -1;
	while (tokens[++i])
	{
		if (ft_strlen(tokens[i]) == 1 && str[index] == tokens[i][0]) // single char
		{
			ft_free_tab(tokens);
			return (1);
		}
		else if (ft_strlen(tokens[i]) == 3 && (unsigned char)tokens[i][1] == '-') // range
		{
			if ((unsigned char)tokens[i][0] > (unsigned char)tokens[0][2])
			{
				ft_free_tab(tokens);
				return (-1); 
			}
			char_index = (unsigned char)tokens[i][0];
			while (char_index <= (unsigned char)tokens[i][2])
			{
				if ((unsigned char)str[index] == char_index)
				{
					ft_free_tab(tokens);
					return (1);
				}
				char_index++;
			}
		}
	}
	ft_free_tab(tokens);
	return (0);
}



int		char_match(char *str, int index, char *dyn_str)
{
	if (!str || index < 0 || !dyn_str)
		return (-1);
	return ((unsigned char)*dyn_str == '.' ?
		(unsigned char)str[index] != '\n':
		(unsigned char)str[index] == (unsigned char)*dyn_str);
}
