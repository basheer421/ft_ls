/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 03:16:03 by bammar            #+#    #+#             */
/*   Updated: 2024/07/02 03:18:09 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * delete func ft_lstdelone(current, destroy_file);
 * delete if ((t_file *)(current->content))->name[0] == '.'
*/
static void remove_hidden_files(t_list **files)
{
    t_list *current;
    t_list *prev;
    t_list *next;

    current = *files;
    prev = NULL;

    while (current)
    {
        next = current->next; // Save next node since current might be deleted
        t_file *file = (t_file *)(current->content);

        // Check if the file name starts with '.'
        if (file->name[0] == '.')
        {
            // Remove the current node and free its content using destroy_file
            ft_lstdelone(current, destroy_file);
            
            if (prev)
                prev->next = next;  // Update the previous node to skip deleted node
            else
                *files = next;  // If the head was deleted, update the head
        }
        else
        {
            // Move prev pointer only if current wasn't deleted
            prev = current;
        }

        current = next;  // Move to the next node
    }
}

// rev files order
void	rev(t_list **files, int keep_hidden)
{
	t_list	*current;
	t_list	*prev;
	t_list	*next;

	current = *files;
	prev = NULL;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*files = prev;
	if (!keep_hidden)
		remove_hidden_files(files);
}
