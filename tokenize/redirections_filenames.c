

#include "minishell.h"

t_bool	save_redirection_filenames(t_token *current)
{
	t_token	*tmp;

	while (current)
	{
		if (is_redir(current->type))
		{
			if (current->next && current->next->type == WORD)
			{
				current->filename = current->next->content;
				current->quote += current->next->quote;
				tmp = current->next;
				current->next = current->next->next;
				free(tmp);
			}
		}
		current = current->next;
	}
	return (FALSE);
}