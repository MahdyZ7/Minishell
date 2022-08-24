/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:03:23 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/26 09:40:53 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns no of strings btween delimiters "c" in string "s"*/
static int	strno(char const *s, char c)
{
	int	num;

	num = 0;
	if (*s == c || *s == 0)
		--num;
	while (*s)
	{
		if (*s == c && *(s + 1) != c && *(s + 1) != 0)
			++num;
		++s;
	}
	return (num + 1);
}

/* Returns length of string "s" from the beginning till the delimiter char "c"*/
static int	lennexchar(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

/* free the array of strings if a single malloc fails occure*/
static void	freesplit(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i] != 0)
		free(strarr[i++]);
	free (strarr);
}

/*Returns am array of strings obtained by splitting "s" at char "c" occurences
**malloc DANGER**/
char	**ft_split(char const *s, char c)
{
	int		pos;
	int		nostr;
	char	**strarr;

	pos = -1;
	if (!s)
		return (0);
	nostr = strno(s, c);
	strarr = (char **)malloc((nostr + 1) * sizeof(char *));
	if (strarr == 0)
		return (0);
	while (++pos < nostr)
	{
		while (*s == c)
			s++;
		strarr[pos] = ft_substr(s, 0, lennexchar(s, c));
		if (strarr[pos] == 0)
		{
			freesplit (strarr);
			return (NULL);
		}
		s += lennexchar(s, c);
	}
	strarr[pos] = 0;
	return (strarr);
}
