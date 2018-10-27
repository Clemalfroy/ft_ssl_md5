/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <cmalfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline t_bool	ft_deqpop(t_deq *self, void *out)
{
	return ((t_bool)(ft_deqnpop(self, 1, out) == 1));
}

inline t_bool	ft_sdspop(t_sds *self, char *out)
{
	return ((t_bool)(ft_sdsnpop(self, 1, out) == 1));
}

inline t_bool	ft_vecpop(t_vec *self, void *out)
{
	return ((t_bool)(ft_vecnpop(self, 1, out) == 1));
}
