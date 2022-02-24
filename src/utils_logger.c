#include "server.h"

void	logger_init(t_logger *logger)
{
	FILE	*log_file = fopen("./logs", "a");

	logger->fd = log_file->_fileno;
	logger->timestamp = NULL;
	logger->method = NULL;
	logger->uri = NULL;
	logger->query = NULL;
	logger->protocol = NULL;
	logger->body = NULL;
	logger->headers = NULL;
	return ;
}

void	logger_free_all(t_logger *logger)
{
	if (logger->timestamp)
		free(logger->timestamp);
	if (logger->method)
		free(logger->method);
	if (logger->uri)
		free(logger->uri);
	if (logger->query)
		free(logger->query);
	if (logger->protocol)
		free(logger->protocol);
	if (logger->body)
		free(logger->body);
	// loop pelos headers
	// if (logger->headers)
	// 	free(logger->headers);
	return ;
}

void	logger_write_log(t_logger *logger)
{
	return ;
}

void	logger_info(string	info_msg, t_logger *logger)
{
	dprintf(logger->fd, "[INFO] %s\n", info_msg);
	return ;
}

void	logger_error(string	err_msg, t_logger *logger)
{
	dprintf(logger->fd, "[ERROR] %s\n", err_msg);
	return ;
}

void	logger_close(t_logger *logger)
{
	logger_free_all(logger);
	close(logger->fd);
	return;
}