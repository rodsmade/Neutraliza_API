#include "server.h"

void	route_request_to_endpoint(struct mg_connection *connection, struct mg_http_message *request)
{
	if (mg_http_match_uri(request, "/") && http_match_method(request, GET))
	{
		string response_body = "{\"response\": \"Server Up and Running!!!\"}";
		mg_http_reply(connection
						, http_status_to_int(OK_200)
						, RESPONSE_HEADER
						, response_body);
		logger_log_response(OK_200
							, RESPONSE_HEADER_JSON
							, response_body);
	}
	else if (mg_http_match_uri(request, "/v1.0/home") && http_match_method(request, GET))
	{
		// implement: string load_resource(landing-page.html)
		string resource = load_resource("resources/landing-page.html");
		string response_body = "{\"response\": \"landing-page.html\"}";
		mg_http_reply(connection
						, http_status_to_int(OK_200)
						, RESPONSE_HEADER
						, resource);
		logger_log_response(OK_200
							, RESPONSE_HEADER_JSON
							, response_body);
	}
	else if (mg_http_match_uri(request, "/v1.0/translation") && http_match_method(request, POST))
	{
		string *split_body = split_and_trim_body(request->body);
		t_word_list	*words_list = NULL;
		create_word_list(split_body, &words_list);
		parse_words(&words_list);	//api_call
		string translation = translate();
		string translation_json = strdup("{\"translation\":\"");
		translation_json = append_string(translation_json, translation, strlen(translation));
		translation_json = append_string(translation_json, "\"}", 2);
		mg_http_reply(connection
						, http_status_to_int(OK_200)
						, RESPONSE_HEADER
						, "{\"Translation\": \"%s\"}", translation);
		logger_log_response(OK_200
							, RESPONSE_HEADER_JSON
							, translation_json);
	}
	else
	{
		string response_body = "{\"response\": \"Bad request, refer to docs (link - soon!).\"}";
		mg_http_reply(connection
						, http_status_to_int(BAD_REQUEST_400)
						, RESPONSE_HEADER
						, response_body);
		logger_log_response(BAD_REQUEST_400
							, RESPONSE_HEADER_JSON
							, response_body);
	}
}