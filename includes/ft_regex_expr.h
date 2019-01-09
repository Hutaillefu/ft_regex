/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_regex_expr.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: htaillef <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 16:25:04 by htaillef     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/09 16:25:06 by htaillef    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_REGEX_EXPR_H
# define FT_REGEX_EXPR_H

/*
  ** The flags to use to customise regex process.
*/

# define FLAGS_G 1
# define FLAGS_M 2
# define FLAGS_I 4

/*
  ** Set up each char used for parsing
*/

# define QUANTIFIER_0_MORE 		'*'
# define QUANTIFIER_1_MORE 		'+'
# define QUANTIFIER_0_1 		'?'
# define QUANTIFIER_GROUP_START	'{'
# define QUANTIFIER_GROUP_END 	'}'

# define COLLECTION_START		'['
# define COLLECTION_END			']'
# define RANGE_SEPARATOR		'-'
#endif
