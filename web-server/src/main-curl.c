#include "server.h"

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	t_memory *mem = (t_memory *) userp;

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

	return realsize;
}

int main(void)
{
	CURL *curl_handle;
	CURLcode res;

	t_memory chunk;

	chunk.memory = malloc(1);	/* will be grown as needed by the realloc above */
	chunk.size = 0;		/* no data at this point */

	curl_global_init(CURL_GLOBAL_ALL);

	/* init the curl session */
	curl_handle = curl_easy_init();

	/* specify URL to get */
	char palavra[] = "dado";
	char url[] = "https://significado.herokuapp.com/dado";
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);

	/* send all data to this function	*/
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	/* we pass our 'chunk' struct to the callback function */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

	/* get it! */
	res = curl_easy_perform(curl_handle);

	/* check for errors */
	if(res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
						curl_easy_strerror(res));
	}
	else {
		cJSON *response_json = cJSON_Parse(chunk.memory);
		if (response_json == NULL)
		{
			printf("deu ruim criar o json\n");
			cJSON_Delete(response_json);
			return 0;
		}
		printf("\n%s\n", cJSON_Print(response_json));
		// me dá a quantidade de retorno de itens da entrada!
		printf("array size: %d\n", cJSON_GetArraySize(response_json));


		const cJSON *definition = NULL;
		definition = response_json->child;
		while (definition)
		{
			const cJSON *class_json = NULL;

			class_json = cJSON_GetObjectItemCaseSensitive(definition, "class");
			if (cJSON_IsString(class_json) && (class_json->valuestring != NULL))
			{
				if (strncmp(class_json->valuestring, "adjetivo", 8) == 0)
					printf("Achou adjetivo !!!\n");
				else
					printf("Não achou adjetivo\n");
			}
			definition = definition->next;
		}
		
		printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
	}

	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);

	free(chunk.memory);

	/* we are done with libcurl, so clean it up */
	curl_global_cleanup();

	return 0;
}
