#include <stdio.h>
#include <stdlib.h>
#include "./data_structures/product.c"

int main()
{
    Product *product;
    Products *products;
    int counter, op, id, quantity;
    float price;
    char *name = malloc(sizeof(char));

    printf("\n1 - Cadastrar Produto");
    printf("\n2 - Listar Produtos");
    printf("\n3 - Editar Produtos");
    printf("\n4 - Remover Produtos");
    printf("\n5- Realizar uma Venda");
    printf("\n0 - SAIR");
    printf("\nEscolha sua opcao:");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        id = GetId();
        printf("\nNome do Produto:");
        scanf("%s", name);
        printf("\nPreço do Produto:");
        scanf("%f", &price);
        printf("\nQuantidade do Produto:");
        scanf("%d", &quantity);
        CreateProduct(id, name, price, quantity);
        break;
    case 2:
        products = ListProducts();
        if (products == NULL)
        {
            printf("Nenhum Produto encontrado");
            break;
        }
        for (counter = 0; counter < products->size; counter++)
        {
            if (!products->products[counter].isActive)
            {
                continue;
            }
            printf("\nId do Produto: %d\n", products->products[counter].id);
            printf("Nome do Produto: %s\n", products->products[counter].name);
            printf("Preco do Produto: RS %.2f\n", products->products[counter].price);
            printf("Quantidate do Produto: %d\n", products->products[counter].quantity);
        }
        break;
    case 3:
        printf("\nDigite o Id do Produto: ");
        scanf("%d", &id);
        product = SelectProductById(id);
        if (product == NULL)
        {
            printf("produto não encontrado");
            break;
        }
        printf("%d,%.2f,%d,%d,%s,\n", product->id, product->price, product->quantity, product->isActive, product->name);
        printf("\n Digite o novo Nome: ");
        scanf("%s", name);
        printf("\n Digite o novo Preço: ");
        scanf("%f", &price);
        printf("\n Digite a nova Quantidade: ");
        scanf("%d", &quantity);
        UpdateProduct(product, name, price, quantity, 1);
        printf("Produto atualizado com sucesso");
        break;
    case 4:
        printf("\n Insira o ID do Produto para Remoção: ");
        scanf("%d", &id);
        SoftDeleteProduct(id);
        break;
    case 5:
        printf("\n Insira o ID do produto para compra: ");
        scanf("%d", &id);
        printf("\nDigite a quantidade comprada: ");
        scanf("%d", &quantity);
        ShopProduct(id, quantity);
        printf("Compra feita com sucesso");
        break;
    case 0:
        printf("\n Obrigado por usar nossos serviços, BY: Ítalo Andrade-126816 & Lucas Sapucaia-112195");
        break;
    default:
        printf("\nErro na escolha da opcao");
        break;
    }
    free(product);
    free(products);
    free(name);
}
