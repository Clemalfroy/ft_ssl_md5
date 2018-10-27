/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/bytes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <cmalfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/11/15 18:23:29 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BYTES_H
# define BYTES_H

# include "tys.h"

int32_t	    ft_get_endianness(void);
uint64_t	swap_int64(const uint64_t data);
uint32_t	swap_int32(const uint32_t data);
uint32_t    left_rotate_32(uint32_t word, uint32_t delta);

#endif
