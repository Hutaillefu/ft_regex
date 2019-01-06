#include "ft_regex.h"

#include <stdio.h>

void		process(t_regex *regex, const char *str, t_list *expr_pattern)
{
	t_list	*it;
	int	index;
	int	add;
	int	start_index;

	if (!regex || !str || !expr_pattern)
		return ;
	index = 0;
	start_index = -1;
	add = 0;
	while (start_index < (int)ft_strlen(str))
	{
		it = expr_pattern;
		start_index++;
		index = start_index;
		while (it)
		{
			add = ((t_pattern *)it->content)->is_match((char *)str, index, (t_pattern *)it->content);
			if (add == -1)
				break ;
			index += add;
			it = it->next;
		}
		if (add > 0 && !it)
		{
			regex->matched = 1;
			printf("fully match\n");
			start_index = index;
		}

	}
}

int	get_matches(t_regex *regex, const char *str, const char *pattern)
{
	t_list	*expr_pattern;
	
	if (!regex || !str || !pattern)
		return (-1);		// Bad parameter pointer
	regex->matched = 0;
	
	if (!(expr_pattern = parse(pattern)))
		return (-2);		// Bad pattern

	process(regex, str, expr_pattern);

	return (regex->matched);
}
