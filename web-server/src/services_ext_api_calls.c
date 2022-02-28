#include "server.h"

static size_t
get_ext_api_response(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	t_memory *mem = (t_memory *) userp;

	char *ptr = realloc(mem->memory, mem->size + realsize + 1);
	if(!ptr) {
		/* out of memory! */
		logger_error("Not enough memory to get dicio-API response! (realloc returned NULL)\n");
		return 0;
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

char	*ext_api_call_dictionary(char *word)
{
	CURL *curl_handle;
	CURLcode res;
	t_memory chunk;

	chunk.memory = malloc(1);
	chunk.size = 0;	

	/* init the curl session */
	curl_global_init(CURL_GLOBAL_ALL);

	curl_handle = curl_easy_init();

	/* specify URL to get */
	char *url = ft_append_string_va(strdup("https://significado.herokuapp.com/"), 1, word);
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);

	/* send all data to this function	*/
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, get_ext_api_response);

	/* we pass our 'chunk' struct to the callback function */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

	/* make external api call */
	res = curl_easy_perform(curl_handle);

	/* check for errors */
	if(res != CURLE_OK) {
		char *error_log = ft_append_string_va(strdup("curl_easy_perform() failed: "), 1, curl_easy_strerror(res));
		logger_error(error_log);
		ft_free_ptr((void *)&error_log);
		curl_easy_cleanup(curl_handle);
		curl_global_cleanup();
		ft_free_ptr((void *)&word);
		free(chunk.memory);
		return (NULL);
	}
	else {
		char* response = strdup(chunk.memory);
		curl_easy_cleanup(curl_handle);
		curl_global_cleanup();
		ft_free_ptr((void *)&url);
		free(chunk.memory);
		return (response);
	}
}
