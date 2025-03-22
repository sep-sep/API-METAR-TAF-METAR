#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>



#define BUFFER_SIZE 8192

//stocke la réponse HTTP
struct ResponseData {
    char data[BUFFER_SIZE];
};

//  à travailler : callback pour écrire la réponse dans un buffer
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t total_size = size * nmemb;
    struct ResponseData *resp = (struct ResponseData *)userdata;
    
    if (strlen(resp->data) + total_size < BUFFER_SIZE - 1) {
        strncat(resp->data, (char *)ptr, total_size);
    }
    return total_size;
}

// Fonction pour récupérer les données METAR ou TAF
void fetch_weather_data(const char *url) {
    CURL *curl;
    CURLcode res;
    struct ResponseData response = {0};

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "Erreur CURL : %s\n", curl_easy_strerror(res));
        } else {
            printf("%s :\n\n\n", response.data);
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

int main(int argc, char *argv[]) {
printf("📡 Récupération du METAR et du TAF en cours\n\n");
	//verification argument 
	if (argc < 3){
		printf("Syntaxe : %s <ORIG> <DEST>\n", argv[0]);
		return EXIT_FAILURE; 
}

char virg[] = ",";
char format[12] = "&format=raw";
char METAR_URL[256] = "https://aviationweather.gov/api/data/taf?ids=";
strcat(METAR_URL, argv[1]);
strcat(METAR_URL, virg);
strcat(METAR_URL, argv[2]);
strcat(METAR_URL, format);

char TAF_URL[256] = "https://aviationweather.gov/api/data/metar?ids=";
strcat(TAF_URL, argv[1]);
strcat(TAF_URL, virg);
strcat(TAF_URL, argv[2]);
strcat(TAF_URL, format);

printf("current url : %s\n", METAR_URL);
printf("current url : %s\n\n\n", TAF_URL);


	
    fetch_weather_data(METAR_URL);
    fetch_weather_data(TAF_URL);

    return EXIT_SUCCESS;
}

  
