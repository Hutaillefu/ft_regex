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
	(*pattern)->is_match = NULL;
	free(*pattern);
	pattern = NULL;
}

void		free_pattern_maillon(void *content, int content_size)
{
	t_pattern	**pattern;

	(void)content_size;
	if (!content)
		return ;
	pattern = (t_pattern **)content;
	if (!pattern || !(*pattern))
		return ;
	free_pattern(pattern);
}

/*
   ** Free each maillon and its content using 'del'.
   ** If del is null, free only the maillon.
*/

void		free_list(t_list **lst, void (*del)(void *, int))
{
	t_list	*it;
	t_list	*next;

	if (!lst || !(*lst))
		return ;
	it = *lst;
	while (it)
	{
		next = it->next;
		if (del)
			del(&(it->content), it->content_size);
		free(it);
		it = next;
	}
	lst = NULL;
}

void		free_regex(t_regex *regex)
{
	if (!regex)
		return ;
	free_list(&(regex->patterns), free_pattern_maillon);
	regex->matched = 0;
	regex->flags = 0;
}
