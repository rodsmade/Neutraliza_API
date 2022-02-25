#include "neutraliza-cli.h"

void	print_help_menu(void)
{
	dprintf(2, "Try 'neutre --help' for more information.");
}

void	evaluate_flags(char *argv[])
{
	if (argv[1][0] != '-')
		print_help_menu();
}

int	main(int argc, char *argv[])
{
	if (argc == 1)
		run_default();
	else
		evaluate_flags(argv);
}