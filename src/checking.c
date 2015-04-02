#include <stdio.h>
#include <string.h>

char checking (char url_check[]){
char check = "y";
char check1[5], domain[20];

strcpy(check1, url_check);
strtok(check1, ":");
if (strcmp(check1, "http") == 0 || strcmp(check1, "https") == 0);
	strcpy(domain, strtok(NULL, "/"));
	
return check;
return domain;
return 0;
}
