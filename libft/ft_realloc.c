/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:51:20 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/16 13:00:18 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Changes the size of the memory block pointed to by ptr to size bytes.
The contents will be unchanged in the range from the start of the region up to the
minimum of the old and new sizes.  If the new size is larger than the old size, the  added
memory  will  not  be  initialized.   If  ptr is NULL, then the call is equivalent to mal‐
loc(size), for all values of size; if size is equal to zero, and ptr is not NULL, then the
call  is  equivalent  to  free(ptr).
Unless ptr is NULL, it must have been re turned by an earlier call to malloc(), calloc(), or realloc().*/
void		*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	new_ptr = malloc(size);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}
