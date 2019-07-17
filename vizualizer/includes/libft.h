/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:18:09 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/29 19:41:47 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define ABS(Value) (Value < 0 ? -(Value) : Value)

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void *memptr, int value, size_t num);
void				ft_bzero(void *s, size_t n);
int					ft_memcmp(const void *arr1, const void *arr2, size_t n);
void				*ft_memccpy(void *dest, const void *source,
		int ch, size_t count);
void				*ft_memmove(void *dest, const void *source, size_t count);
void				*ft_memchr(const void *arr, int c, size_t n);
int					ft_memcmp(const void *arr1, const void *arr2, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *str);
char				*ft_strcpy(char *dest, const char *source);
char				*ft_strncpy(char *dest, const char *source, size_t n);
char				*ft_strcat(char *dest, const char *append);
char				*ft_strncat(char *dest, const char *append, size_t n);
size_t				ft_strlcpy(char *dest, const char *source, size_t n);
size_t				ft_strlcat(char *dest, const char *source, size_t n);
char				*ft_strchr(const char *str, int ch);
char				*ft_strrchr(const char *str, int ch);
char				*ft_strstr(const char *str1, const char *str2);
char				*ft_strnstr(const char *str1, const char *str2, size_t n);
int					ft_strcmp(const char *str1, const char *str2);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_isdigit(int ch);
int					ft_isalpha(int ch);
int					ft_isalnum(int ch);
int					ft_isprint(int ch);
int					ft_isascii(int ch);
int					ft_toupper(int ch);
int					ft_tolower(int ch);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
char				*ft_strrev(char *s);
int					ft_atoi(const char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_putendl(char const *s);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del) (void*, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_isspace(int ch);
int					ft_count_words(char const *s);
void				ft_lstaddback(t_list **alst, t_list *new);
void				ft_setbackground_fd(int backg, int fd);
char				*ft_free_join(char *new, char *src);
t_list				*ft_list_add(void *str, int elem);
t_list				*ft_list_push_back(t_list **begin_list,
		void *str, int elem);
t_list				*ft_list_foreach_if(t_list *begin_list, int elem);
void				ft_abs(int *nbr);
void				ft_absf(float *nbr);
float				ft_truncf(float nbr);
int					ft_pow(int nbr, int power);
char				*ft_free_strjoin_duo(char const *s1, char const *s2);
char				*ft_free_strjoin_rev(char *src, char *new);
char				*ft_ftoa(long double nbr);
char				*ft_ltoa_base(long n, int base);
char				*ft_ltoa(long n);
char				*ft_ultoa_base(unsigned long n, int base);
char				*ft_ultoa(unsigned long n);
void				ft_frtwarr(void **arr, int size);
void				ft_list_remove_free_if(t_list **begin_list, int elem);
int					get_next_line(int fd, char **line);
int					ft_max(int a, int b);
int					ft_min(int a, int b);
int					ft_isdigonly(char *str);

#endif
