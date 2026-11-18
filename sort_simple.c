/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaccell <gbaccell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/18 13:41:01 by gbaccell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*======================== ESTRATEGIA SIMPLE - O(n^2) ========================*/

/*
** sort_simple: extracao do minimo (adaptacao do selection sort).
**   1. enquanto a->size > 3 (ou > 0):
**        pos = find_min_pos(ctx->a);
**        bring_to_top_a(ctx, pos);    leva o menor ao topo
**        pb(ctx);                     guarda em b
**   2. sort_three(ctx) para o que sobrou (se parou em 3)
**   3. enquanto b nao vazia -> pa(ctx);
**      (b tem os menores com o maior no topo, entao voltam em ordem)
**
** Complexidade (em operacoes):
**   n extracoes x ate n/2 rotacoes cada = O(n^2)
**   Espaco: O(1) extra (so a pilha b).
** Com disorder baixo o menor quase sempre ja esta perto do topo,
** por isso o adaptive usa este para disorder < 0.2.
*/
void	sort_simple(t_ctx *ctx)
{
	while (ctx->a->size > 0)
	{
		bring_to_top_a(ctx, find_min_pos(ctx->a));
		pb(ctx);
	}
	while (ctx->b->size > 0)
		pa(ctx);
}
