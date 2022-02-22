#include "header.h"

char	*g_landing_page_html;
// t_word	*g_words_list;

int	count_spaces(const char *body_str)
{
	int	i, count;

	count = 0;
	i = -1;
	while (body_str[++i])
		if (body_str[i] == ' ')
			count++;
	if (body_str[i - 1] == ' ')
		count--;
	return (count);
}

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

static void	fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	if (ev == MG_EV_HTTP_MSG)
	{
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;
		if (mg_http_match_uri(hm, "/"))
			mg_http_reply(c, 200, "Content-Type: text/html; charset=UTF-8\r\n", g_landing_page_html);
		if (mg_http_match_uri(hm, "/translate"))
		{
			char **words_list = split_and_trim_body(hm->body);
			// g_words_list = parse_words(words_list);
			mg_http_reply(c, 200, "Content-Type: text/html; charset=UTF-8\r\n", "Yr translation is coming!\n\n\nbody: %s\n\n\nword[0]: %s, %s", (hm->body).ptr, words_list[0], "teste");
		}
		else
			mg_http_reply(c, 400, "Content-Type: text/html; charset=UTF-8\r\n", "Bad bad URI :(");
	}
}

void	load_landing_page(void)
{
	long	length;
	FILE	*f = fopen ("landing-page.html", "rb");

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

int	main(int argc, char *argv[]) {
	struct mg_mgr mgr;
	mg_mgr_init(&mgr);										// Init manager
	load_landing_page();
//	mg_http_listen(&mgr, "http://localhost:4242", fn, &mgr);	// Setup listener
	if (!mg_http_listen(&mgr, "http://localhost:4242", fn, &mgr))
	return (1);	// error!
	for (;;) mg_mgr_poll(&mgr, 1000);						// Event loop
	mg_mgr_free(&mgr);										// Cleanup
	return 0;
}
