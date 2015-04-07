#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>

size_t write_data_ehentai(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void ehentai(char url_orig[], char name[], char chapter[], char downdir[]){
printf("This is ehentai");
}
