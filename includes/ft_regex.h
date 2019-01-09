#ifndef FT_REGEX_H
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
	int	(*is_match)(char *, int, char *);
}		t_pattern;

typedef struct s_regex
{
	int	matched;
	int	flags;
	t_list	*patterns;
}		t_regex;

t_pattern	*create_pattern(int (*is_match)(char *, int, char *));
void		free_pattern(t_pattern **pattern);
void		free_regex(t_regex *regex);

int			get_matches(t_regex *regex, const char *str, const char *pattern);

t_list		*parse(const char *pattern);

int			char_match(char *str, int start_pos, char *dyn_str);
int			collection_match(char *str, int start_pos, char *dyn_str);
#endif
