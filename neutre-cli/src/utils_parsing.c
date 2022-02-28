#include "neutraliza-cli.h"

static void	check_double_dash(char *argv, t_exec_flags *exec_flags)
{
	if (strcmp(&argv[2], "dashboard") == 0)
		exec_flags->opt_d = 1;
	else if (strcmp(&argv[2], "help") == 0)
		exec_flags->opt_h = 1;
	else if (strcmp(&argv[2], "list") == 0)
		exec_flags->opt_l = 1;
	else if (strcmp(&argv[2], "all") == 0)
		exec_flags->type_a = 1;
	else if (strcmp(&argv[2], "get") == 0)
		exec_flags->type_g = 1;
	else if (strcmp(&argv[2], "post") == 0)
		exec_flags->type_p = 1;
	else if (strcmp(&argv[2], "info") == 0)
		exec_flags->type_i = 1;
	else if (strcmp(&argv[2], "error") == 0)
		exec_flags->type_e = 1;
	else if (strcmp(&argv[2], "mini") == 0)
		exec_flags->form_m = 1;
	else if (strcmp(&argv[2], "beauty") == 0)
		exec_flags->form_b = 1;
	else
		print_help_msg_exit();
	return ;
}

static void	check_single_dash(char *argv, t_exec_flags *exec_flags)
{
	int	i = 0;

	while (argv[++i])
	{
		if (argv[i] == 'd')
			exec_flags->opt_d = 1;
		else if (argv[i] == 'h')
			exec_flags->opt_h = 1;
		else if (argv[i] == 'l')
			exec_flags->opt_l = 1;
		else if (argv[i] == 'a')
			exec_flags->type_a = 1;
		else if (argv[i] == 'g')
			exec_flags->type_g = 1;
		else if (argv[i] == 'p')
			exec_flags->type_p = 1;
		else if (argv[i] == 'i')
			exec_flags->type_i = 1;
		else if (argv[i] == 'e')
			exec_flags->type_e = 1;
		else if (argv[i] == 'm')
			exec_flags->form_m = 1;
		else if (argv[i] == 'b')
			exec_flags->form_b = 1;
		else
			print_help_msg_exit();
	}
	return ;
}

void	capture_flags(int argc, char *argv[], t_exec_flags *exec_flags)
{
	int	i = 0;

	while (++i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')	// o arg começa com '--'
			check_double_dash(argv[i], exec_flags);
		else if (argv[i][0] == '-' && argv[i][1] && argv[i][1] != '-') // o arg começa com '-'
			check_single_dash(argv[i], exec_flags);
		else
			print_help_msg_exit();
	}
	return ;
}

void	check_flags_concurrency(t_exec_flags *exec_flags)
{
	// crazy boolean logic BUT. if it is NOT the case that ONLY ONE between 
	// d, h or a flags is true, than REFUSE INPUT because the three operations
	// cannot concur !!
	if ((!exec_flags->opt_d || exec_flags->opt_h || exec_flags->opt_l)
		&& (exec_flags->opt_d || !exec_flags->opt_h || exec_flags->opt_l)
		&& (exec_flags->opt_d || exec_flags->opt_h || !exec_flags->opt_l))
		print_help_msg_exit();
	if (exec_flags->form_m && exec_flags->form_b)
		print_help_msg_exit();
	if (exec_flags->opt_l
		&& (!exec_flags->type_g && !exec_flags->type_p && !exec_flags->type_e
			&& !exec_flags->type_i))
		exec_flags->type_a = 1;
	return ;
}
