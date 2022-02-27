#include "neutraliza-cli.h"

void	init_flags(t_exec_flags *exec_flags)
{
	exec_flags->opt_d = 0;
	exec_flags->opt_h = 0;
	exec_flags->opt_l = 0;
	exec_flags->type_a = 0;
	exec_flags->type_g = 0;
	exec_flags->type_p = 0;
	exec_flags->type_i = 0;
	exec_flags->type_e = 0;
	exec_flags->form_m = 0;
	exec_flags->form_b = 0;
	return ;
}
