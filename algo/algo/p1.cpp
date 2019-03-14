#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NWORD 200000
#define BUFFER_LENGTH 100

typedef struct Dict {
	char word[BUFFER_LENGTH];
	char *mean;
}Dict;

FILE *fp;
Dict book[NWORD];
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
			printf("파일을 찾을 수 없습니다.\n");
		else {
			printf("파일을 불러왔습니다.\n\n");
			return;
		}

	}
}

void save()
{
	char moon[2000];
	int ok = 0;

	while (!feof(fp)) {
		fgets(moon, 2000, fp);
		if (moon[0] == '\n')
			continue;

		while (moon[ok] != '(')
			ok++;
		ok--;

		book[size].mean = strdup(moon);
		moon[ok] = '\0';
		strcpy(book[size].word, moon);
		size++;
		ok = 0;
	}
}

void find(int first, int last, char *sword)
{
	int mid, res = 0;

	if (last - first < 100) {
		for (int i = first; i != last; i++) {
			if (strcmpi(book[i].word, sword) == 0) {
				puts(book[i].mean);
				res++;
			}
		}
		if (res == 0) {
			while (first < last) {
				mid = (first + last) / 2;
				if (strcmpi(book[mid].word, sword) > 0)
					last = mid - 1;
				else
					first = mid + 1;
			}
			printf("Not found!\n");
			puts(book[first].word);
			printf("- - - - -\n");
			puts(book[first + 1].word);
			printf("\n");
		}
		else
			res = 0;
		return;
	}

	mid = (first + last) / 2;

	if (strcmpi(book[mid].word, sword) == 0) {
		for (int i = mid - 50; i != mid + 50; i++) {
			if (strcmpi(book[i].word, sword) == 0) {
				puts(book[i].mean);
			}
		}
		return;
	}
	else if (strcmpi(book[mid].word, sword) > 0)
		return find(first, mid - 1, sword);
	else
		return find(mid + 1, last, sword);
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
		else if (strcmp(command, "exit") == 0)
			break;
		else {
			strtok(command, " ");
			if (strcmp(command, "find") == 0) {
				moon = strtok(NULL, "\0");
				find(0, size, moon);
			}
			else
				printf("잘못된 입력입니다.\n\n");
		}
	}

	return 0;
}