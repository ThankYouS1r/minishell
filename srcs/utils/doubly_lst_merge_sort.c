#include "utils.h"

void	doubly_lst_merge(t_dlst *left, t_dlst *right, t_dlst **merged)
{
	t_dlst	*tmp;	

	*merged = NULL;
	if (left == NULL)
	{
		*merged = right;
		return ;
	}
	if (right == NULL)
	{
		*merged = left;
		return ;
	}
	if (ft_strcmp(left->str, right->str) < 0)
	{
		*merged = left;
		left = left->next;
	}
	else
	{
		*merged = right;
		right = right->next;
	}
	(*merged)->prev = NULL;
	tmp = *merged;
	while (left && right)
	{
		if (ft_strcmp(left->str, right->str) < 0)
		{
			(*merged)->next = left;
			left = left->next;
		}
		else
		{
			(*merged)->next = right;
			right = right->next;
		}
		(*merged)->next->prev = (*merged);
		*merged = (*merged)->next;
	}
	while (left)
	{
		(*merged)->next = left;
		(*merged)->next->prev = (*merged);
		*merged = (*merged)->next;
		left = left->next;
	}
	while (right)
	{
		(*merged)->next = right;
		(*merged)->next->prev = (*merged);
		*merged = (*merged)->next;
		right = right->next;
	}
	*merged = tmp;
}

void	doubly_lst_split(t_dlst *src, t_dlst **left, t_dlst **right)
{
	t_dlst	*fast;
	t_dlst	*slow;

	if (src == NULL || src->next == NULL)
	{
		*left = src;
		*right = NULL;
		return ;
	}
	slow = src;
	fast = src->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			fast = fast->next;
			slow = slow->next;
		}
	}
	*left = src;
	*right = slow->next;
	slow->next = NULL;
}

void	doubly_lst_merge_sort(t_dlst **head)
{
	t_dlst	*left;
	t_dlst	*right;

	left = NULL;
	right = NULL;
	if ((*head == NULL) || ((*head)->next == NULL))
		return ;
	doubly_lst_split(*head, &left, &right);
	doubly_lst_merge_sort(&left);
	doubly_lst_merge_sort(&right);
	doubly_lst_merge(left, right, head);
}
