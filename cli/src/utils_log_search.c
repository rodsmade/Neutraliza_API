#include "neutraliza-cli.h"

int	match_entry_by_str(char *line, char *log_type, char *uri, char *method)
// devolve 1 se bate tds os critérios, 0 c.c.
{
	char	*arg;

	if (!log_type && !uri && !method)
		return (0);
	if (log_type && !strstr(line, log_type))
		return (0);
	if (uri && !strstr(line, uri))
		return (0);
	if (method && !strstr(line, method))
		return (0);
	return (1);
}

int count_logs(char *log_type, char *uri, char *method)
{
	char	*file_name = "../logs/logs.txt";
	FILE	*fp;
	char	*line;
	int		count_entries = 0;

	fp = fopen(file_name, "r");
	
	while((line = get_next_line(fp->_fileno)) != NULL)
	{
		count_entries += match_entry_by_str(line, log_type, uri, method);
		free(line);
	}
	fclose(fp);
	return (count_entries);
}
