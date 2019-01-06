#ifndef FT_regex_H
# define FT_REGEX_H

#include "libft.h"

#include <stdio.h>

typedef struct	s_match
{
	int	str_start;	// Start ptr of match in str
	int	str_end;	// End   ptr of match in str
	int	word_index;	// Word index of match in str
}		t_match;

# define FLAGS_G 1
# define FLAGS_M 2
# define FLAGS_I 4

typedef struct	s_pattern
{
	char	*dyn_str;
	int	min;
	int	max;
	int	(*is_match)(char *, int, struct s_pattern *);
}		t_pattern;

typedef struct s_regex
{
	int	matched;
	int	flags;
	t_list	*patterns;
}		t_regex;

t_pattern	*create_pattern(int (*is_match)(char *, int, struct s_pattern *));

int		get_matches(t_regex *regex, const char *str, const char *pattern);

t_list		*parse(const char *pattern);

int		single_char_match(char *str, int start_pos, t_pattern *pattern);
int		any_char_match(char *str, int start_pos, t_pattern *pattern);
int		chars_match(char *str, int start_pos, t_pattern *pattern);
int		single_str_match(char *str, int start_pos, t_pattern *pattern);
#endif
