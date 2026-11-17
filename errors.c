/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaccell <gbaccell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 18:44:38 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/17 16:11:22 by gbaccell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** error_exit: saida padrao de erro do programa.
** Libera as duas pilhas (evita leaks), escreve "Error\n" no
** stderr (fd 2), como pede o subject, e sai com codigo 1.
*/
void	error_exit(t_ctx *ctx)
{
	free_stack(ctx->a);
	free_stack(ctx->b);
	ft_putendl_fd("Error", 2);
	exit(1);
}
