#include "cJSON.h"
#include <stdio.h>

//NOTE: Returns a heap allocated string, you are required to free it after use.
char *create_monitor_with_helpers(void)
{
	const unsigned int resolution_numbers[3][2] = {
		{1280, 720},
		{1920, 1080},
		{3840, 2160}
	};
	char *string = NULL;		//RETORNO DA FUNÇÃO
	cJSON *resolutions = NULL;	// é o segundo atributo do json dps do nome, wtf man
	size_t index = 0;

	cJSON *monitor = cJSON_CreateObject();	// ñ sei ?????????

	if (cJSON_AddStringToObject(monitor, "name", "Awesome 4K") == NULL)
	//				é tipo		objeto;	key;	  value (em string))
	{
		goto end;
	}

	resolutions = cJSON_AddArrayToObject(monitor, "resolutions");
	if (resolutions == NULL)
	{
		goto end;
	}

	for (index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int))); ++index)
	{
		cJSON *resolution = cJSON_CreateObject();

		if (cJSON_AddNumberToObject(resolution, "width", resolution_numbers[index][0]) == NULL)
		{
			goto end;
		}

		if (cJSON_AddNumberToObject(resolution, "height", resolution_numbers[index][1]) == NULL)
		{
			goto end;
		}

		cJSON_AddItemToArray(resolutions, resolution);
	}

	string = cJSON_Print(monitor);	//TRANSFORMA O STRUCT/JSON EM UM STRING/JSON
	if (string == NULL)
	{
		fprintf(stderr, "Failed to print monitor.\n");
	}

end:
	cJSON_Delete(monitor);
	return string;
}

/* return 1 if the monitor supports full hd, 0 otherwise */
int supports_full_hd(const char * const monitor)	// RECEBE O STRING/JSON DE ENTRADA
{
	const cJSON *resolution = NULL;
	const cJSON *resolutions = NULL;
	const cJSON *name = NULL;
	int status = 0;

	cJSON *monitor_json = cJSON_Parse(monitor);	// JOGOU O STRING/JSON PRA STRUCT/JSON
	if (monitor_json == NULL)
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
		{
			fprintf(stderr, "Error before: %s\n", error_ptr);
		}
		status = 0;
		cJSON_Delete(monitor_json);
	}

	name = cJSON_GetObjectItemCaseSensitive(monitor_json, "name"); // DEVOLVE UM STRUCT/JSON DO CAMPO name
	if (cJSON_IsString(name) && (name->valuestring != NULL))
	{
		printf("Checking monitor \"%s\"\n", name->valuestring);
	}

	resolutions = cJSON_GetObjectItemCaseSensitive(monitor_json, "resolutions");	// DEVOLVE UM STRUCT/JSON DO CAMPO resolutions - que por acaso é um array !!!!!!!!!!!!
	cJSON_ArrayForEach(resolution, resolutions)
	{
		cJSON *width = cJSON_GetObjectItemCaseSensitive(resolution, "width");	// PESCOU O STRUCT/JSON
		cJSON *height = cJSON_GetObjectItemCaseSensitive(resolution, "height");	// PESCOU O STRUCT/JSON

		if (!cJSON_IsNumber(width) || !cJSON_IsNumber(height))
		{
			status = 0;
			goto end;
		}

		if ((width->valuedouble == 1920) && (height->valuedouble == 1080))
		{
			status = 1;
			goto end;
		}
	}

end:
	cJSON_Delete(monitor_json);
	return status;
}

void main()
{
	printf("%s\n", create_monitor_with_helpers());
	return ;
}
