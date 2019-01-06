#include "ft_regex.h"

#include <stdio.h>

void		add_str(char **str, char *new_str)
{
	char *ret;

	if (!str || !new_str)
		return ;

	ret = *str;
	*str = ft_strjoin(*str, new_str);
	free(ret);

	ret = *str;
	*str = ft_strjoin(*str, "\n");
	free(ret);
}

t_pattern	*create_pattern(int (*is_match)(char *, int, t_pattern *))
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

int		is_range(const char *str)
{
	if (!str || ft_strlen(str) < 3)
		return (0);
	return (ft_isascii(str[0]) && str[1] == '-' && ft_isascii(str[2]) && str[2] != ']');
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

int		is_quantifier(char c)
{	
	return (c == '{' || c == '*' || c == '+' || c == '?');
}

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
