/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:11:10 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/06 13:41:22 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _COMPLETION_H
# define _COMPLETION_H

# include <dirent.h>

t_list			*get_file_list(char *buffer, t_list **env_list);
int				get_max_name_len(t_list *comp_list);
char			*get_name(struct dirent *file);
int				case_unsensitive_ncmp(const char *s1, const char *s2, size_t n);

#endif
