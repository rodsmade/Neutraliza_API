#include "server.h"

void	logger_init(void)
{
	FILE	*log_file = fopen("../logs/logs.txt", "a");

	if (!log_file)
		logger_error("Couldn't open logs file");
	g_logger.fd = log_file->_fileno;
	g_logger.transaction_id = 0;
	g_logger.timestamp = NULL;
	return ;
}

void	logger_free_all(void)
{
	if (g_logger.timestamp)
		free(g_logger.timestamp);
	return ;
}

static string get_time(void)
{
  time_t rawtime;
  struct tm * timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  return (asctime(timeinfo));
}

static string get_headers(struct mg_http_message *request)
{
	string	headers_to_string = strdup("");
	int		i = -1;

	while (request->headers[++i].name.ptr)
	// {"header1":"value1"},{"header2":"value2"},...,{"headerN":"valueN"}
	{
		headers_to_string = ft_append_string(headers_to_string, "{\"", 2);
		headers_to_string = ft_append_string(headers_to_string
											, request->headers[i].name.ptr
											, request->headers[i].name.len);
		headers_to_string = ft_append_string(headers_to_string, "\":\"", 3);
		headers_to_string = ft_append_string(headers_to_string
											, request->headers[i].value.ptr
											, request->headers[i].value.len);
		headers_to_string = ft_append_string(headers_to_string, "\"}", 4);
		if (request->headers[i + 1].name.ptr)
			headers_to_string = ft_append_string(headers_to_string, ",", 1);
	}	
	return (headers_to_string);
}

void	logger_log_new_request(struct mg_http_message *request)
{
	string	headers;
	string	timestamp;

	g_logger.transaction_id++;
	g_logger.timestamp = get_time();
	headers = get_headers(request);
	timestamp = ft_strtrim(get_time(), "\n");
	dprintf(g_logger.fd
			, "[{\"log-type\":\"[REQUEST]\",\"log\":[{\"transaction_id\":%ld,\"timestamp\":\"%s\",\"body\":\"%.*s\",\"method\":\"%.*s\",\"protocol\":\"%.*s\",\"query\":\"%.*s\",\"uri\":\"%.*s\",\"headers\":[%s]}]}]\n"
			, g_logger.transaction_id
			, timestamp
			, (int) request->body.len, request->body.ptr
			, (int) request->method.len, request->method.ptr
			, (int) request->proto.len, request->proto.ptr
			, (int) request->query.len, request->query.ptr
			, (int) request->uri.len, request->uri.ptr
			, headers);
	free(headers);
	free(timestamp);
	return ;
}

void	logger_log_response(int status_code, string headers, string body)
{
	dprintf(g_logger.fd
			, "[{\"log-type\":\"[RESPONSE]\",\"log\":[{\"transaction_id\":%ld,\"status_code\":\"%s\",\"response_body\":[%s],\"response_headers\":[%s]}]}]\n"
			, g_logger.transaction_id
			, http_status_to_string(status_code)
			, body
			, headers);
	return ;
}

void	logger_info(string	info_msg)
{
	dprintf(g_logger.fd, "[INFO] %s\n", info_msg);
	return ;
}

void	logger_error(string	err_msg)
{
	dprintf(g_logger.fd, "[ERROR] %s\n", err_msg);
	return ;
}

void	logger_close(void)
{
	logger_free_all();
	close(g_logger.fd);
	return;
}
