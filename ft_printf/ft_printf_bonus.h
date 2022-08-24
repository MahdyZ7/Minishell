/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:57:03 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/10 08:59:29 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H
# include <stdarg.h>
# include <unistd.h>
# include "../libft/libft.h"

int	ft_printf(const char *str, ...);
int	ft_printfchar_b(int c, int dash, int width);
int	ft_printfstr_b(char *str, int *flags);
int	ft_printfptr_b(long long int p, int dash, int width);
int	ft_printfunsgned_b(unsigned int p, int *flags, unsigned int base, char up);
int	ft_printfint_b(int num, int *flags);
#endif