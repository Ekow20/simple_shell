#include "main.h"

/*
* This function takes a command string as input and returns the full path of the file
* if it exists in any of the directories listed in the PATH environment variable.
* The function returns NULL if the file is not found in any of the directories.
*/
char *get_location(char *command)
{
char *path, *path_cp, *path_token, *file_path;
int command_length, directory_length;
struct stat buffer;

/* Get the PATH environment variable which contains a list of directories
* where the shell searches for executable files.
*/
path = getenv("PATH");

if (path)
{
/* Duplicate the path string using the strdup() function.
* Remember to free up memory for this because strdup() allocates memory
* that needs to be freed at a later time.
*/
path_cp = strdup(path);

/* Get the length of the command that was passed */
command_length = strlen(command);

/* Let's break down the path variable and get all the directories available */
path_token = strtok(path_cp, ":");

while (path_token != NULL)
{
/* Get the length of the directory */
directory_length = strlen(path_token);

/* Allocate memory for storing the command name together with the directory name */
file_path = malloc(command_length + directory_length + 2);
/* NB: We added 2 for the slash and null character we will introduce in the full command. */

/* To build the path for the command, let's copy the directory path and concatenate the command to it. */
strcpy(file_path, path_token);
strcat(file_path, "/");
strcat(file_path, command);
strcat(file_path, "\0");

/* Let's test if this file path actually exists and return it if it does, otherwise try the next directory */
if (stat(file_path, &buffer) == 0)
{
/* A return value of 0 means success, implying that the file_path is valid.*/

/* Free up allocated memory before returning your file_path */
free(path_cp);
return (file_path);
}
else
{
/* Free up the file_path memory so we can check for another path */
free(file_path);
path_token = strtok(NULL, ":");
}
}

/* If we don't find any file_path that exists for the command, we return NULL but we need to free up memory for path_cp */
free(path_cp);

/* Before we exit without luck, let's see if the command itself is a file_path that exists */
if (stat(command, &buffer) == 0)
{
return (command);
}

return (NULL);
}
return (NULL);
}
