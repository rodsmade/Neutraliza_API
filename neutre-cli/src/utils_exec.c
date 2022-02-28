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
			printf("printa lista beautificada\n");
		else
			printf("printa lista minificada\n");
		if (exec_flags->type_a)
			printf("printa todos os logs\n");
		if (exec_flags->type_g)
			printf("printa logs de get\n");
		if (exec_flags->type_p)
			printf("printa logs de post\n");
		if (exec_flags->type_e)
			printf("printa logs de erro\n");
		if (exec_flags->type_i)
			printf("printa logs de info\n");
	}
	else
		print_help_msg_exit();
	return ;
}
