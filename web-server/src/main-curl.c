/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2021, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
/* <DESC>
 * Shows how the write callback function can be used to download data into a
 * chunk of memory instead of storing it in a file.
 * </DESC>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>
#include "cJSON.h"

struct MemoryStruct {
	char *memory;
	size_t size;
};

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

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

	struct MemoryStruct chunk;

	chunk.memory = malloc(1);	/* will be grown as needed by the realloc above */
	chunk.size = 0;		/* no data at this point */

	curl_global_init(CURL_GLOBAL_ALL);

	/* init the curl session */
	curl_handle = curl_easy_init();

	/* specify URL to get */
	char palavra[] = "manga";
	curl_easy_setopt(curl_handle, CURLOPT_URL, "https://significado.herokuapp.com/gostoso");

	/* send all data to this function	*/
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	/* we pass our 'chunk' struct to the callback function */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

	/* some servers do not like requests that are made without a user-agent
		 field, so we provide one */
//	 curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	/* get it! */
	res = curl_easy_perform(curl_handle);

	/* check for errors */
	if(res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
						curl_easy_strerror(res));
	}
	else {
		/*
		 * Now, our chunk.memory points to a memory block that is chunk.size
		 * bytes big and contains the remote file.
		 *
		 * Do something nice with it!
		 */
		printf("data received: >>>%s<<<\n", chunk.memory);
		printf("teste1\n");
		cJSON *response_json = cJSON_Parse(chunk.memory);
		printf("teste2\n");
		if (response_json == NULL)
		{
			printf("deu ruim criar o json\n");
			cJSON_Delete(response_json);
			return 0;
		}
		printf("array size: %d\n", cJSON_GetArraySize(response_json));
				printf("teste3\n");
		const cJSON *definition = NULL;
		printf("teste4\n");
		definition = cJSON_GetArrayItem(response_json, 0);
		const cJSON *class_json = NULL;
		class_json = cJSON_GetObjectItemCaseSensitive(definition, "class");
		printf("deu bom??? >%s<\n", class_json->valuestring);
		if (cJSON_IsString(class_json) && (class_json->valuestring != NULL))
			printf("deu bom! buscou a classe, ela existe\n");
		printf("teste6\n");
		if (strncmp(class_json->valuestring, "adjetivo", 8) == 0)
			printf("Achou adjetivo !!! => %s\n", palavra);
		else
			printf("Não achou adjetivo\n");
		printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
	}

	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);

	free(chunk.memory);

	/* we are done with libcurl, so clean it up */
	curl_global_cleanup();

	return 0;
}
