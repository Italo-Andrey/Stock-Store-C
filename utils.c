#include <stdio.h>

FILE *GetFile(char *mode)
{
    FILE *file = fopen("products.csv", mode);
    return file;
}

FILE *GetTempFile(char *mode)
{
    FILE *file = fopen("tmp.csv", mode);
    if (file == NULL)
    {
        printf("Nao pode abrir o arquivo, reinicie o programa");
        exit(1);
    }
    return file;
}

void ChangeFiles()
{
    remove("products.csv");
    rename("tmp.csv", "products.csv");
}
