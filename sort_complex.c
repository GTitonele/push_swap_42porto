/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilherme <guilherme@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/19 19:25:09 by guilherme        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*===================== ESTRATEGIA COMPLEX - O(n log n) ======================*/

/*
** Ideia (radix sort LSD binario): olha um bit por vez, do menos para o
** mais significativo. Em cada passada, quem tem o bit 0 vai para b e
** quem tem o bit 1 fica em a; depois tudo volta para a.
** Precisa da pilha NORMALIZADA (0..n-1, sem negativos).
*/

/*
** max_bits: quantos bits sao necessarios para representar max.
**   bits = 0; while ((max >> bits) != 0) bits++;
** Ex.: max = 99 -> 7 bits | max = 499 -> 9 bits
*/
int	max_bits(int max)
{
	int	bits;

	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

/*
** radix_pass: uma passada para o bit 'bit'.
**   size = ctx->a->size; repetir size vezes:
**     se ((ctx->a->top->content >> bit) & 1) == 0 -> pb
**     senao                                       -> ra
**   depois: enquanto b nao vazia -> pa
*/
void	radix_pass(t_ctx *ctx, int bit)
{
	int	size;
	int	i;

	size = ctx->a->size;
	i = 0;
	while (i < size)
	{
		if (((ctx->a->top->content >> bit) & 1) == 0)
			pb(ctx);
		else
			ra(ctx);
		i++;
	}
	while (ctx->b->size > 0)
		pa(ctx);
}

/*
** sort_complex: para bit de 0 ate max_bits(get_max(ctx->a)) - 1:
**   radix_pass(ctx, bit);
**   (otimizacao opcional: parar se is_sorted(ctx->a))
**
** Complexidade (em operacoes):
**   log2(n) passadas x ~2n operacoes cada = O(n log n)
**   Espaco: O(1) extra.
** Referencia: ~1084 ops para 100 numeros e ~6784 para 500. Passa no
** minimo do subject (< 2000 / < 12000); para "excelente" (< 700 /
** < 5500) precisa de um algoritmo mais otimizado.
*/
void	sort_complex(t_ctx *ctx)
{
	int	bits;
	int	bit;

	bits = max_bits(get_max(ctx->a));
	bit = 0;
	while (bit < bits)
	{
		radix_pass(ctx, bit);
		bit++;
	}
}
