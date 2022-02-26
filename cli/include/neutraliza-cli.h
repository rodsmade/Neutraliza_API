#ifndef HEADER_H
# define HEADER_H

// ------------------------------------------------		INCLUDES	-----------

# include <stdio.h>		// dprintf()
# include <stdlib.h>	// error()
# include <string.h>	// strcmp()
# include <stdarg.h>	// vargs
# include <unistd.h>	// needed for get_next_line()

# define	BUFFER_SIZE	100

// ------------------------------------------------		TYPEDEFS	-----------

typedef struct s_exec_flags
{
	int	opt_d;	// default = 0;		display dashboard;
	int	opt_h;	// default = 0;		display help msg;
	int	opt_a;	// default = 0;		log type: all;
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

// utils_init.c
void		init_flags(t_exec_flags *exec_flags);

// utils_libft.c
char		*ft_strchr(const char *s, int c);

// utils_libft.c
int 		count_logs(const char *log_type, ...);

// utils_parsing.c
void		capture_flags(int argc, char *argv[], t_exec_flags *exec_flags);
void		check_flags_consistency(t_exec_flags *exec_flags);

// utils_print.c
void		print_help_msg_exit(void);
void		print_help_menu(void);
void		display_dashboard(void);

// utils_strings.c
char	*append_n_strs(char* body, int count_append, char *appendage, ...);

#endif