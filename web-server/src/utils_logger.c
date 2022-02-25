#include "server.h"

void	logger_init(t_logger *logger)
{
	FILE	*log_file = fopen("./logs.txt", "a");

	logger->fd = log_file->_fileno;
	logger->transaction_id = 0;
	logger->timestamp = NULL;
	return ;
}

void	logger_free_all(t_logger *logger)
{
	if (logger->timestamp)
		free(logger->timestamp);
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

/**
 * In order for this function to work properly with NO LEAKS, original_str
 * HAS to be malloced initially. It WILL be freed. So it's reasonable to call
 * my_string = append_string(my_string, "something");
**/
string	append_string(string original_str, const char *appendage, size_t n)
{
	string	new_str;
	int	orig_len = 0;
	int	i;

	orig_len = strlen(original_str);
	new_str = realloc(original_str, (orig_len + n + 1) * sizeof(char));
	new_str[orig_len + n] = '\0';
	i = -1;
	while (++i < n)
		new_str[orig_len + i] = appendage[i];
	return (new_str);
}

static string get_headers(struct mg_http_message *request)
{
	string	headers_to_string = strdup("");
	int		i = -1;

	while (request->headers[++i].name.ptr)
	// {"header1":"value1"},{"header2":"value2"},...,{"headerN":"valueN"}
	{
		headers_to_string = append_string(headers_to_string, "{\"", 2);
		headers_to_string = append_string(headers_to_string
											, request->headers[i].name.ptr
											, request->headers[i].name.len);
		headers_to_string = append_string(headers_to_string, "\":\"", 3);
		headers_to_string = append_string(headers_to_string
											, request->headers[i].value.ptr
											, request->headers[i].value.len);
		headers_to_string = append_string(headers_to_string, "\"}", 4);
		if (request->headers[i + 1].name.ptr)
			headers_to_string = append_string(headers_to_string, ",", 1);
	}	
	return (headers_to_string);
}

void	logger_new_request(struct mg_http_message *request, t_logger *logger)
{
	string	headers;
	string	timestamp;

	logger->transaction_id++;
	logger->timestamp = get_time();
	headers = get_headers(request);
	timestamp = ft_strtrim(get_time(), "\n");
	dprintf(logger->fd
			, "[{\"log-type\":\"[REQUEST]\",\"log\":[{\"transaction_id\":%ld,\"timestamp\":\"%s\",\"body\":\"%.*s\",\"method\":\"%.*s\",\"protocol\":\"%.*s\",\"query\":\"%.*s\",\"uri\":\"%.*s\",\"headers\":[%s]}]}]\n"
			, logger->transaction_id
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

void	logger_log_response(int status_code, string headers, string body, t_logger *logger)
{
	dprintf(logger->fd
			, "[{\"log-type\":\"[RESPONSE]\",\"log\":[{\"transaction_id\":%ld,\"status_code\":\"%s\",\"response_body\":[%s],\"response_headers\":[%s]}]}]\n"
			, logger->transaction_id
			, http_status_to_string(status_code)
			, body
			, headers);
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
