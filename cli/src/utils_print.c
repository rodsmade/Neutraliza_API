#include "neutraliza-cli.h"

void	display_dashboard(void)
{
	printf("printa dash normal\n");
	return ;
}

void	print_help_msg_exit(void)
{
	dprintf(2, "Try 'neutre --help' for more information.\n");
	exit(1);
}

void	print_help_menu(void)
{
	printf("Usage:\n\tneutre [LOG_TYPE] [FORMAT]\t-\tfilters through log file by LOG_TYPE\n\tneutre [OPTION]\t\t\t-\tdisplay general dashboard or list logs\n\n[OPTION]\n\t--dashboard, -d, (no option):\n\t\t\tprint comprehensive dashboard (all endpoints/methods) -- DEFAULT\n\t--help, -h:\n\t\t\tdisplay this help and exit\n\t--all, -a:\n\t\t\tlist all logs -- DEFAULT\n[LOG_TYPE]\n\t--get, -g:\n\t\t\tlist all logs of GET requests\n\t--post, -p:\n\t\t\tlist all logs of POST requests\n\t--info, -i:\n\t\t\tlist all logs of INFO messages\n\t--error, -e:\n\t\tlist all logs of ERROR messages\n[FORMAT]\n\t--mini, -m:\n\t\tdisplay logs in minified version (one log per line) -- DEFAULT\n\t--beauty, -b:\n\t\tdisplay logs º¤ø,¸¸,ø¤º°`°º¤ø, b e a u t i f u l l y ,ø¤°º¤ø,¸¸,ø¤°º¤ø,¸¸\n\nFull documentation available locally via: man man_pages/neutre.1\n");
}
