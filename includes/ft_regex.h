#ifndef FT_regex_H
# define FT_REGEX_H

typedef struct	s_match
{
	int	str_start;	// Start ptr of match in str
	int	str_end;	// End   ptr of match in str
	int	word_index;	// Word index of match in str
}		t_match;

typedef struct	s_matches
{
	int	nb_match;
	t_match	*matches;
}		t_matches;

typedef struct s_regex
{
	char	*str;
	char	*pattern;
}		t_regex;

t_matches	*get_matches(t_regex *regex);
#endif
