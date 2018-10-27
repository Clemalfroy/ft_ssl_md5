/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfro <cmalfro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by cmalfro           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by cmalfro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void				*ft_deqput(t_deq *self, size_t idx)
{
	return (ft_deqnput(self, idx, 1));
}

inline char				*ft_sdsput(t_sds *self, size_t idx)
{
	return (ft_sdsnput(self, idx, 1));
}

inline void				*ft_vecput(t_vec *self, size_t idx)
{
	return (ft_vecnput(self, idx, 1));
}
