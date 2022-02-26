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

// int	main(int argc, char *argv[])
// {
// 	if (argc < 1)
// 		print_help_msg_exit();
// 	else if (argc == 1)
// 		display_dashboard();
// 	else
// 		parse_input(argc, argv);
// 	return (0);
// }

#include <stdio.h>	// FILE, fopen()
#include <stdio.h> // printf()
#include <stdlib.h> // free()

char	*g_file_name = "/home/rods/documents/git/42labs-selection-process-v2-rodsmade/logs/logs.txt";
FILE	*g_fp;

char	*get_next_line(int fd);

int main()
/**
*	- Function main() opens a file in a file descriptor (fd / _fileno).
*	- This file contains text meant to be read one line at a time by means
*	of function get_next_line().
*	- Each call must return a string of chars ended tied up with a '\n', so long
*	as there is one. Empty lines are returned all the same (one single '\n' per call).
*	- main() proceeds to print the resulting line read by get_next_line(),
*	looping throughout the file.
*	- Once EOF is reached, get_next_line() returns NULL and stops execution;
*	main() closes the file, and the program comes to a halt.
**/
{
	char	*linha;
	int		i = 0;

	g_fp = fopen(g_file_name, "r");
	
	while((linha = get_next_line(g_fp->_fileno)) != NULL)
	{
		printf("Line %i >>> %s", i++, linha);
		free(linha);
	}
	
	fclose(g_fp);
	return (0);
}
