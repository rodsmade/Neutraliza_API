#include "server.h"

string		g_landing_page_html;
t_logger	g_logger;
int			g_EXIT_SIG;

void	catch_sigint(void)
{
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

void	load_resources(void)
{
	long	length;
	FILE	*file = fopen ("resources/landing-page.html", "rb");

	if (file)
	{
		fseek(file, 0, SEEK_END);
		length = ftell (file);
		fseek(file, 0, SEEK_SET);
		g_landing_page_html = malloc(length);	// lembrar de dar free
		if (g_landing_page_html)
			fread (g_landing_page_html, 1, length, file);
		fclose(file);
	}
	else
		logger_error("Failed to open html", &g_logger);
	return ;
}

static void	fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	if (ev == MG_EV_HTTP_MSG)
	{
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;
		// printf("\n\n ESMIRILHANDO O mg_http_message:\n");
	 	// printf("-- method: >>%s<<\n", hm->method.ptr);
	 	// printf("-- uri: >>%s<<\n", hm->uri.ptr);
	 	// printf("-- query: >>%s<<\n", hm->query.ptr);
	 	// printf("-- proto: >>%s<<\n", hm->proto.ptr);
	 	// printf("-- body: >>%s<<\n", hm->body.ptr);
	 	// printf("-- head: >>%s<<\n", hm->head.ptr);
	 	// printf("-- chunk: >>%s<<\n", hm->chunk.ptr);
	 	// printf("-- message: >>%s<<\n", hm->message.ptr);
		// printf("-- header[%i]: {\"%s\": \"%s\"\n", 0, hm->headers[0].name.ptr, hm->headers[0].value.ptr);
		// printf("-- header[%i]: {\"%s\": \"%s\"\n", 1, hm->headers[1].name.ptr, hm->headers[1].value.ptr);
		// printf("-- header[%i]: {\"%s\": \"%s\"\n", 2, hm->headers[2].name.ptr, hm->headers[2].value.ptr);
		// printf("-- header[%i]: {\"%s\": \"%s\"\n", 3, hm->headers[3].name.ptr, hm->headers[3].value.ptr);
		// printf("-- header[%i]: {\"%s\": \"%s\"\n", 4, hm->headers[4].name.ptr, hm->headers[4].value.ptr);
		// printf("-- header[%i]: {\"%s\": \"%s\"\n", 5, hm->headers[5].name.ptr, hm->headers[5].value.ptr);
		// printf("-- header[%i]: {\"%s\": \"%s\"\n", 6, hm->headers[6].name.ptr, hm->headers[6].value.ptr);
		// printf("-- header[%i]: {\"%s\": \"%s\"\n", 7, hm->headers[7].name.ptr, hm->headers[7].value.ptr);
		// printf("-- header[%i]: {\"%s\": \"%s\"\n", 8, hm->headers[8].name.ptr, hm->headers[8].value.ptr);
		// printf("-- header[%i]: {\"%s\": \"%s\"\n", 9, hm->headers[9].name.ptr, hm->headers[9].value.ptr);
		if (mg_http_match_uri(hm, "/"))
			mg_http_reply(c, 200, "Content-Type: text/html; charset=UTF-8\r\n", "{\"api-status\": \"A-OK, Up and Running, WOO-HOO!!!\"}");
		if (mg_http_match_uri(hm, "/home"))
			mg_http_reply(c, 200, "Content-Type: text/html; charset=UTF-8\r\n", g_landing_page_html);
		if (mg_http_match_uri(hm, "/translate"))
		{
			printf("Body: %s\n", hm->body.ptr);
			string *split_body = split_and_trim_body(hm->body);
			t_word_list	*words_list = NULL;
			create_word_list(split_body, &words_list);
			parse_words(&words_list);	//api_call
			string translation = translate();
			mg_http_reply(c, 200, "Content-Type: text/html; charset=UTF-8\r\n", "{\"Translation\": \"%s\"}", translation);
		}
		else
			mg_http_reply(c, 400, "Content-Type: text/html; charset=UTF-8\r\n", "Bad bad request ヽ(O`皿'O)ﾉ");
	}
}

int	main(int argc, string argv[]) {
	struct mg_mgr	mgr;

	mg_mgr_init(&mgr);	// Init manager
	logger_init(&g_logger);
	load_resources();	// load resources to memory
	signal(SIGINT, catch_sigint);
	if (!mg_http_listen(&mgr, "http://localhost:4242", fn, &mgr))
	{
		logger_error("Failed to setup listener", &g_logger);
		return (1);
	}
	while (!g_EXIT_SIG)
		mg_mgr_poll(&mgr, 1000);	// Event loop
	mg_mgr_free(&mgr);	// Cleanup
	logger_close(&g_logger);
	return 0;
}
