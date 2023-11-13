/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 06:42:21 by julthoma          #+#    #+#             */
/*   Updated: 2023/11/13 06:42:21 by julthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_fdf(char *filename)
{
    (void)filename;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_printf("usage: ./fdf <filename>\n");
        return (0);
    }
    ft_fdf(argv[1]);
    return (0);
}
