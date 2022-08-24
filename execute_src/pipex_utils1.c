/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:59:22 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/25 17:59:56 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* free the output of ft_split after we are done with it*/
void	clear_str_sep(char **str_sep)
{
	int	i;

	i = 0;
	if (str_sep)
	{
		while (str_sep[i])
			free(str_sep[i++]);
		free (str_sep);
	}
}

/*Appends suffex string "sufstr" to the prefix string "prestr" 
up until "sufstr" char 0 or new line. 
Return -1 if Memory allocation failed, 0 otherwise
**malloc DANGER**/
int	ft_strjoin_ms(char **prestr, char *sufstr)
{
	int		i1;
	int		i2;
	char	*fullstr;

	i1 = 0;
	i2 = 0;
	fullstr = (char *)malloc(ft_strlen(*prestr) + ft_strlen(sufstr) + 1);
	if (fullstr == NULL)
		return (print_error("", "malloc failed", -1));
	while (*prestr && (*prestr)[i1])
	{
		fullstr[i1] = (*prestr)[i1];
		++i1;
	}
	while (sufstr && sufstr[i2])
		fullstr[i1++] = sufstr[i2++];
	fullstr[i1] = 0;
	if (*prestr)
		free (*prestr);
	*prestr = fullstr;
	return (0);
}

/* Compare the first "n" chars from strings "s1" & "s2".
Return the diffrence in the first char or 0 if no diffrence is found
** PROTECTED **/
int	ft_strncmp_p(const char *s1, const char *s2, size_t n)
{
	size_t	pos;

	pos = 0;
	if (!n || !s1 || !s2)
		return (0);
	while (pos < (n - 1) && s1[pos] && s2[pos] && (unsigned char)s1[pos]
		== (unsigned char)s2[pos])
		pos++;
	return ((unsigned char)s1[pos] - (unsigned char)s2[pos]);
}

/* Compare the first "n" chars from strings "s1" & "s2".
Return the diffrence in the first char or 0 if no diffrence is found
** PROTECTED and not case sensitive **/
int	ft_strncmp_pc(const char *s1, const char *s2, size_t n)
{
	size_t	pos;

	pos = 0;
	if (!n || !s1 || !s2)
		return (0);
	while (pos < (n - 1) && s1[pos] && s2[pos]
		&& ft_tolower((unsigned char)s1[pos])
		== ft_tolower((unsigned char)s2[pos]))
		pos++;
	return ((unsigned char)s1[pos] - (unsigned char)s2[pos]);
}

// make all chars of str lowercase
void	ft_tolower_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str && str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] -= 'A' - 'a';
		++i;
	}
}
