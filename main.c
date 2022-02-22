#include "mongoose.h"
#include "header.h"
#include <stdio.h> // fopen(), fread()

char	*g_landing_page_html;

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

char	*fetch_word(struct mg_str body)
{
	int i;
	static char	*buff = NULL;
	static int	buff_pos = 0;
	char	*word = NULL;

	if (!buff)
	{
		if (!(buff = calloc(sizeof(char), (body.len + 1))))
			return (NULL);
		strlcpy(buff, body.ptr, body.len);
		printf("inicio do buffer: >>%s<<z\n", buff);
	}
	i = -1;
	while (buff[++i + buff_pos])
	{
		if (buff[i + buff_pos] == ' ')
		{
			word = calloc(sizeof(char), i + 1);
			word[i] = '\0';
			strlcpy(word, buff + buff_pos, i + 1);
			buff_pos += i + 1;
			return (word);
		}
		if (buff[i] == '\0')
		{
			buff_pos = 0;
			free(buff);
			buff = NULL;
			break ;
		}
	}
	if (buff[buff_pos])
	{
		word = calloc(sizeof(char), i + 1);
		word[i] = '\0';
		strlcpy(word, buff + buff_pos, i + 1);
	}
	if (buff[i + buff_pos] == '\0')
	{
		buff_pos = 0;
		free(buff);
		buff = NULL;
	}
	return (word);
}

char	**parse_body(struct mg_str body)
{
	char **list_of_words;
	int word_count;

	word_count = count_spaces(body.ptr) + 1;
	// printf("word count: %d\n", word_count);
	list_of_words = malloc(sizeof(*list_of_words) * (word_count + 1));
	list_of_words[word_count] = NULL;
	int i = -1;
	while (++i < word_count)
	{
		list_of_words[i] = fetch_word(body);
		printf("word %d: %s\n", i, list_of_words[i]);
		if (list_of_words[i] == NULL)
			return (NULL);		//deu ruim cancela desaloca memória etc.
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
			char **words = parse_body(hm->body);
			// mg_http_reply(c, 200, "Content-Type: text/html; charset=UTF-8\r\n", "Yr translation is coming! body: %s; word[0]: %s, word[1]: %s, word[2]: %s", hm->body, words[0], words[1], words[2]);
			mg_http_reply(c, 200, "Content-Type: text/html; charset=UTF-8\r\n", "Yr translation is coming! body: %s, word[0]: %s, teste: %s", (hm->body).ptr, words[0], "teste");
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
