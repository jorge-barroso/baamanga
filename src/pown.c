#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>

size_t write_data_pown(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void pown(char url_orig[], char name[], char downdir[]){
printf("Give a name to the pown: ");
scanf("%49s", name);
}
