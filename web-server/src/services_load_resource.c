#include "server.h"

string	load_resource(string resource_path)
{
	string	resource;
	long	length;
	FILE	*file = fopen (resource_path, "rb");

	if (file)
	{
		fseek(file, 0, SEEK_END);
		length = ftell (file);
		fseek(file, 0, SEEK_SET);
		resource = malloc(length * sizeof(char));
		if (resource)
			fread(resource, 1, length, file);
		fclose(file);
		return (resource);
	}
	else
	{
		char *log = strdup("");
		log = ft_append_string("Failed to load resource ", resource_path, strlen(resource_path));
		logger_error(log);
		free(log);
	}
	return (NULL);
}