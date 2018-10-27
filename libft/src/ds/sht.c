/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sht.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfro <cmalfro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by cmalfro           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by cmalfro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline t_bool	ft_deqsht(t_deq *self, void *out)
{
	return ((t_bool)(ft_deqnsht(self, 1, out) == 1));
}

inline t_bool	ft_sdssht(t_sds *self, char *out)
{
	return ((t_bool)(ft_sdsnsht(self, 1, out) == 1));
}

inline t_bool	ft_vecsht(t_vec *self, void *out)
{
	return ((t_bool)(ft_vecnsht(self, 1, out) == 1));
}
