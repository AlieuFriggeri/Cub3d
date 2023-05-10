/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:35:05 by vgroux            #+#    #+#             */
/*   Updated: 2023/01/19 18:37:51 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	else if (n == 0)
		len++;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	ft_float_len(long double nb)
{
	int			len;

	len = 0;
	if (nb == 0.0)
		return (1);
	while (nb != 0.0)
	{
		nb *= 10;
		nb -= (int)nb;
		len++;
	}
	return (len);
}

char	*ft_ftoa(long double n)
{
	int			nb;
	long double	deci;
	char		*str;
	size_t		len;

	nb = (int)n;
	deci = n - (long double)nb;
	len = ft_intlen(nb) + 1 + ft_float_len(deci);
	str = ft_calloc(len, sizeof(char));
	if (!str)
		return (NULL);
	len = 0;
	if (n < 0)
		str[len++] = '-';
	while (nb != 0)
	{
		str[len] = nb % 10;
	}
}
