#include "ft_regex.h"

t_pattern	*create_pattern(int (*is_match)(char *, int, char *))
{
	t_pattern	*pattern;

	if (!(pattern = (t_pattern *)ft_memalloc(sizeof(t_pattern))))
		return (NULL);
	pattern->dyn_str = ft_strdup("");
	pattern->min = 1;
	pattern->max = 1;
	pattern->is_match = is_match;
	return (pattern);
}

void		free_pattern(t_pattern **pattern)
{
	if (!pattern || !(*pattern))
		return ;
	if ((*pattern)->dyn_str)
		ft_strdel(&(*pattern)->dyn_str);
	free(*pattern);
	pattern = NULL;
}
