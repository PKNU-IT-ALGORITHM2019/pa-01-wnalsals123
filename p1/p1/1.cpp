#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NWORD 200000
#define BUFFER_LENGTH 100

FILE *fp;
char *dict[NWORD];
int size = 0;

void load()
{
	char buffer[BUFFER_LENGTH];

	while (1) {
		printf("$ read ");
		scanf("%s", buffer);
		getchar();
		fp = fopen(buffer, "r");
		if (fp == NULL) 
			printf("������ ã�� �� �����ϴ�.\n");
		else {
			printf("������ �ҷ��Խ��ϴ�.\n\n");
			return;
		}
			
	}
}

void save()
{
	char moon[1000];

	while (!feof(fp)) {
		fgets(moon, 1000, fp);
		if (moon[0] != '\n') {
			dict[size] = strdup(moon);
			size++;
		}
	}
}

void find(char *word)
{
	printf("%s!!\n", word);
}

int main()
{
	char command[BUFFER_LENGTH];
	char *moon;

	load();
	save();

	while (1) {
		printf("$ ");
		gets_s(command, sizeof(command));

		if (strcmp(command, "size") == 0)
			printf("%d\n", size);
		else {
			moon = strtok(command, " ");
			if (strcmp(moon, "find") == 0) {
				moon = strtok(NULL, " ");
				if (strcmp(moon, "exit") == 0)
					break;
				find(moon);
			}
			else
				printf("�߸��� �Է��Դϴ�.\n");
		}		
	}

	return 0;
}