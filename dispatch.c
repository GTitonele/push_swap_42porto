/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilherme <guilherme@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/19 18:22:43 by guilherme        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*======================= FLUXO PRINCIPAL DA ORDENACAO =======================*/

/*
** resolve_strat: converte a estrategia PEDIDA na estrategia REAL usada.
**   - strat != STRAT_ADAPTIVE -> retorna strat (flag forcada pelo usuario)
**   - strat == STRAT_ADAPTIVE -> decide pelo disorder (limites do subject):
**       disorder <  0.2          -> STRAT_SIMPLE   O(n^2)
**       0.2 <= disorder < 0.5    -> STRAT_MEDIUM   O(n * sqrt(n))
**       disorder >= 0.5          -> STRAT_COMPLEX  O(n log n)
** Obs.: com pouca desordem o O(n^2) e barato, pois quase nao precisa
** rotacionar. Essa justificativa tem que ir para o README.
*/
t_strat	resolve_strat(t_strat strat, double dis)
{
	if (strat != STRAT_ADAPTIVE)
		return (strat);
	if (dis < 0.2)
		return (STRAT_SIMPLE);
	if (dis < 0.5)
		return (STRAT_MEDIUM);
	return (strat)
}

/*
** sort_with: chama o algoritmo correspondente a estrategia REAL.
**   - a->size <= 5 -> sort_small(ctx)   (casos pequenos, poucas operacoes)
**   - STRAT_SIMPLE  -> sort_simple(ctx)
**   - STRAT_MEDIUM  -> sort_medium(ctx)
**   - STRAT_COMPLEX -> sort_complex(ctx)
** Norm: switch e proibido, usar if / else if.
** Decidam (e expliquem no README) se o sort_small vale para todas as
** estrategias ou so para a adaptive.
*/
void	sort_with(t_ctx *ctx, t_strat strat);

/*
** run_push_swap: tudo o que acontece DEPOIS do parsing.
** Chamada pelo main logo depois do parse_args (assim o main nao passa
** do limite de 5 variaveis da Norm).
**   1. dis = disorder(ctx->a);          ANTES de qualquer movimento
**   2. used = resolve_strat(cfg->strat, dis);
**   3. se a pilha nao esta ordenada (is_sorted):
**        a. normalize(ctx->a); se falhar (malloc) -> error_exit(ctx)
**        b. sort_with(ctx, used);
**      se ja esta ordenada nao imprime NENHUMA operacao
**   4. se cfg->bench -> print_bench(ctx, cfg->strat, used, dis);
**      (o bench aparece mesmo com a pilha ja ordenada: 0 operacoes)
*/
void	run_push_swap(t_ctx *ctx, t_cfg *cfg)
{
	(void)cfg;
	if (is_sorted(ctx->a))
		return ;
	if (ctx->a->size <= 5)
		sort_small(ctx);
	else
		sort_simple(ctx);
}
