/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfro <cmalfro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by cmalfro           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by cmalfro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline char	*ft_sdsprd(t_sds *self, char const *items)
{
	return (ft_sdsmusht(self, items, ft_strlen(items)));
}
