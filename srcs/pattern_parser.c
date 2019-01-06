#include "ft_regex.h"

int		is_quantifier(char c)
{	
	return (c == '{' || c == '*' || c == '+' || c == '?');
}


int		is_range(const char *str)
{
	if (!str || ft_strlen(str) < 3)
		return (0);
	return (ft_isascii(str[0]) && str[1] == '-' && ft_isascii(str[2]) && str[2] != ']');
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
	t_pattern *pattern_expr;

	if (!expr_pattern || !pattern || !index)
		return ;
	pattern_expr = create_pattern(&char_match);
	add_str(&(pattern_expr->dyn_str), ft_strsub(pattern, *index, 1));
	ft_lstpush(expr_pattern, ft_lstnew(pattern_expr, sizeof(pattern_expr)));
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
			*index+=2;
		}
		else
		{
			c = ft_strdup("1");
			c[0] = pattern[*index];
			add_str(&(pattern_expr->dyn_str), c);
		}
		(*index)++;
	}
	return (0);
}

int		parse_limits(t_list **expr_pattern, const char *pattern, int *index)
{
	t_pattern	*selection;

	printf("parse limits\n");

	if (!expr_pattern || !(*expr_pattern) || !pattern || !index)
		return (0);
	
	selection = (t_pattern *)ft_lstgetindex(expr_pattern, ft_lstlen(expr_pattern) - 1)->content;

	printf("quantifier is %c\n", (unsigned char)pattern[*index]);

	if ((unsigned char)pattern[*index] == '*')
	{
		selection->min = 0;
		selection->max = -1; // infini
	}
	else if ((unsigned char)pattern[*index] == '+')
	{
		printf("Setting up max pattern to -1 for + qualifier\n");
		selection->min = 1;
		selection->max = -1;
	}
	else if ((unsigned char)pattern[*index] == '?')
	{
		printf("Setting up max pattern to 1 for ? qualifier\n");
		selection->min = 0;
		selection->max = 1;
	}
	else if ((unsigned char)pattern[*index] == '{')
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
		if (pattern[index] == '[')
		{
			index++;
			parse_collection(&expr_pattern, pattern, &index);
		}
		else if (is_quantifier(pattern[index]))
		{
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
