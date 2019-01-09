#include "ft_regex.h"

int		is_quantifier(char c)
{	
	return (c == QUANTIFIER_GROUP_START || c == QUANTIFIER_0_MORE ||
			c == QUANTIFIER_1_MORE || c == QUANTIFIER_0_1);
}


int		is_range(const char *str)
{
	if (!str || ft_strlen(str) < 3)
		return (0);
	return (ft_isascii(str[0]) && str[1] == RANGE_SEPARATOR &&
			ft_isascii(str[2]) && str[2] != COLLECTION_END);
}

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

void		parse_char(t_list **expr_pattern, const char *pattern, int *index)
{
	t_pattern 	*pattern_expr;
	char		*c;

	if (!expr_pattern || !pattern || !index)
		return ;
	pattern_expr = create_pattern(&char_match);
	c = ft_strsub(pattern, *index, 1);
	add_str(&(pattern_expr->dyn_str), c);
	ft_lstpush(expr_pattern, ft_lstnew(pattern_expr, sizeof(pattern_expr)));
	ft_strdel(&c);
}

int		parse_collection(t_list **expr_pattern, const char *pattern, int *index)
{
	int 		pattern_len;
	t_pattern	*pattern_expr;
	char		*c;

	if (!expr_pattern || !pattern || !index)
		return (0);
	(*index)++;
	pattern_len = ft_strlen(pattern);
	pattern_expr = create_pattern(&collection_match);
	while (*index < pattern_len)
	{
		if (pattern[*index] == COLLECTION_END)
		{
			ft_lstpush(expr_pattern, ft_lstnew(pattern_expr, sizeof(pattern_expr)));
			return (1);
		}
		else if (is_range(&(pattern[*index])))
		{
			c = ft_strsub(pattern, *index, 3);
			add_str(&(pattern_expr->dyn_str), c);
			*index+=2;
			ft_strdel(&c);
		}
		else
		{
			c = ft_strdup("1");
			c[0] = pattern[*index];
			add_str(&(pattern_expr->dyn_str), c);
			ft_strdel(&c);
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

	if ((unsigned char)pattern[*index] == QUANTIFIER_0_MORE)
	{
		selection->min = 0;
		selection->max = -1;
	}
	else if ((unsigned char)pattern[*index] == QUANTIFIER_1_MORE)
	{
		selection->min = 1;
		selection->max = -1;
	}
	else if ((unsigned char)pattern[*index] == QUANTIFIER_0_1)
	{
		selection->min = 0;
		selection->max = 1;
	}
	else if ((unsigned char)pattern[*index] == QUANTIFIER_GROUP_START)
	{
		(*index)++;
		// process range quantifier
	}

	return (1);
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
		if (pattern[index] == COLLECTION_START)
			parse_collection(&expr_pattern, pattern, &index);
		else if (is_quantifier(pattern[index]))
			parse_limits(&expr_pattern, pattern, &index);
		else
			parse_char(&expr_pattern, pattern, &index);
		index++;
	}
	return (expr_pattern);
}
