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

int		parse_collection(t_list **expr_pattern, const char *pattern, int *index)
{
	int 		pattern_len;
	t_pattern	*pattern_expr;
	char		*c;

	if (!expr_pattern || !pattern || !index)
		return (0);

	pattern_len = ft_strlen(pattern);
	pattern_expr = create_pattern(&collection_match);
	while (*index < pattern_len)
	{
		if (pattern[*index] == ']')
		{
			ft_lstpush(expr_pattern, ft_lstnew(pattern_expr, sizeof(pattern_expr)));
			return (1);
		}
		else if (is_range(&(pattern[*index])))
		{
			add_str(&(pattern_expr->dyn_str), ft_strsub(pattern, *index, 3));
			printf("%s", pattern_expr->dyn_str);
			*index+=2;
		}
		else
		{
			c = ft_strdup("1");
			c[0] = pattern[*index];
			add_str(&(pattern_expr->dyn_str), c);
			printf("%s", pattern_expr->dyn_str);
		}
		(*index)++;
	}
	return (0);
}

int		parse_limits(t_list **expr_pattern, const char *pattern, int *index)
{
	t_pattern	*selection;
	
	if (!expr_pattern || !(*expr_pattern) || !pattern || !index)
		return (0);
	
	selection = (t_pattern *)ft_lstgetindex(expr_pattern, ft_lstlen(expr_pattern) - 1)->content;

	if (pattern[*index] == '*')
	{
		selection->min = 0;
		selection->max = -1; // infini
	}
	else if (pattern[*index] == '+')
	{
		selection->min = 1;
		selection->max = -1;
	}
	else if (pattern[*index] == '?')
	{
		selection->min = 0;
		selection->max = 1;
	}

	return (1);
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

void		parse_char(t_list **expr_pattern, const char *pattern, int *index)
{
	t_pattern *pattern_expr;

	if (!expr_pattern || !pattern || !index)
		return ;
	pattern_expr = create_pattern(&char_match);
	add_str(&(pattern_expr->dyn_str), ft_strsub(pattern, *index, 1));
	ft_lstpush(expr_pattern, ft_lstnew(pattern_expr, sizeof(pattern_expr)));
}

t_list		*parse(const char *pattern)
{
	t_list	*expr_pattern;
	int	index;
	int	pattern_len;


	if (!pattern)
		return (NULL);
	index = 0;
	expr_pattern = NULL;
	pattern_len = ft_strlen(pattern);
	while (index < pattern_len)
	{
		if (pattern[index] == '[')
		{
			index++;
			parse_collection(&expr_pattern, pattern, &index);
		}
		else if (is_quantifier(pattern[index]))
		{
			index++;
			parse_limits(&expr_pattern, pattern, &index);
		}
		else
		{
			parse_char(&expr_pattern, pattern, &index);
		}
		index++;
	}

	return (expr_pattern);
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
