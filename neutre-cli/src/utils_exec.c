#include "neutraliza-cli.h"

void	execute_cmd(t_exec_flags *exec_flags)
{
	if (exec_flags->opt_d)
		display_dashboard();
	else if (exec_flags->opt_h)
		print_help_menu();
	else if (exec_flags->opt_l) 
	{
		if (exec_flags->form_b)
			print_beautiful_logs(exec_flags);
		else if (exec_flags->form_m)
			print_minified_logs(exec_flags);
	}
	else
		print_help_msg_exit();
	return ;
}
