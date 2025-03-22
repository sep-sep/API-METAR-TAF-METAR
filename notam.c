#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    FILE *file = (FILE *)stream;
    return fwrite(ptr, size, nmemb, file);
}

int main(int argc, char *argv[]) {
    printf("📡 Récupération du NOTAM en cours\n\n");
    
    if (argc < 2) {
        printf("Syntaxe : %s <ORIG>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen("page.html", "w");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return EXIT_FAILURE;
    }

    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.notams.faa.gov/dinsQueryWeb/queryRetrievalMapAction.do");
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        char postData[256] = "retrieveLocId=";
        strcat(postData, argv[1]);
        strcat(postData, "&actionType=notamRetrievalByICAOs");
        
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Erreur : %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }
    
    fclose(file);
    return 0;
}
