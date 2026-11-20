/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_target.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsouza <elsouza@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 15:40:00 by elsouza           #+#    #+#             */
/*   Updated: 2026/11/20 15:40:00 by elsouza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_value_pos(t_stack *s, int v)
{
	t_node	*node;
	int		i;

	node = s->top;
	i = 0;
	while (i < s->size)
	{
		if (node->content == v)
			return (i);
		node = node->next;
		i++;
	}
	return (-1);
}

int	target_in_b(t_stack *b, int v)
{
	t_node	*node;
	int		best;
	int		i;

	node = b->top;
	best = -1;
	i = 0;
	while (i < b->size)
	{
		if (node->content < v && node->content > best)
			best = node->content;
		node = node->next;
		i++;
	}
	if (best == -1)
		return (find_max_pos(b));
	return (find_value_pos(b, best));
}

int	target_in_a(t_stack *a, int v)
{
	t_node	*node;
	int		best;
	int		i;

	node = a->top;
	best = INT_MAX;
	i = 0;
	while (i < a->size)
	{
		if (node->content > v && node->content < best)
			best = node->content;
		node = node->next;
		i++;
	}
	if (best == INT_MAX)
		return (find_min_pos(a));
	return (find_value_pos(a, best));
}
