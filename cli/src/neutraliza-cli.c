#include "neutraliza-cli.h"

void	parse_input(int argc, char *argv[])
{
	t_exec_flags	exec_flags;

	init_flags(&exec_flags);
	capture_flags(argc, argv, &exec_flags);
	check_flags_consistency(&exec_flags);
	execute_cmd(&exec_flags);
	return ;
}

int	main(int argc, char *argv[])
{
	if (argc < 1)
		print_help_msg_exit();
	else if (argc == 1)
		display_dashboard();
	else
		parse_input(argc, argv);
	return (0);
}
