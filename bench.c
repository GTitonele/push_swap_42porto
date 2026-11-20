/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilherme <guilherme@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/19 19:24:41 by guilherme        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*strat_name(t_strat strat)
{
	if (strat == STRAT_SIMPLE)
		return ("Simple");
	if (strat == STRAT_MEDIUM)
		return ("Medium");
	if (strat == STRAT_COMPLEX)
		return ("Complex");
	return ("Adaptive");
}

char	*strat_complexity(t_strat strat)
{
	if (strat == STRAT_SIMPLE)
		return ("O(n^2)");
	if (strat == STRAT_MEDIUM)
		return ("O(n*sqrt(n))");
	return ("O(n log n)");
}

int	total_ops(t_ctx *ctx)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (i < OP_SIZE)
	{
		total += ctx->ops_count[i];
		i++;
	}
	return (total);
}

void	put_percent_fd(double dis, int fd)
{
	int	v;

	v = (int)(dis * 10000 + 0.5);
	ft_putnbr_fd(v / 100, fd);
	ft_putchar_fd('.', fd);
	if (v % 100 < 10)
		ft_putchar_fd('0', fd);
	ft_putnbr_fd(v % 100, fd);
	ft_putchar_fd('%', fd);
}

void	print_bench(t_ctx *ctx, t_strat asked, t_strat used, double dis)
{
	int	op;

	ft_putstr_fd("[bench] disorder: ", 2);
	put_percent_fd(dis, 2);
	ft_putstr_fd("\n[bench] strategy: ", 2);
	ft_putstr_fd(strat_name(asked), 2);
	ft_putstr_fd(" / ", 2);
	ft_putstr_fd(strat_complexity(used), 2);
	ft_putstr_fd("\n[bench] total_ops: ", 2);
	ft_putnbr_fd(total_ops(ctx), 2);
	ft_putstr_fd("\n[bench]", 2);
	op = 0;
	while (op < OP_SIZE)
	{
		ft_putchar_fd(' ', 2);
		ft_putstr_fd(op_name(op), 2);
		ft_putstr_fd(": ", 2);
		ft_putnbr_fd(ctx->ops_count[op], 2);
		op++;
	}
	ft_putchar_fd('\n', 2);
}
