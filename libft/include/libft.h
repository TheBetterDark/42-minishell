/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:06:50 by smoore            #+#    #+#             */
/*   Updated: 2025/02/11 12:57:08 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>

int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isdigit_str(char *str);
int						ft_isalnum(int c);
int						ft_isalnum_str(char *str);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_memcmp(const void *str1, const void *str2, size_t n);
int						ft_atoi(const char *nptr);
long long				ft_atol(const char *str);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strnstr(const char *big, const char *little,
							size_t len);
char					*ft_strdup(const char *s);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_itoa(int n);
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
								char));
char					**ft_split(char const *s, char c);
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
void					*ft_memset(void *s, int c, size_t n);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memmove(void *dest, const void *src, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
void					*ft_calloc(size_t nmemb, size_t size);
size_t					ft_strlen(const char *s);
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_ltoa(long long n);

// --------------------BONUS-----------------------------------------
typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

int						ft_lstsize(t_list *lst);
void					ft_lstadd_front(t_list **lst, t_list *new);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstnew(void *content);
t_list					*ft_lstlast(t_list *lst);
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));

// ---------------GET NEXT LINE--------------------------------------

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list_len
{
	char				*str;
	size_t				len;
	struct s_list_len	*next;
}						t_list_len;

void					pop_head(t_list_len **head);
int						has_newline(t_list_len *head);
size_t					len_of_newline(t_list_len *head);
char					*gnl_substr(char const *s, size_t start, size_t size);
char					*get_next_line(int fd);

// ---------------------FT_PRINTF------------------------------------

int						ft_printf(const char *f_str, ...);
int						print_str(char *str);
int						print_hex(unsigned int num, char f_char);
int						print_ptr(unsigned long long ptr);
int						print_unsigned(unsigned int num);

// ---------------------NEW------------------------------------------

void					*ft_malloc(size_t size, t_list *mem);
void					ft_free_all(t_list *mem);
void					ft_free(void *ptr, t_list *mem);
void					ft_str_arr_free(char ***head);
char					**ft_str_arr_add(const char **str_arr, const char *str);
char					**ft_str_arr_minus(const char **str_arr,
							const char *str);
char					**ft_str_arr_dup(const char **str_arr);
char					*ft_str_arr_has(const char **str_arr, const char *str);
void					ft_str_arr_out(const char **str_arr);

// ---------------------FT_SNPRINTF------------------------------------

int						ft_snprintf(char *buffer, size_t size,
							const char *format, ...);
int						ft_putchar_buf(char *buffer, size_t size, char c);
int						ft_putstr_buf(char *buffer, size_t size,
							const char *str);
int						ft_putnbr_buf(char *buffer, size_t size, int n);
int						ft_putunbr_buf(char *buffer, size_t size,
							unsigned int n);
int						ft_putendl_buf(char *buffer, size_t size,
							const char *str);
char					*ft_strupr(char *str);
char					*ft_tobase(unsigned long num, int base);
#endif
