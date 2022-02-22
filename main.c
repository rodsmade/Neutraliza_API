#include "mongoose.h"

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
//   struct mg_http_serve_opts opts = {.root_dir = "."};   // Serve local dir
  if (ev == MG_EV_HTTP_MSG)
  	// mg_http_serve_dir(c, ev_data, &opts);
	  mg_http_reply(c, 200, NULL, "Hello %s!", "World");
}

int main(int argc, char *argv[]) {
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);                                        // Init manager
//   mg_http_listen(&mgr, "http://localhost:4242", fn, &mgr);  // Setup listener
  if (!mg_http_listen(&mgr, "http://localhost:4242", fn, &mgr))
	return (1);	// error!
  for (;;) mg_mgr_poll(&mgr, 1000);                         // Event loop
  mg_mgr_free(&mgr);                                        // Cleanup
  return 0;
}