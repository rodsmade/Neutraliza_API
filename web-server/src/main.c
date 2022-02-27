#include "server.h"

t_logger	g_logger;
int			g_EXIT_SIG;

void	signal_handler(int dummy)
{
	(void)dummy;
	g_EXIT_SIG = 1;
}

static void	handle_http_connection(struct mg_connection *connection, int ev, void *ev_data, void *fn_data __attribute__((unused)))
{
	if (ev == MG_EV_HTTP_MSG)
	{
		struct mg_http_message *request = (struct mg_http_message *) ev_data;
		logger_new_request(request);

		// route to endpoints
		route_request_to_endpoint(connection, request);
	}
}

int	main(void)
{
	struct mg_mgr	mg_mgr;

	printf("Starting server . . .\n");

	// initialising structures and loading resources
	mg_mgr_init(&mg_mgr);
	logger_init();
	printf("Initialised structures.\n");

	// Setting up listener (socket)
	if (!mg_http_listen(&mg_mgr, "http://localhost:4242", handle_http_connection, NULL))
	{
		logger_error("Failed to setup listener");
		return (1);
	}

	// Capture ctrl+c signal so that server is closed properly
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);

	printf("Server is up.\n");
	print_grand_opener();

	// Set server up polling every 1000 ms.
	while (!g_EXIT_SIG)
		mg_mgr_poll(&mg_mgr, 1000);

	// In the event of server being closed by ctrl+c, closing routine
	printf("\n");
	printf("Freeing memory and closing logs fd . . .\n");
	mg_mgr_free(&mg_mgr);
	logger_close();

	printf("Server shut down.\n");

	return (0);
}
