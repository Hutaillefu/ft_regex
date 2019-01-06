#include "ft_regex.h"

int		collection_match(char *str, int index, t_pattern *pattern)
{
	char **tokens;
	int	i;

	if (!str || index < 0 || !pattern)
		return (-1);

	tokens = ft_strsplit(pattern->dyn_str, '\n');
	i = 0;
	while (tokens[i])
	{
		if (ft_strlen(tokens[i]) == 1 && str[index] == tokens[i][0])
		{
			return (1); // match 1 char
		}
		i++;
	}
	return (-1);
}



int		char_match(char *str, int index, t_pattern *pattern)
{
	int nb;

	nb = index;
	while ((pattern->dyn_str[0] == '.' ? str[nb] != '\n' : str[nb] == pattern->dyn_str[0]))
	{
		if (pattern->max == 1) // ?
			return (1);
		nb++;
	}
	if (nb - index == 0 && pattern->min == 1)
		return (-1);
	return (nb - index);	
}
