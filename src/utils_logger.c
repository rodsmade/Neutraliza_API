#include "server.h"

void	logger_init(t_logger *logger)
{
	FILE	*log_file = fopen("./logs", "a");

	logger->fd = log_file->_fileno;
	logger->transaction_id = 0;
	logger->timestamp = NULL;
	logger->method = NULL;
	logger->uri = NULL;
	logger->query = NULL;
	logger->protocol = NULL;
	logger->body = NULL;
	// logger->headers = NULL;
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

static string get_time (void)
{
  time_t rawtime;
  struct tm * timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  return (asctime(timeinfo));
}

void	logger_log_request(struct mg_http_message *request, t_logger *logger)
{
	logger->timestamp = get_time();
	logger->body = strndup(request->body.ptr, request->body.len);
	logger->method = strndup(request->method.ptr, request->method.len);
	logger->protocol = strndup(request->proto.ptr, request->proto.len);
	logger->query = strndup(request->query.ptr, request->query.len);
	logger->uri = strndup(request->uri.ptr, request->uri.len);
	int	i = -1;	

	return ;
}

// void	logger_log_response(int status_code, string headers, string body, t_logger *logger)
void	logger_log_response(t_logger *logger)
{
	// monta o JSON
	cJSON *log_JSON	= cJSON_CreateArray();
	cJSON *log_obj_JSON = cJSON_CreateObject();
	cJSON_AddItemToArray(log_JSON, log_obj_JSON);
	cJSON_AddStringToObject(log_obj_JSON, "log-type", "[RESPONSE]");

	cJSON *log_arr_JSON = cJSON_AddArrayToObject(log_obj_JSON, "log");

	cJSON *log_obj = cJSON_CreateObject();
	cJSON_AddItemToArray(log_arr_JSON, log_obj);

	cJSON_AddStringToObject(log_obj, "transaction_id", "4729847");
	cJSON_AddStringToObject(log_obj, "status_code", "200");
	cJSON_AddStringToObject(log_obj, "response_body", "body");

	cJSON *response_headers_arr = cJSON_CreateArray();
	cJSON_AddItemToObject(log_obj, "response_headers", response_headers_arr);
	
	// monta headers da resposta
	cJSON *header_1_obj_JSON = cJSON_CreateObject();
	cJSON_AddStringToObject(header_1_obj_JSON, "header1", "value1");
	cJSON_AddItemToArray(response_headers_arr, header_1_obj_JSON);
	cJSON *header_2_obj_JSON = cJSON_CreateObject();
	cJSON_AddStringToObject(header_2_obj_JSON, "header2", "value2");
	cJSON_AddItemToArray(response_headers_arr, header_2_obj_JSON);

	dprintf(logger->fd, "%s\n", cJSON_PrintUnformatted(log_JSON));
	return ;
}

string	logger_request_JSON_to_string(t_logger *logger)
{
	string	request_JSON_to_string;

	// monta as parada doida

	return (request_JSON_to_string);
}

void	logger_write_request_log(t_logger *logger)
{
	dprintf(logger->fd
			, "[{\"log-type\": \"[REQUEST]\",\"log\":%s}]"
			, logger_request_JSON_to_string(logger));
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