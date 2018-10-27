/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <cmalfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:53:08 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

inline int	ft_stris(const char *s1, int (*cb)(int))
{
	char const *s;

	s = s1;
	while (*s)
		if (!cb(*s++))
			return (0);
	return (s > s1);
}

inline char	*ft_strnew(size_t size)
{
	char			*str;
	unsigned int	i;

	i = -1;
	if ((str = (char *)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	while (++i <= size)
		str[i] = 0;
	return (str);
}
