/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:29:30 by adupin            #+#    #+#             */
/*   Updated: 2023/10/23 12:11:39 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// char	*op_pos(char *str, int op)
// {
// 	size_t	len;

// 	len = ft_strlen(str);
// 	if (op == HEREDOC)
// 		return (ft_strnstr(str, "<<", len));
// 	else if (op == R_APP)
// 		return (ft_strnstr(str, ">>", len));
// 	else if (op == R_INPUT)
// 		return (ft_strnstr(str, "<", len));
// 	else if (op == R_OUTPUT)
// 		return (ft_strnstr(str, ">", len));
// 	else if (op == PIPE)
// 		return (ft_strnstr(str, "|", len));
// 	else
// 		return (NULL);
// }

int	has_operator(char *str, int len)
{
	if (ft_strnstr(str, "<<", len))
		return (HEREDOC);
	else if (ft_strnstr(str, ">>", len))
		return (R_APP);
	else if (ft_strnstr(str, "<", len))
		return(R_INPUT);
	else if (ft_strnstr(str, ">", len))
		return(R_OUTPUT);
	else if (ft_strnstr(str, "|", len))
		return (PIPE);
	else
		return (WORD);	
}

/* Return the index of the minimum positive value */
int	ft_min_index(long int *array, int len)
{
	int	value;
	int	index;
	int	i;

	i = 0;
	index = -1;
	while(i < len)
	{
		if (array[i] != -1)
		{
			if (index == -1)
			{
				value = array[i];
				index = i;
			}
			else if (array[i] < value)
			{
				value = array[i];
				index = i;
			}
		}
		i++;
	}
	return (index);
}

void	*first_appearance(long int *array, char *str)
{
	size_t	len;
	int		i;

	len = ft_strlen(str);
	i = 0;
	array[HEREDOC - 1] = ft_strnstr(str, "<<", len) - str;
	array[R_APP - 1] = ft_strnstr(str, ">>", len) - str;
	array[R_INPUT - 1] = ft_strnstr(str, "<", len) - str;
	array[R_OUTPUT - 1] = ft_strnstr(str, ">", len) - str;
	array[PIPE - 1] = ft_strnstr(str, "|", len) - str;
	while (array[i])
	{
		if (array[i] < 0)
			array[i] = -1;
		i++;
	}
}

t_lex *create_node(char *str)
{
	static int node_index = 0;
	t_lex *node;
	t_lex *new;
	int op;

	node = malloc(sizeof(t_lex));
	if (!node)
		return (NULL);
	op = has_operator(str, 2);
	node->index = node_index;
	printf("str = %s\nop = %d\n", str, op);
	node->operator = op;
	node->word = NULL;
	if (op == WORD)
	{
		node->word = ft_strdup(str);
		if (!node->word)
			return(free(node), NULL);
		node->operator = WORD;
	}
	node->next = NULL;
	node_index++;
	return (node);
}

t_lex	*lexer(char *str)
{
	long int array[5];
	int	i;
	char	*word;
	t_lex *lex;
	t_lex *node;

	i = 0;
	while (str[i])
	{
		first_appearance(array, &str[i]);
		if (ft_min_index(array, 5) == -1)
			node = create_node(&str[i]);
		else if (array[ft_min_index(array, 5)] == 0)
			node = create_node(str);
		else
		{
			word = ft_substr(str, i, array[ft_min_index(array, 5)]);
			if (!str)
				return (0);
			node = create_node(word);
			free(word);
		}
		if (!node)
			return (0);
	}	
	
	
	

	

	
	

	
}
