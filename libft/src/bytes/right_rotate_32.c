/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endianness.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <cmalfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/bytes.h"

uint32_t  right_rotate_32(uint32_t word, uint32_t delta)
{
	return ((word >> delta) | (word << ((sizeof(int32_t) * 8) - delta)));
}