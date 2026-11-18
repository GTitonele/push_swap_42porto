/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaccell <gbaccell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/18 17:09:59 by gbaccell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*================= NORMALIZACAO (valores -> indices 0..n-1) =================*/

/*
** Por que normalizar?
** O radix (complex) e os chunks (medium) ficam MUITO mais simples se os
** numeros forem 0, 1, 2, ..., n-1 em vez de valores quaisquer
** (negativos, gigantes, espacados). A ordem relativa nao muda, entao
** o resultado (as operacoes) e o mesmo.
** Ex.: [ 42, -7, 1000, 3 ]  ->  [ 2, 0, 3, 1 ]
** O disorder pode ser calculado antes ou depois: da o mesmo valor.
*/

/*
** stack_to_array: copia os valores da pilha (do topo ao fundo) para um
** array novo com malloc. Retorna NULL se o malloc falhar.
*/
int		*stack_to_array(t_stack *a);

/*
** sort_array: ordena o array em ordem crescente.
** Pode ser um bubble/insertion sort simples: isso NAO conta como
** operacao do push_swap, e so preparacao interna.
*/
void	sort_array(int *arr, int size);

/*
** normalize: troca o content de cada no pela sua POSICAO no array
** ordenado.
**   1. arr = stack_to_array(a); se NULL -> retorna 0
**   2. sort_array(arr, a->size);
**   3. para cada no da pilha (percorrer exatamente a->size nos):
**        procurar node->content em arr; o indice encontrado vira o
**        novo content
**   4. free(arr); retorna 1
*/
int		normalize(t_stack *a);
