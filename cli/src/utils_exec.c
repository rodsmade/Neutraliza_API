#include "neutraliza-cli.h"

void	execute_cmd(t_exec_flags *exec_flags)
{
	if (exec_flags->opt_d)
		display_dashboard();
	else if (exec_flags->opt_h)
		print_help_menu();
	else if (exec_flags->opt_a) 
	{
		if (exec_flags->form_b)
			printf("printa lista beautificada\n");
		else
			printf("printa lista minificada\n");
	}
	else
		printf("algo de errado não está certo\n");
	return ;
}
