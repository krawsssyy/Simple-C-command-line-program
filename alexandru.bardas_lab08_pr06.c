#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

int inVector(int* indices, int length, int value) {
		int i;
		for(i = 0; i < length; i++)
			if(indices[i] == value)
				return 1;
		return 0;
}

int main(int argc, char* argv[]) {
	FILE* fd;
	if(argc != 3) {
		printf("Acest program sterge aparitiile unui cuvant dintr-un fisier dat.\n");
		printf("Folosire: %s %s %s", argv[0], "cuvant", "numeFisier");
	}
	fd=fopen(argv[1], "r");
	int fileArg = 1;
	char* word;
	if(fd == NULL) {
		fd = fopen(argv[2], "r");
		fileArg = 2;	
		if(fd == NULL) {
			printf("Niciunul dintre argumentele date nu pot fi deschide ca fisiere");
			return 1;
		}
		else 
			word = argv[1];
	}
	else
		word = argv[2];
	char* buf = malloc(BUFFER_SIZE);
	int i = 0;
	char f = '0';
	while(f != EOF) {
		f = fgetc(fd);
		buf[i] = f;
		i++;
	}
	buf[i] = '\0';
	fclose(fd);
	fd = fopen(argv[fileArg], "w");
	if(fd == NULL){
		printf("Nu se poate scrie in fisierul dat ca parametru!\n");
		free(buf);
		return 1;
	}
	fseek(fd, 0, SEEK_SET);
	int wordLength = strlen(word);
	int j;
	int count = 0;
	int* indices = malloc(BUFFER_SIZE/64*sizeof(int));
	for(j = 0; j < i - wordLength - 1; j++) {
		char* substr = malloc(wordLength);
		strncpy(substr, buf+j, wordLength);
		if(strcmp(substr, word) == 0){
			if(j != 0){
				if ((buf[j - 1] == ' ' || buf[j - 1] == '?' || buf[j - 1] == '!' || buf[j - 1] == '.' || buf[j - 1] == ':' || buf[j - 1] == ';') && 
					(buf[j + wordLength] == ' ' || buf[j + wordLength] == '?' || buf[j + wordLength] == '!' || buf[j + wordLength] == '.' || buf[j + wordLength] == ':' || buf[j + wordLength] == ';'))
						indices[count++] = j;
			}
			else 
				if (buf[j + wordLength] == ' ' || buf[j + wordLength] == '?' || buf[j + wordLength] == '!' || buf[j + wordLength] == '.' || buf[j + wordLength] == ':' || buf[j + wordLength] == ';')
					indices[count++] = j;
		}
		free(substr);
	}
	for(j = 0; j < i; j++){
		if(inVector(indices, count, j) == 0)
			fputc(buf[j], fd);
		else
			j = j + wordLength - 1;
	}
	printf("Numar de aparitiiul de aparitii al cuvantului '%s' in fisierul dat este : %d", word, count); 
	free(buf);
	free(indices);
	fclose(fd);
	return 0;
}