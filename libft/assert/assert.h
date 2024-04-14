/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbiteau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:04:09 by cbiteau           #+#    #+#             */
/*   Updated: 2024/03/08 14:04:10 by cbiteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSERT_H

# define ASSERT_H

# include <stdio.h>
# include <string.h>

typedef struct s_tests
{
	int		tests_success;
	int		tests_failed;
	int		log_level;
	char	name[256];
}				t_tests;

t_tests			init_tester(char name[256], int log_level);
void			tests_header(t_tests *tests);
void			tests_result(t_tests *tests);
void			ft_assert(int actual, char *behavior, t_tests *tests);
void			ft_assert_cmp(int act, int exp, char *behavior, t_tests *tests);
void			ft_assert_strcmp(char *act, char *exp, char *behavior,
					t_tests *tests);
#endif
