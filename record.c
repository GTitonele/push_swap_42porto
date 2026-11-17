/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 11:59:17 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/09 21:51:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** op_name: converte um t_ops no texto da operacao ("sa", "pb"...).
** Monta uma tabela local indexada pelo enum e devolve a string.
** Retorna NULL se op for invalido (>= OP_SIZE).
** Tambem sera util para o --bench (imprimir o nome de cada contador).
*/
char	*op_name(t_ops op)
{
	char	*names[OP_SIZE];

	if (op >= OP_SIZE)
		return (NULL);
	names[OP_PA] = "pa";
	names[OP_PB] = "pb";
	names[OP_RA] = "ra";
	names[OP_RB] = "rb";
	names[OP_RR] = "rr";
	names[OP_RRA] = "rra";
	names[OP_RRB] = "rrb";
	names[OP_RRR] = "rrr";
	names[OP_SA] = "sa";
	names[OP_SB] = "sb";
	names[OP_SS] = "ss";
	return (names[op]);
}

/*
** record_op: chamada por TODA operacao depois de executada.
**   1. pega o nome da operacao
**   2. incrementa o contador dessa operacao (para o --bench)
**   3. imprime o nome + '\n' no stdout (saida oficial do programa)
*/
void	record_op(t_ctx *ctx, t_ops op)
{
	char	*operation;

	operation = op_name(op);
	if (!operation)
	{
		ft_putendl_fd("record_op: invalid op", 2);
		return ;
	}
	ctx->ops_count[op]++;
	ft_putendl_fd(operation, 1);
}
