#include "header.h"

char		*g_landing_page_html;

char	**split_and_trim_body(struct mg_str body)
{
	char **list_of_words;
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
	FILE	*f = fopen ("resources/landing-page.html", "rb");

	if (f)
	{
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		g_landing_page_html = malloc (length);
		if (g_landing_page_html)
			fread (g_landing_page_html, 1, length, f);
		fclose (f);
	}
}

static void	fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	if (ev == MG_EV_HTTP_MSG)
	{
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;
		if (mg_http_match_uri(hm, "/"))
			mg_http_reply(c, 200, "Content-Type: text/html; charset=UTF-8\r\n", "{\"api-status\": \"A-OK, Up and Running, WOO-HOO!!!\"}");
		if (mg_http_match_uri(hm, "/home"))
			mg_http_reply(c, 200, "Content-Type: text/html; charset=UTF-8\r\n", g_landing_page_html);
		if (mg_http_match_uri(hm, "/translate"))
		{
			printf("Body: %s\n", hm->body.ptr);
			char **split_body = split_and_trim_body(hm->body);
			t_word_list	*words_list = NULL;
			create_word_list(split_body, &words_list);
			parse_words(&words_list);	//api_call
			char *translation = translate();
			mg_http_reply(c, 200, "Content-Type: text/html; charset=UTF-8\r\n", "{\"Translation\": \"%s\"}", translation);
		}
		else
			mg_http_reply(c, 400, "Content-Type: text/html; charset=UTF-8\r\n", "Bad bad request ヽ(O`皿'O)ﾉ");
	}
}

int	main(int argc, char *argv[]) {
	struct mg_mgr mgr;

	mg_mgr_init(&mgr);	// Init manager
	load_resources();	// load resources do memory
	if (!mg_http_listen(&mgr, "http://localhost:4242", fn, &mgr))	// Setup listener
		return (1);	// error! tratar depois
	while (42)
		mg_mgr_poll(&mgr, 1000);	// Event loop
	mg_mgr_free(&mgr);	// Cleanup
	return 0;
}
