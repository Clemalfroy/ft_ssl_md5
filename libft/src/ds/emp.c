/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfro <cmalfro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by cmalfro           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by cmalfro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/sds.h"

inline char	*ft_sdsemp(t_sds *self, size_t idx, char const *items)
{
	return (ft_sdsmput(self, idx, items, ft_strlen(items)));
}
