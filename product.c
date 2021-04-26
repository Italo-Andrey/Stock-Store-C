#include <stdio.h>
#include <ctype.h>
#include "../utils.c"

typedef struct product
{
    int id;
    char *name;
    float price;
    int quantity;
    int isActive; // 0 -> Inactive || 1 -> Active
} Product;

typedef struct _products
{
    int size;
    Product *products;
} Products;

Product *createProduct(int id, char *name, float price, int quantity, int isActive)
{
    Product *product = malloc(sizeof(Product));
    product->id = id;
    product->name = name;
    product->price = price;
    product->quantity = quantity;
    product->isActive = isActive;

    return product;
}

void CreateProduct(int id, char *name, float price, int quantity)
{
    Product *product = createProduct(id, name, price, quantity, 1);
    FILE *file = GetFile("a");
    fprintf(file, "%d,%.2f,%d,%d,%s,\n", product->id, product->price, product->quantity, product->isActive, product->name);
    fclose(file);
    free(product);
    free(file);
}

Products *ListProducts()
{
    int counter = 0, index = 0, id, quantity, isActive;
    float price;
    char *temp = malloc(sizeof(char *));

    FILE *file = GetFile("r");
    if (file == NULL)
    {
        return NULL;
    }

    while (fgets(temp, 500, file))
    {
        counter++;
    }
    free(temp);
    if (counter == 0)
    {
        fclose(file);
        return NULL;
    }
    Product *productList = malloc(counter * (sizeof(Product)));

    fseek(file, 0L, SEEK_SET);
    char *line = malloc(sizeof(char *));
    char *result = malloc(sizeof(char *));
    while ((result = fgets(line, 500, file)) != NULL)
    {

        char *name = malloc(100);
        sscanf(line, "%d,%f,%d,%d,%[^,]s,", &id, &price, &quantity, &isActive, name);
        productList[index] = *createProduct(id, name, price, quantity, isActive);
        index++;
    }
    fclose(file);
    free(line);

    Products *products = malloc(sizeof(Products));
    products->size = counter;
    products->products = productList;
    return products;
}

Product *SelectProductById(int id)
{

    int quantity, tempId, isActive;
    float price;
    char *name = malloc(sizeof(char *));

    FILE *file = GetFile("r");
    char *line = malloc(sizeof(char *));

    while ((line = fgets(line, 500, file)) != NULL)
    {
        sscanf(line, "%d,%f,%d,%d,%[^,]s,", &tempId, &price, &quantity, &isActive, name);
        if (tempId == id)
        {

            Product *product = createProduct(id, name, price, quantity, isActive);
            fclose(file);
            return product;
        }
    }

    fclose(file);
    free(line);
    return NULL;
}

void HardDeleteProduct(int id)
{
    int tempId, quantity, isActive;
    char *name = malloc(100);
    float price;

    FILE *file = GetFile("r");
    FILE *tempFile = GetTempFile("w");
    char *line = malloc(sizeof(char *));

    while (fgets(line, 500, file) != NULL)
    {
        if (tempId != id)
        {
            sscanf(line, "%d,%f,%d,%d,%[^,]s,", &tempId, &price, &quantity, &isActive, name);
            fprintf(tempFile, "%d,%.2f,%d,%d,%s,\n", tempId, price, quantity, isActive, name);
        }
    }
    fclose(file);
    fclose(tempFile);
    free(line);

    ChangeFiles();
}

int UpdateProduct(Product *product, char *newName, float newPrice, int newQuantity, int newState)
{

    if (product == NULL)
        return 0;

    product->name = newName;
    product->price = newPrice;
    product->quantity = newQuantity;
    product->isActive = newState;

    int tempId, quantity, isActive;
    float price;

    FILE *file = GetFile("r");
    FILE *tempFile = GetTempFile("w");

    char *line = malloc(sizeof(char *));
    char *result = malloc(sizeof(char *));
    char *name = malloc(sizeof(char *));
    while ((result = fgets(line, 500, file)) != NULL)
    {

        sscanf(line, "%d,%f,%d,%d,%[^,]s,", &tempId, &price, &quantity, &isActive, name);
        if (tempId != product->id)
        {
            fprintf(tempFile, "%d,%.2f,%d,%d,%s,\n", tempId, price, quantity, isActive, name);
        }
        else
        {
            fprintf(tempFile, "%d,%.2f,%d,%d,%s,\n", product->id, product->price, product->quantity, product->isActive, product->name);
        }
    }

    fclose(file);
    fclose(tempFile);

    ChangeFiles();

    free(product);
    free(line);
    return 1;
}

int SoftDeleteProduct(int id)
{
    Product *product = SelectProductById(id);
    return UpdateProduct(product, product->name, product->price, product->quantity, 0);
}

void ShopProduct(int id, int quantity)
{
    Product *product = SelectProductById(id);
    UpdateProduct(product, product->name, product->price, product->quantity - quantity, product->isActive);
    free(product);
}

int GetId()
{
    Products *products = ListProducts();
    int id;
    if (products == NULL)
        id = 1;
    else
    {

        Product *lastItem = &products->products[products->size - 1];
        id = lastItem->id + 1;
        free(lastItem);
    }
    free(products);
    return id;
}
