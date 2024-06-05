#include <stdio.h> /* printf */
#include <string.h> /* strcpy */
#include <ctype.h> /* tolower */
#include <stdlib.h> /* malloc */

size_t NumOfRows(char **envp);
size_t MaxRowLength(char **envp);
char *MakeLC(char *buffer);
void CopyToBuffer(char **envp, char **buffer);
char **AllocateBuffer(char **envp, size_t num_of_rows, size_t row_length);

int main(int argc, char **argv, char **envp)
{
    size_t num_of_rows = NumOfRows(envp);
    size_t row_length = MaxRowLength(envp);
    char **buffer = AllocateBuffer(envp, num_of_rows, row_length);
    size_t i = 0;

    for (i = 0; i < num_of_rows; ++i)
    {
        printf("%s\n", buffer[i]);
        free(buffer[i]);
    }

    free(buffer);

    return 0;
}

size_t NumOfRows(char **envp)
{
    size_t row_count = 0;
    
    while (*envp)
    {
        ++row_count;
        ++envp;
    }

    return row_count;
}

size_t MaxRowLength(char **envp)
{
    size_t row_length;
    row_length = strlen(*envp);

    while(*envp)
    {
        if (strlen(*envp) > row_length)
        {
            row_length = strlen(*envp);
        }
        ++envp;
    }
    return row_length;
}
        
char **AllocateBuffer(char **envp, size_t num_of_rows, size_t row_length)
{
    char **buffer = (char **)malloc(num_of_rows * sizeof(char *));
    size_t i = 0;

    for (i = 0; i < num_of_rows; ++i)
    {
        buffer[i] = (char *)malloc(row_length);
    }

   CopyToBuffer(envp, buffer);
   return buffer;
}

void CopyToBuffer(char **envp, char **buffer)
{
    while (*envp)
    {
        strcpy(*buffer, MakeLC(*envp));
        ++buffer;
        ++envp;
    }
}

char *MakeLC(char *buffer)
{
    size_t i = 0;

    while (buffer[i])
    {
        buffer[i] = tolower(buffer[i]);
        ++i;
    }
    return buffer;
}
