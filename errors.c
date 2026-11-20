/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 18:44:38 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 10:30:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_ctx(t_ctx *ctx)
{
	free_stack(ctx->a);
	free_stack(ctx->b);
	free(ctx->buf);
	ctx->buf = NULL;
	ctx->len = 0;
	ctx->cap = 0;
}

void	error_exit(t_ctx *ctx)
{
	free_ctx(ctx);
	ft_putendl_fd("Error", 2);
	exit(1);
}
