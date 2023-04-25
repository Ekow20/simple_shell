#include "main.h"

int main(int ac, char **argv)
{
char *prompt = "(Myshell) $ ";
char *lineptr;
char *lineptr_copy = NULL;
const char *delim = " \n";
size_t n = 0;
ssize_t nchars_read;
int num_tokens = 0;
char *token;
int i;

(void)ac;

while (1)
{
printf("%s", prompt);
nchars_read = getline(&lineptr, &n, stdin);

/* Check to see if the getline method failed or if the user used CTRL + D. */
if (nchars_read == -1)
{
printf("Exiting !!!\n");
return (-1);
}

lineptr_copy = malloc(sizeof(char) * nchars_read);
if (lineptr_copy == NULL)
{
perror("tsh: memory allocation error");
return (-1);
}
strcpy(lineptr_copy, lineptr);

/* split the string (lineptr) into an array of words */
/* calculate the total number of tokens */
token = strtok(lineptr, delim);

while (token != NULL)
{
num_tokens++;
token = strtok(NULL, delim);
}
num_tokens++;

/* Allocate space to hold the array of strings */
argv = malloc(sizeof(char *) * num_tokens);

/* Store each token in the argv array */
token = strtok(lineptr_copy, delim);

for (i = 0; token != NULL; i++)
{
argv[i] = malloc(sizeof(char) * strlen(token));
strcpy(argv[i], token);

token = strtok(NULL, delim);
}
argv[i] = NULL;

execmd(argv);

printf("%s\n", lineptr);
free(lineptr);
}
return (0);
}
