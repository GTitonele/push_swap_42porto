/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_query.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaccell <gbaccell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/18 14:43:25 by gbaccell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *s)
{
	t_node	*node;
	int		i;

	node = s->top;
	i = 0;
	while (i < s->size - 1)
	{
		if (node->content > node->next->content)
			return (0);
		node = node->next;
		i++;
	}
	return (1);
}

int	find_min_pos(t_stack *s)
{
	t_node	*node;
	int		i;
	int		min;
	int		pos;

	node = s->top;
	i = 0;
	min = node->content;
	pos = i;
	while (i < s->size)
	{
		if (node->content < min)
		{
			min = node->content;
			pos = i;
		}
		node = node->next;
		i++;
	}
	return (pos);
}

int	find_max_pos(t_stack *s)
{
	t_node	*node;
	int		i;
	int		max;
	int		pos;

	node = s->top;
	i = 0;
	max = node->content;
	pos = i;
	while (i < s->size)
	{
		if (node->content > max)
		{
			max = node->content;
			pos = i;
		}
		node = node->next;
		i++;
	}
	return (pos);
}

int	get_max(t_stack *s)
{
	t_node	*node;
	int		i;
	int		max;

	node = s->top;
	i = 0;
	max = node->content;
	while (i < s->size)
	{
		if (node->content > max)
			max = node->content;
		node = node->next;
		i++;
	}
	return (max);
}
