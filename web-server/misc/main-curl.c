#include "server.h"

static size_t	get_ext_api_response(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  t_memory *mem = (t_memory *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) {
	/* out of memory! */
	printf("not enough memory (realloc returned NULL)\n");
	return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return (realsize);
}

void	init_memory_chunk(t_memory *chunk)
{
	chunk->memory = malloc(1); 
	chunk->size = 0;
}

char	*get_definition(char *word)
{
	CURL *curl_handle = NULL;
	CURLcode res_code;
	t_memory chunk;

	// init variables
	init_memory_chunk(&chunk);
	curl_global_init(CURL_GLOBAL_ALL);
	curl_handle = curl_easy_init();

	// set options for the curl call
	char *url = ft_append_str_va(strdup("https://significado.herokuapp.com/"), 1, word);
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, get_ext_api_response);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

	// perform api call
	res_code = curl_easy_perform(curl_handle);

	// checks if call went ok
	if(res_code != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res_code));
		curl_easy_cleanup(curl_handle);
		curl_global_cleanup();
		ft_free_ptr((void *)&url);
		ft_free_ptr((void *)&chunk.memory);
		return (NULL);
	}

	char *response_json = strdup(chunk.memory);
	// reset libcurl and clean up and free allocated mem
	curl_easy_cleanup(curl_handle);
	curl_global_cleanup();
	ft_free_ptr((void *)&url);
	ft_free_ptr((void *)&chunk.memory);
	return (response_json);
}

int main()
{
	char *definition;
	//////////////////////////////////
	printf("\n");
	definition = get_definition("livro");
	printf("Definition: %s\n", definition);
	ft_free_ptr((void *)&definition);
	printf("\n");

	//////////////////////////////////
	printf("\n");
	definition = get_definition("livro");
	printf("Definition: %s\n", get_definition("banana"));
	ft_free_ptr((void *)&definition);
	printf("\n");

	return 0;
}