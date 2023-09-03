

#include "minishell.h"

t_ast	*make_command_node(t_token *start, t_ast *up, int end_index, int *error_index)
{
	t_ast		*new;
	t_pipeline	*pipeline;

	if (*error_index == MALLOC_FAIL)
		return (NULL);
	pipeline = form_pipeline(start, end_index, error_index);
	//printf("error %d\n", *error_index); //debug
	//print_token(start, ON); //debug
	if (!pipeline)
		return (NULL);
	new = new_ast_node(up, pipeline, PIPE, error_index);
	if (!new)
		return (NULL);
	return (new);
}

t_token	*remove_braces(t_token *start, t_token *end, int *error_index)
{
	t_token	*new_start;

	new_start = start;
	if (start->type != LPAR && start->type != WORD && !is_redir(start->type))
		return (handle_error_value(error_index, start->position), NULL);
	if (start->type == LPAR)
	{
		new_start = start->next;
		end = last_node(new_start, end);
		if (!end || end->type != RPAR)
			return (handle_error_value(error_index, start->position), NULL);
	}
	return (new_start);
}

t_ast	*branch_out(t_token *start, t_ast *up, int end_index, int *error_index)
{
	t_token	*new_start;
	int		index;

	if (!start) // || find_logic_token(start, end_index) == start->position
		return (handle_error_value(error_index, end_index), NULL);
	index = find_logic_token(start, end_index);
	if (index == PARENTHESES_ERROR)
	{
		new_start = remove_braces(start, node_at_index(start, end_index), error_index);
		if (!new_start)
			return (NULL);
		end_index = last_node(new_start, node_at_index(start, end_index))->position;
		start = new_start;
	}
	return (form_tree(start, up, end_index, error_index));
}

t_ast	*form_tree(t_token *start, t_ast *up, int end_index, int *error_index)
{
	t_ast	*new;
	int		index;

	if (*error_index == MALLOC_FAIL || !start)
		return (NULL);
	index = find_logic_token(start, end_index);
	//printf("logic index is %d\n", index); //debug
	//printf("start index is %d\n", start->position); //debug
	//printf("end index is %d\n", end_index); //debug
	if (index == PARENTHESES_ERROR)
	{
		if (start->type == LPAR)
			index = token_after_parentheses(start, end_index);
		else
			index = find_token(start, end_index, LPAR);
		return (handle_error_value(error_index, index), NULL);
	}
	if (index == NO_LOGIC)
		return (make_command_node(start, up, end_index, error_index));
	new = new_ast_node(up, NULL, node_at_index(start, index)->type, error_index);
	if (!new)
		return (NULL);
	new->left = branch_out(start, new, index, error_index);
	new->right = branch_out(node_at_index(start, index)->next, new, end_index, error_index);
	return (new);
}