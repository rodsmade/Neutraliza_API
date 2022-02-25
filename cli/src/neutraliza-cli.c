#include "neutraliza-cli.h"

void	capture_flags(int argc, char *argv[], t_exec_flags *exec_flags)
{
	if (argv[1][0] != '-')
		print_help_msg_exit();
	if (argc == 2)	// tem 1 argumento só (além do nome do pgm)
	{
		if (argv[1][0] == '-' && argv[1][1] == '-')	// o arg começa com '--'
		{
			if (strcmp(&argv[1][2], "help") == 0)	// é '--help'
			{
				exec_flags->opt_h = 1;
				exec_flags->opt_d = 0;
			}
			else if (strcmp(&argv[1][2], "all") == 0)	// é '--all'
			{
				exec_flags->opt_a = 1;
				exec_flags->opt_d = 0;
			}
			else if (strcmp(&argv[1][2], "dashboard") != 0)	// se for '--dashboard' segue o flow sem alterar nada (DEFAULT)
				print_help_msg_exit();	// não é nem '--help' e nem '--dashboard'
		}
		else	// o arg não começa com '--'
			print_help_msg_exit();
	}
	if (argc == 3)
	{
		printf("chorei\n");
	}
	return ;
}

void init_flags(t_exec_flags *exec_flags)
{
	exec_flags->opt_d = 1;
	exec_flags->opt_h = 0;
	exec_flags->opt_a = 0;
	exec_flags->type_a = 1;
	exec_flags->type_g = 0;
	exec_flags->type_p = 0;
	exec_flags->type_i = 0;
	exec_flags->type_e = 0;
	exec_flags->form_m = 1;
	exec_flags->form_b = 0;
	return ;
}

void	run_command(int argc, char *argv[])
{
	t_exec_flags	exec_flags;

	init_flags(&exec_flags);
	capture_flags(argc, argv, &exec_flags);
	if (exec_flags.opt_d)
	{
		display_dashboard();
	}
	if (exec_flags.opt_h)
		print_help_menu();
	if (exec_flags.opt_a) 
	{
		if (exec_flags.form_m)
			printf("printa lista minificada\n");
		if (exec_flags.form_b)
			printf("printa lista beautificada\n");
	}
}

int	main(int argc, char *argv[])
{
	if (argc == 1)
		display_dashboard();
	else if (argc < 1 || argc > 3)
		print_help_msg_exit();
	else
		run_command(argc, argv);
	return (0);
}