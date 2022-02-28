#include "neutraliza-cli.h"

void	print_help_msg_exit(void)
{
	dprintf(2, "Try 'neutre --help' for more information.\n");
	exit(1);
}

void	print_help_menu(void)
{
	printf("Usage:\n\tneutre [LOG_TYPE] [FORMAT]\t-\tfilters through log file by LOG_TYPE\n\tneutre [OPTION]\t\t\t-\tdisplay general dashboard or list logs\n\n[OPTION]\n\t--dashboard, -d, (no option):\n\t\tprint comprehensive dashboard (all endpoints/methods) -- DEFAULT\n\t--help, -h:\n\t\tdisplay this help and exit\n\t--list, -l:\n\t\tlist logs -- all by DEFAULT\n[LOG_TYPE]\n\t--all, -a:\n\t\tlist all logs -- DEFAULT\n\t--get, -g:\n\t\tlist all logs of GET requests\n\t--post, -p:\n\t\tlist all logs of POST requests\n\t--info, -i:\n\t\tlist all logs of INFO messages\n\t--error, -e:\n\t\tlist all logs of ERROR messages\n[FORMAT]\n\t--mini, -m:\n\t\tdisplay logs in minified version (one log per line) -- DEFAULT\n\t--beauty, -b:\n\t\tdisplay logs º¤ø,¸¸,ø¤º°`°º¤ø, b e a u t i f u l l y ,ø¤°º¤ø,¸¸,ø¤°º¤ø,¸¸\n\nFull documentation available locally via: man man_pages/neutre.1\n");
}

static void	printl_dash(void)
{
	printf("-------------------------------------------------------\n");
}

static void	printl_dot_dash(void)
{
	printf(".-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.\n");
}

static void	printl_dot(void)
{
	printf(".                                                     .\n");
}

static void	print_header_dashboard(void)
{
	printl_dot_dash();
	printl_dot();
	printf(".                 API DASHBOARD                       .\n");
	printl_dot();
}

static void	printl_endpoint_digest(t_endpoint endpoint)
{
	if (endpoint.tot_reqs >= 0 && endpoint.tot_reqs <= 99999)
		printf("- %d\t\t| %s\t\t| %s\n", endpoint.tot_reqs
											, endpoint.method
											, endpoint.uri);
	else
		printf("- %d\t| %s\t\t| %s\n", endpoint.tot_reqs
											, endpoint.method
											, endpoint.uri);
	return;
}

void	display_dashboard(void)
{
	t_endpoint	endpoints[3];
	int			reqs_per_endpoint[3];
	int			i = -1;
	char	*uri_json;
	char	*method_json;

	// gather endpoints data
	endpoints[0] = (t_endpoint){ .uri = "/", .method = "GET"};
	endpoints[1] = (t_endpoint){ .uri = "/v1.0/home", .method = "GET"};
	endpoints[2] = (t_endpoint){ .uri = "/v1.0/translation", .method = "POST"};
	while (++i < 3)
	{
		uri_json = strdup("");
		uri_json = append_n_strs(uri_json, 3, "\"uri\":\"", endpoints[i].uri, "\"");
		method_json = strdup("");
		method_json = append_n_strs(method_json, 3, "\"method\":\"", endpoints[i].method, "\"");
		endpoints[i].tot_reqs = count_logs("\"log-type\":\"[REQUEST]\""
						, uri_json
						, method_json);
		free(uri_json);
		free(method_json);
	}

	// print dashboard
	print_header_dashboard();
	printl_dash();
	printf("| Requests\t| HTTP Method\t| Endpoint   \n");
	printl_dash();
	i = -1;
	while (++i < 3)
		printl_endpoint_digest(endpoints[i]);
	printl_dash();
	printl_dot();
	printl_dot();
	printl_dash();
	printf("| Server Total:                                       .\n");
	printl_dash();
	printf("- Total requests\t:\t%d\n", count_logs("\"log-type\":\"[REQUEST]\"", NULL, NULL));
	printf("- Bad requests\t\t:\t%d\n", count_logs("\"log-type\":\"[RESPONSE]\"", "\"status_code\":\"400_BAD_REQUEST\"", NULL));
	printf("- Errors\t\t:\t%d\n", count_logs("\"log-type\":\"[ERROR]\"", NULL, NULL));
	printf("- Info\t\t\t:\t%d\n", count_logs("\"log-type\":\"[INFO]\"", NULL, NULL));
	printl_dash();
	printl_dot();
	printl_dot_dash();
	return ;
}
