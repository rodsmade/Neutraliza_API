#include "header.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newitem;

	newitem = malloc(sizeof(t_list));
	newitem->content = content;
	newitem->next = NULL;
	return (newitem);
}

int	ft_lstsize(t_list *lst)
{
	int	count_items;

	if (lst == NULL)
		return (0);
	count_items = 1;
	while (lst->next != NULL)
	{
		count_items++;
		lst = lst->next;
	}
	return (count_items);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_element;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last_element = ft_lstlast(*lst);
		last_element->next = new;
	}
}
