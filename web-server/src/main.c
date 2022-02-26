#include "server.h"

string		g_landing_page_html;
t_logger	g_logger;
int			g_EXIT_SIG;

void	signal_handler(int dummy)
{
	(void)dummy;
	g_EXIT_SIG = 1;
}

string	*split_and_trim_body(struct mg_str body)
{
	string *list_of_words;
	int	i = -1;

	list_of_words = ft_split(body.ptr, ' ');
	while (list_of_words[++i])
	{
		list_of_words[i] = ft_strtrim(list_of_words[i], "!.,?");
		printf("word[%i]: %s\n", i, list_of_words[i]);
	}
	return (list_of_words);
}

int	load_resources(void)
{
	long	length;
	FILE	*file = fopen ("resources/landing-page.html", "rb");

	if (file)
	{
		fseek(file, 0, SEEK_END);
		length = ftell (file);
		fseek(file, 0, SEEK_SET);
		g_landing_page_html = malloc(length * sizeof(char));
		if (g_landing_page_html)
			fread(g_landing_page_html, 1, length, file);
		fclose(file);
		return (1);
	}
	else
		printf("Failed to open html\n");
	return (0);
}

static void	handle_http_connection(struct mg_connection *connection, int ev, void *ev_data, void *fn_data)
{
	if (ev == MG_EV_HTTP_MSG)
	{
		struct mg_http_message *request = (struct mg_http_message *) ev_data;
		logger_new_request(request, &g_logger);

		if (mg_http_match_uri(request, "/") && http_match_method(request, GET))
		{
			string response_body = "{\"response\": \"Server Up and Running!!!\"}";
			mg_http_reply(connection
							, OK_200
							, "Content-Type: text/html; charset=UTF-8\r\n"
							, response_body);
			logger_log_response(OK_200
								, "{\"Content-Type\":\"text/html; charset=UTF-8\"}"
								, response_body
								, &g_logger);
		}
		else if (mg_http_match_uri(request, "/v1.0/home") && http_match_method(request, GET))
		{
			string response_body = "{\"response\": \"landing-page.html\"}";
			mg_http_reply(connection
							, OK_200
							, "Content-Type: text/html; charset=UTF-8\r\n"
							, g_landing_page_html);
			logger_log_response(OK_200
								, "{\"Content-Type\":\"text/html; charset=UTF-8\"}"
								, response_body
								, &g_logger);
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
							, OK_200
							, "Content-Type: text/html; charset=UTF-8\r\n"
							, "{\"Translation\": \"%s\"}", translation);
			logger_log_response(OK_200
								, "{\"Content-Type\":\"text/html; charset=UTF-8\"}"
								, translation_json
								, &g_logger);
		}
		else
		{
			string response_body = "{\"response\": \"Bad request, refer to docs (link - soon!).\"}";
			mg_http_reply(connection
							, BAD_REQUEST_400
							, "Content-Type: text/html; charset=UTF-8\r\n"
							, response_body);
			logger_log_response(BAD_REQUEST_400
								, "{\"Content-Type\":\"text/html; charset=UTF-8\"}"
								, response_body
								, &g_logger);
		}
	}
}

int	main(int argc, string argv[])
{
	struct mg_mgr	mgr;

	printf("Starting server . . .\n");

	// initialising structures and loading resources
	mg_mgr_init(&mgr);
	logger_init(&g_logger);
	printf("Initialised structures.\n");

	if (load_resources())
		printf("Loaded resources.\n");
	else
		logger_error("Failed to load resources", &g_logger);

	// Setting up listener (socket)
	if (!mg_http_listen(&mgr, "http://localhost:4242", handle_http_connection, NULL))
	{
		logger_error("Failed to setup listener", &g_logger);
		return (1);
	}

	// Capture ctrl+c signal so that server is closed properly
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);

	printf("Server is up.\n");
	print_grand_opener();

	while (!g_EXIT_SIG)
		mg_mgr_poll(&mgr, 1000);

	// In the event of server being closed by ctrl+c, closing routine
	printf("\n");
	printf("Freeing memory and closing logs fd . . .\n");
	mg_mgr_free(&mgr);
	logger_close(&g_logger);

	printf("Server shut down.\n");

	return (0);
}
