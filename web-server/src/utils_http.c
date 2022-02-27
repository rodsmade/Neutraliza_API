#include "server.h"

int	http_match_method(struct mg_http_message *request, int method)
{
	if (strncmp(request->method.ptr
				, http_method_to_string(method)
				, request->method.len) == 0)
		return (1);
	else
		return (0);
}

string	http_method_to_string(enum e_http_method method)
{
	string strings[] = {"GET", "POST", "PUT", "PATCH", "DELETE"};

	return (strings[method]);
}

string	http_status_to_string(enum e_http_method method)
{
	string strings[] = {"100_CONTINUE"
						, "200_OK"
						, "400_BAD_REQUEST"
						, "404_NOT_FOUND"
						, "418_TEAPOT"
						, "500_SERVER_ERROR"};

	return (strings[method]);
}

int	http_status_to_int(enum e_http_method method)
{
	int statuses[] = {100
					, 200
					, 400
					, 404
					, 418
					, 500};

	return (statuses[method]);
}

string	class_to_string(enum e_class class)
{
	string strings[] = {"none"
						, "adjective"
						, "adverb"
						, "article"
						, "conjunction"
						, "interjection"
						, "numeral"
						, "preposition"
						, "pronoun"
						, "noun"
						, "verb"};

	return (strings[class]);
}
