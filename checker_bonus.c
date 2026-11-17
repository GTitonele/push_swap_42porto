/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaccell <gbaccell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/17 15:00:00 by gbaccell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*========================= BONUS - programa checker =========================*/

/*
** SO FAZER DEPOIS DA PARTE OBRIGATORIA PERFEITA.
** Este arquivo NAO esta no SRCS do Makefile. Para o bonus:
**   - criar a regra 'bonus' no Makefile gerando o executavel 'checker'
**   - usar os mesmos arquivos do push_swap, MENOS o main.c
**   - precisa de um get_next_line (ler o stdin linha por linha)
**
** Fluxo do main do checker:
**   1. sem argumentos -> sai sem mostrar nada
**   2. parse_args(argv, 1, &a); se falhar -> "Error\n" no stderr
**   3. le cada linha do stdin; para cada uma: exec_op;
**      operacao invalida -> libera tudo e "Error\n"
**   4. no fim: is_sorted(a) && b vazia -> "OK\n", senao -> "KO\n"
*/

/*
** exec_op: executa a operacao lida (ex.: "sa\n").
** IMPORTANTE: usar as PRIMITIVAS (swap, push, rotate, rev_rotate) e nao
** sa()/pb()..., porque essas imprimem a operacao no stdout.
** Comparar com ft_strncmp incluindo o '\n' (ex.: "rra\n").
** Retorna 1 se a operacao existe, 0 se e invalida.
*/
int		exec_op(t_stack *a, t_stack *b, char *line);
