/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaccell <gbaccell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/17 15:00:00 by gbaccell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*=================== MODO --bench (saida no stderr, fd 2) ===================*/

/*
** Tudo aqui escreve no fd 2 (ft_putstr_fd / ft_putnbr_fd).
** printf nao e permitido (so um ft_printf feito por voces).
** Exemplo de saida (o formato exato e livre):
**   [bench] disorder: 49.93%
**   [bench] strategy: Adaptive / O(n log n)
**   [bench] total_ops: 6784
**   [bench] sa: 0 sb: 0 ss: 0 pa: 3392 pb: 3392
**   [bench] ra: 0 rb: 0 rr: 0 rra: 0 rrb: 0 rrr: 0
*/

/*
** strat_name: "Simple", "Medium", "Complex" ou "Adaptive".
*/
char	*strat_name(t_strat strat);

/*
** strat_complexity: "O(n^2)", "O(n*sqrt(n))" ou "O(n log n)".
** Para a adaptive, usar a complexidade da estrategia REAL escolhida.
*/
char	*strat_complexity(t_strat strat);

/*
** total_ops: soma ctx->ops_count[0] ate ctx->ops_count[OP_SIZE - 1].
*/
int		total_ops(t_ctx *ctx);

/*
** put_percent_fd: imprime dis (0..1) como porcentagem com 2 casas.
**   1. v = (int)(dis * 10000 + 0.5);   ex.: 0.49934 -> 4993
**   2. imprime v / 100       -> "49"
**   3. imprime '.'
**   4. se v % 100 < 10 imprime '0' antes (ex.: 5.07 e nao 5.7)
**   5. imprime v % 100 e depois '%'
*/
void	put_percent_fd(double dis, int fd);

/*
** print_bench: monta as linhas do exemplo acima.
**   asked -> estrategia pedida (cfg->strat), para mostrar o nome
**   used  -> estrategia real (resolve_strat), para mostrar a classe
** Para cada operacao: op_name(op) + ": " + ctx->ops_count[op].
*/
void	print_bench(t_ctx *ctx, t_strat asked, t_strat used, double dis);
