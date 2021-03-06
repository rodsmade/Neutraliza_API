#ifndef HEADER_H
# define HEADER_H

// ------------------------------------------------		INCLUDES	-----------

# include <stdio.h>		// dprintf()
# include <stdlib.h>	// error()
# include <string.h>	// strcmp()
# include <stdarg.h>	// vargs
# include <unistd.h>	// needed for get_next_line()
# include "cJSON.h"		// parse to/from JSON

# define	BUFFER_SIZE	100

// ------------------------------------------------		TYPEDEFS	-----------

typedef struct s_exec_flags
{
	int	opt_d;	// default = 0;		display dashboard;
	int	opt_h;	// default = 0;		display help msg;
	int	opt_l;	// default = 0;		list logs (all by default);
	int	type_a;	// default = 0;		log type: all;
	int	type_g;	// default = 0;		log type: GET;
	int	type_p;	// default = 0;		log type: POST;
	int	type_i;	// default = 0;		log type: INFO;
	int	type_e;	// default = 0;		log type: ERROR;
	int	form_m;	// default = 0;		format: minified;
	int	form_b;	// default = 0;		format: bbbeeeautifulll,ø¤°º¤ø,¸¸,ø¤º°º¤
}	t_exec_flags;

typedef struct s_endpoint
{
	char	*uri;
	char	*method;
	int		tot_reqs;
}	t_endpoint;

// ------------------------------------------------		PROTOTYPES	-----------
// utils_exec.c
void		execute_cmd(t_exec_flags *exec_flags);

// utils_get_next_line.c
char		*get_next_line(int fd);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			contains_nl(char *string);

// utils_init.c
void		init_flags(t_exec_flags *exec_flags);

// utils_libft.c
char		*ft_strchr(const char *s, int c);
void		ft_free_arr(void ***arr);
void		ft_free_ptr(void **ptr);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);

// utils_log_search.c
int			match_entry_by_str(char *line, char *log_type, char *uri, char *method);
int			count_logs(char *log_type, char *uri, char *method);

// utils_parsing.c
void		capture_flags(int argc, char *argv[], t_exec_flags *exec_flags);
void		check_flags_concurrency(t_exec_flags *exec_flags);

// utils_print.c
void		print_help_msg_exit(void);
void		print_help_menu(void);
void		display_dashboard(void);
void		print_beautiful_logs(t_exec_flags *exec_flags);
void		print_minified_logs(t_exec_flags *exec_flags);

// utils_strings.c
char		*append_n_strs(char* body, int count_append, char *appendage, ...);

#endif