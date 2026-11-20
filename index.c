/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilherme <guilherme@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:00:00 by gbaccell          #+#    #+#             */
/*   Updated: 2026/11/19 19:25:42 by guilherme        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*stack_to_array(t_stack *a)
{
	int		*arr;
	t_node	*node;
	int		i;

	arr = malloc(sizeof(int) * a->size);
	if (!arr)
		return (NULL);
	node = a->top;
	i = 0;
	while (i < a->size)
	{
		arr[i] = node->content;
		node = node->next;
		i++;
	}
	return (arr);
}

void	sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	find_index(int *arr, int size, int value)
{
	int	k;

	k = 0;
	while (k < size)
	{
		if (arr[k] == value)
			return (k);
		k++;
	}
	return (-1);
}

int	normalize(t_stack *a)
{
	int		*arr;
	t_node	*node;
	int		i;

	arr = stack_to_array(a);
	if (!arr)
		return (0);
	sort_array(arr, a->size);
	node = a->top;
	i = 0;
	while (i < a->size)
	{
		node->content = find_index(arr, a->size, node->content);
		node = node->next;
		i++;
	}
	free(arr);
	return (1);
}
