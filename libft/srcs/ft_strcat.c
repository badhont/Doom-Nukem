/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:43:44 by lfatton           #+#    #+#             */
/*   Updated: 2018/05/30 15:26:01 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	s1len;
	size_t	i;

	s1len = ft_strlen(s1);
	i = 0;
	while (s2[i])
	{
		s1[s1len + i] = s2[i];
		i++;
	}
	s1[s1len + i] = '\0';
	return (s1);
}
