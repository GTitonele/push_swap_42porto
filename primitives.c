/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 08:47:49 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/09 11:04:44 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*======================= PRIMITIVAS DA LISTA CIRCULAR =======================*/

/*
** pop_top: remove o no do topo da pilha e o devolve (sem free).
**   - pilha vazia           -> retorna NULL
**   - so 1 elemento         -> pilha fica vazia (top = NULL)
**   - 2 ou mais elementos   -> religa o anterior (fundo) com o
**                              proximo e o proximo vira o topo
** Usada apenas por push().
*/
static t_node	*pop_top(t_stack *stack)
{
	t_node	*node;

	if (!stack || stack->size < 1)
		return (NULL);
	node = stack->top;
	if (stack->size < 2)
		stack->top = NULL;
	else
	{
		node->previous->next = node->next;
		node->next->previous = node->previous;
		stack->top = node->next;
	}
	stack->size--;
	return (node);
}

/*
** swap: troca os dois primeiros elementos da pilha.
**   - menos de 2 elementos  -> nao faz nada
**   - exatamente 2          -> basta mover o top, pois a lista
**                              e circular (A <-> B)
**   - mais de 2             -> troca os ponteiros de top e
**                              new_top mantendo os vizinhos
**                              (fundo e terceiro elemento) ligados
** Antes:  fundo <-> top <-> new_top <-> terceiro
** Depois: fundo <-> new_top <-> top <-> terceiro
*/
void	swap(t_stack *stack)
{
	t_node	*new_top;
	t_node	*top;

	if (!stack || stack->size < 2)
		return ;
	top = stack->top;
	new_top = top->next;
	if (stack->size > 2)
	{
		top->previous->next = new_top;
		new_top->next->previous = top;
		new_top->previous = top->previous;
		top->previous = new_top;
		top->next = new_top->next;
		new_top->next = top;
		stack->top = new_top;
	}
	stack->top = new_top;
}

/*
** push: tira o topo de src e coloca no topo de dst.
**   - src vazia  -> nao faz nada
**   - dst vazia  -> o no vira uma lista circular de 1 elemento
**                   (next e previous apontam para ele mesmo)
**   - senao      -> insere o no entre o fundo de dst e o topo
**                   atual de dst, e ele passa a ser o novo topo
*/
void	push(t_stack *src, t_stack *dst)
{
	t_node	*src_top;

	if (!src || !dst || src->size < 1)
		return ;
	src_top = pop_top(src);
	if (dst->size < 1)
	{
		src_top->next = src_top;
		src_top->previous = src_top;
	}
	else
	{
		src_top->next = dst->top;
		src_top->previous = dst->top->previous;
		dst->top->previous->next = src_top;
		dst->top->previous = src_top;
	}
	dst->top = src_top;
	dst->size++;
}

/*
** rotate: o primeiro elemento vira o ultimo.
** Como a lista e circular, basta avancar o top para top->next.
*/
void	rotate(t_stack *stack)
{
	if (!stack || stack->size < 2)
		return ;
	stack->top = stack->top->next;
}

/*
** rev_rotate: o ultimo elemento vira o primeiro.
** Como a lista e circular, basta recuar o top para top->previous.
*/
void	rev_rotate(t_stack *stack)
{
	if (!stack || stack->size < 2)
		return ;
	stack->top = stack->top->previous;
}
