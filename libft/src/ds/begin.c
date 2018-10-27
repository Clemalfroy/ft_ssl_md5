/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfro <cmalfro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by cmalfro           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by cmalfro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void	*ft_deqbeg(t_deq *self)
{
	return (self->buf + (self->cur * self->isz));
}

inline char	*ft_sdsbeg(t_sds *self)
{
	return (self->buf);
}

inline void	*ft_vecbeg(t_vec *self)
{
	return (self->buf);
}
