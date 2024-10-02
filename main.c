#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUTOS 100 // Número máximo de produtos que podem ser cadastrados
#define MAX_CARRINHO 50  // Número máximo de itens no carrinho

// Estrutura que define um produto
typedef struct
{
    int codigo;            // Código identificador do produto
    int quantidadeEstoque; // Quantidade disponível em estoque
    char nome[50];         // Nome do produto
    float preco;           // Preço por unidade do produto
} Produto;

// Estrutura que define um item no carrinho
typedef struct
{
    Produto produto; // Produto adicionado ao carrinho
    int quantidade;  // Quantidade comprada do produto
} ItemCarrinho;

// Declaração de variáveis globais para armazenar produtos e itens do carrinho
Produto produtos[MAX_PRODUTOS];      // Lista de produtos cadastrados
ItemCarrinho carrinho[MAX_CARRINHO]; // Lista de itens no carrinho
int numProdutos = 0;                 // Quantidade atual de produtos cadastrados
int numItensCarrinho = 0;            // Quantidade atual de itens no carrinho

// Função que busca um produto pelo código
// Retorna o ponteiro para o produto se encontrado, caso contrário, retorna NULL
Produto *pegarProdutoPorCodigo(int codigo)
{
    for (int i = 0; i < numProdutos; i++)
    {
        if (produtos[i].codigo == codigo)
        {
            return &produtos[i]; // Retorna o endereço do produto encontrado
        }
    }
    return NULL; // Retorna NULL se o produto não for encontrado
}

// Função que exibe o menu principal e gerencia a escolha do usuário
void menu()
{
    int opcao;
    do
    {
        system("cls"); // Limpa a tela
        // Exibe as opções do menu
        printf("----------------------------------------\n"
               "------------- MENU MERCADO -------------\n"
               "----------------------------------------\n"
               "1. Cadastrar Produto\n"
               "2. Listar Produtos\n"
               "3. Comprar Produto\n"
               "4. Visualizar Carrinho\n"
               "5. Fechar Pedido\n"
               "6. Adicionar quantidade no estoque\n"
               "7. Remover Produto\n"
               "8. Remover Item do Carrinho\n"
               "0. Sair\n"
               "Escolha uma opcao: \n");
        scanf("%d", &opcao); // Lê a escolha do usuário

        // Executa a função correspondente à opção escolhida
        switch (opcao)
        {
        case 1:
            system("cls");
            cadastrarProduto();
            break;
        case 2:
            system("cls");
            listarProdutos();
            break;
        case 3:
            system("cls");
            comprarProduto();
            break;
        case 4:
            system("cls");
            verCarrinho();
            break;
        case 5:
            system("cls");
            fecharCarrinho();
            break;
        case 6:
            system("cls");
            adicionarEstoque();
            break;
        case 7:
            system("cls");
            removerProduto();
            break;
        case 8:
            system("cls");
            removerItemCarrinho();
            break;
        case 0:
            system("cls");
            printf("Fechando o Programa...\n");
            break;
        default:
            system("cls");
            printf("Opcao invalida!\n");
            system("pause"); // Pausa para permitir que o usuário veja a mensagem
        }
    } while (opcao != 0); // Continua exibindo o menu até que o usuário escolha sair
}

// Função para verificar se uma string contém apenas números
// Retorna 1 se todos os caracteres forem dígitos, caso contrário, retorna 0
int lerNumero(const char *str)
{
    while (*str)
    {
        if (!isdigit(*str))
        {
            return 0; // Retorna 0 se encontrar um caractere não numérico
        }
        str++;
    }
    return 1; // Retorna 1 se todos os caracteres forem dígitos
}

// Função para cadastrar um novo produto no sistema
void cadastrarProduto()
{
    printf("----------- CADASTRO PRODUTO -----------\n\n ");

    // Verifica se o limite de produtos foi atingido
    if (numProdutos >= MAX_PRODUTOS)
    {
        printf("Limite de produtos atingido!\n");
        system("pause");
        return;
    }

    Produto novoProduto;
    char codigoStr[20]; // String para armazenar o código como texto

    // Solicita e valida o código do produto
    printf("Crie e informe o codigo do produto: ");
    scanf("%s", codigoStr); // Lê a entrada como string

    if (!lerNumero(codigoStr))
    {
        printf("Erro: O código deve conter apenas números!\n");
        system("pause");
        return;
    }

    novoProduto.codigo = atoi(codigoStr); // Converte a string para inteiro

    // Verifica se o código já está cadastrado
    for (int i = 0; i < numProdutos; i++)
    {
        if (produtos[i].codigo == novoProduto.codigo)
        {
            printf("Codigo ja cadastrado!\n");
            system("pause");
            return;
        }
    }

    // Solicita o nome, preço e quantidade em estoque do novo produto
    printf(" Informe o nome do produto: ");
    scanf(" %[^\n]s", novoProduto.nome); // Lê toda a linha até o enter

    printf(" Informe o preco do produto: R$ ");
    scanf("%f", &novoProduto.preco);

    printf(" Informe a quantidade a ser adicionada no estoque: ");
    scanf("%d", &novoProduto.quantidadeEstoque);

    // Adiciona o novo produto ao array de produtos
    produtos[numProdutos++] = novoProduto;
    printf(" Cadastro Concluido!\n");
    system("pause");
}

// Função para listar todos os produtos cadastrados
void listarProdutos()
{
    printf("--------- PRODUTOS CADASTRADOS ---------\n ");

    // Exibe todos os produtos cadastrados
    for (int i = 0; i < numProdutos; i++)
    {
        printf("\n--- Produto (%d) ---\n", i + 1);
        printf("Codigo: %d \n", produtos[i].codigo);
        printf("Nome: %s \n", produtos[i].nome);
        printf("Preco por unidade: R$ %.2f \n", produtos[i].preco);
        printf("Quantidade no estoque: %d \n", produtos[i].quantidadeEstoque);
    }
    system("pause");
}

// Função para comprar um produto e adicioná-lo ao carrinho
void comprarProduto()
{
    printf("----------- COMPRAR PRODUTOS -----------\n ");
    int codigo, quantidade;

    // Exibe os produtos disponíveis
    for (int i = 0; i < numProdutos; i++)
    {
        printf("\n--- Produto (%d) ---\n", i + 1);
        printf("Codigo: %d \n", produtos[i].codigo);
        printf("Nome: %s \n", produtos[i].nome);
        printf("Preco por unidade: R$ %.2f \n", produtos[i].preco);
        printf("Quantidade no estoque: %d \n", produtos[i].quantidadeEstoque);
    }

    // Solicita o código do produto a ser comprado
    printf("\nCodigo do produto: \n");
    scanf("%d", &codigo);

    // Busca o produto pelo código
    Produto *ponteiro = pegarProdutoPorCodigo(codigo);
    if (ponteiro == NULL)
    {
        printf("Produto nao encontrado\n");
        system("pause");
        return;
    }
    system("cls");
    printf("Produto selecionado: %s\n", ponteiro->nome);

    // Solicita a quantidade desejada
    printf("Quantidade do produto: \n");
    scanf("%d", &quantidade);

    // Valida a quantidade informada
    if (quantidade <= 0)
    {
        printf("Quantidade invalida!\n");
        system("pause");
        return;
    }

    // Verifica se há estoque suficiente
    if (ponteiro->quantidadeEstoque < quantidade)
    {
        printf("Estoque insuficiente!\n");
        system("pause");
        return;
    }

    // Verifica se o produto já está no carrinho
    int indiceCarrinho = -1;
    for (int i = 0; i < numItensCarrinho; i++)
    {
        if (carrinho[i].produto.codigo == codigo)
        {
            carrinho[i].quantidade += quantidade; // Aumenta a quantidade no carrinho
            indiceCarrinho = i;
            break;
        }
    }

    // Caso o produto não esteja no carrinho, adiciona um novo item
    if (indiceCarrinho == -1)
    {
        carrinho[numItensCarrinho].produto = *ponteiro;
        carrinho[numItensCarrinho].quantidade = quantidade;
        numItensCarrinho++;
    }

    // Atualiza o estoque do produto
    ponteiro->quantidadeEstoque -= quantidade;
    printf("Produto adicionado ao carrinho!\n");
    system("pause");
}

// Função para exibir os itens no carrinho
void verCarrinho()
{
    printf("----------- ITENS NO CARRINHO -----------\n ");

    if (numItensCarrinho == 0)
    {
        printf("Carrinho vazio!\n");
    }
    else
    {
        for (int i = 0; i < numItensCarrinho; i++)
        {
            printf("\n--- Item (%d) ---\n", i + 1);
            printf("Produto: %s\n", carrinho[i].produto.nome);
            printf("Preco: R$ %.2f\n", carrinho[i].produto.preco);
            printf("Quantidade: %d\n", carrinho[i].quantidade);
        }
    }
    system("pause");
}

// Função para finalizar a compra e calcular o total
void fecharCarrinho()
{
    printf("----------- FECHAR CARRINHO -----------\n ");
    float total = 0;

    for (int i = 0; i < numItensCarrinho; i++)
    {
        total += carrinho[i].produto.preco * carrinho[i].quantidade; // Calcula o total
    }

    if (total == 0)
    {
        printf("Carrinho vazio!\n");
    }
    else
    {
        printf("Valor total da compra: R$ %.2f\n", total);
        numItensCarrinho = 0; // Limpa o carrinho
        printf("Compra finalizada!\n");
    }
    system("pause");
}

// Função para adicionar estoque a um produto existente
void adicionarEstoque()
{
    printf("----------- ADICIONAR ESTOQUE -----------\n ");
    int codigo, quantidade;

    // Solicita o código do produto
    printf("Codigo do produto: \n");
    scanf("%d", &codigo);

    // Busca o produto pelo código
    Produto *ponteiro = pegarProdutoPorCodigo(codigo);
    if (ponteiro == NULL)
    {
        printf("Produto nao encontrado\n");
        system("pause");
        return;
    }

    // Solicita a quantidade a ser adicionada
    printf("Quantidade a ser adicionada no estoque: \n");
    scanf("%d", &quantidade);

    if (quantidade <= 0)
    {
        printf("Quantidade invalida!\n");
        system("pause");
        return;
    }

    // Atualiza o estoque do produto
    ponteiro->quantidadeEstoque += quantidade;
    printf("Estoque atualizado!\n");
    system("pause");
}

// Função para remover um produto do sistema
void removerProduto()
{
    printf("----------- REMOVER PRODUTO -----------\n ");
    int codigo;

    // Solicita o código do produto
    printf("Codigo do produto: \n");
    scanf("%d", &codigo);

    // Busca o produto pelo código
    for (int i = 0; i < numProdutos; i++)
    {
        if (produtos[i].codigo == codigo)
        {
            // Remove o produto deslocando os elementos
            for (int j = i; j < numProdutos - 1; j++)
            {
                produtos[j] = produtos[j + 1];
            }
            numProdutos--;
            printf("Produto removido!\n");
            system("pause");
            return;
        }
    }

    printf("Produto nao encontrado!\n");
    system("pause");
}

// Função para remover um item do carrinho
void removerItemCarrinho()
{
    printf("----------- REMOVER ITEM DO CARRINHO -----------\n ");
    int codigo;

    // Solicita o código do produto no carrinho
    printf("Codigo do produto: \n");
    scanf("%d", &codigo);

    // Busca o produto no carrinho pelo código
    for (int i = 0; i < numItensCarrinho; i++)
    {
        if (carrinho[i].produto.codigo == codigo)
        {
            // Remove o item do carrinho deslocando os elementos
            for (int j = i; j < numItensCarrinho - 1; j++)
            {
                carrinho[j] = carrinho[j + 1];
            }
            numItensCarrinho--;
            printf("Item removido do carrinho!\n");
            system("pause");
            return;
        }
    }

    printf("Item nao encontrado no carrinho!\n");
    system("pause");
}

// Função principal que inicia o programa
int main()
{
    menu(); // Inicia o menu principal
    return 0;
}
