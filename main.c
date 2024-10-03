#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CADASTROS 100     // Limite de produtos cadastráveis
#define MAX_ITENS_CARRINHO 50 // Limite de itens no carrinho

// Estrutura para armazenar informações de um produto
typedef struct
{
    int codigo;    // Código único do produto
    int estoque;   // Quantidade disponível
    char nome[30]; // Nome do produto
    float preco;   // Preço unitário
} Produto;

// Estrutura para itens adicionados ao carrinho
typedef struct
{
    Produto produto; // Produto no carrinho
    int quantidade;  // Quantidade escolhida
} ProdCarrinho;

// Variáveis globais para armazenar produtos e itens no carrinho
Produto gProdutos[MAX_CADASTROS];           // Lista de produtos cadastrados
ProdCarrinho gCarrinho[MAX_ITENS_CARRINHO]; // Lista de itens no carrinho
int gNumProdutos = 0;                       // Quantidade de produtos cadastrados
int gNumProdCarrinho = 0;                   // Quantidade de itens no carrinho

// Exibe o menu principal e executa ações baseadas na escolha
void menu()
{
    int opcao;
    do
    {
        system("cls"); // Limpa a tela a cada loop do menu
        printf("----------------------------------------\n"
               "------------- MENU MERCADO -------------\n"
               "----------------------------------------\n\n"
               "1. Cadastrar Produto\n\n"
               "2. Listar Produtos\n\n"
               "3. Comprar Produto\n\n"
               "4. Visualizar Carrinho\n\n"
               "5. Fechar Pedido\n\n"
               "6. Adicionar Quantidade no Estoque\n\n"
               "7. Remover Produto do Sistema\n\n"
               "8. Remover Item do Carrinho\n\n"
               "0. Sair\n\n"
               "Escolha uma opcao:  ");
        scanf("%d", &opcao); // Lê a opção do usuário

        // Chama a função correspondente à opção
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
            removerProdutoCadastrado();
            break;
        case 8:
            system("cls");
            removerProdCarrinho();
            break;
        case 0:
            system("cls");
            printf("Fechando o Programa...\n");
            break;
        default:
            system("cls");
            printf("Opcao invalida!\n");
            system("pause");
        }
    } while (opcao != 0); // Continua até o usuário escolher sair
}

// Verifica se uma string contém apenas números
int lerNumero(const char *CodigoDigitado)
{
    // Percorre elemento por string, indo até o último caractere
    for (int i = 0; i < strlen(CodigoDigitado); i++)
    {
        if (!isdigit(CodigoDigitado[i]))
        {
            return 0; // Retorna falso se algum caractere não for número
        }
    }
    return 1; // Retorna verdadeiro se todos forem números
}

// Função para cadastrar um novo produto
void cadastrarProduto()
{
    printf("----------- CADASTRO PRODUTO -----------\n\n ");
    if (gNumProdutos >= MAX_CADASTROS)
    {
        printf("Limite de produtos atingido!\n");
        system("pause");
        return;
    }

    Produto novoProduto;

    char codigoDigitado[30]; // Variavel para armazenar o 'codigo' como string

    printf("Crie e informe o codigo do produto: ");
    scanf("%s", codigoDigitado);

    // Confere se foram digitados apenas números no 'codigo'
    if (!lerNumero(codigoDigitado))
    {
        printf("Erro: O código deve conter apenas números!\n");
        system("pause");
        return;
    }

    // Converte a string para int
    novoProduto.codigo = atoi(codigoDigitado);

    // Verifica se o codigo já foi cadastrado
    for (int i = 0; i < gNumProdutos; i++)
    {
        if (gProdutos[i].codigo == novoProduto.codigo)
        {
            printf("Codigo ja cadastrado!\n");
            system("pause");
            return;
        }
    }

    printf(" Informe o nome do produto: ");
    scanf(" %[^\n]s", novoProduto.nome);

    printf(" Informe o preco do produto: R$ ");
    scanf("%f", &novoProduto.preco);

    printf(" Informe a quantidade a ser adicionada no estoque: ");
    scanf("%d", &novoProduto.estoque);

    gProdutos[gNumProdutos++] = novoProduto;
    printf(" Cadastro Concluido!\n");
    system("pause");
}

// Função para listar produtos cadastrados
void listarProdutos()
{
    printf("--------- PRODUTOS CADASTRADOS ---------\n ");
    for (int i = 0; i < gNumProdutos; i++)
    {
        printf("\n--- Produto (%d) ---\n", i + 1);
        printf("Codigo: %d \n", gProdutos[i].codigo);
        printf("Nome: %s \n", gProdutos[i].nome);
        printf("Preco por unidade: R$ %.2f \n", gProdutos[i].preco);
        printf("Quantidade no estoque: %d \n", gProdutos[i].estoque);
    }
    system("pause");
}

// Função que busca produto pelo código
Produto *produtoPorCodigo(int codigo)
{
    for (int i = 0; i < gNumProdutos; i++)
    {
        if (gProdutos[i].codigo == codigo)
        {
            return &gProdutos[i];
        }
    }
    return NULL;
}

// Função para comprar um produto e adicioná-lo ao carrinho
void comprarProduto()
{
    printf("----------- COMPRAR PRODUTOS -----------\n ");
    int codigoLocal, quantidadeLocal;

    // Mostra as listas de produtoss
    for (int i = 0; i < gNumProdutos; i++)
    {
        printf("\n--- Produto (%d) ---\n", i + 1);
        printf("Codigo: %d \n", gProdutos[i].codigo);
        printf("Nome: %s \n", gProdutos[i].nome);
        printf("Preco por unidade: R$ %.2f \n", gProdutos[i].preco);
        printf("Quantidade no estoque: %d \n", gProdutos[i].estoque);
    }

    printf("\nCodigo do produto: \n");
    scanf("%d", &codigoLocal);

    // Busca o produto pelo codigo digitado
    Produto *ponteiro = produtoPorCodigo(codigoLocal);

    if (ponteiro == NULL)
    {
        printf("Produto nao encontrado\n");
        system("pause");
        return;
    }
    system("cls");
    printf("Produto selecionado: %s\n", ponteiro->nome);

    printf("Quantidade do produto: \n");
    scanf("%d", &quantidadeLocal);

    // verifica se a quanidade foi maior que 0
    if (quantidadeLocal <= 0)
    {
        printf("Quantidade invalida!\n");
        system("pause");
        return;
    }

    // Verifica se existe estoque suficiente comparado a quantidade solicitada para a compra
    if (ponteiro->estoque < quantidadeLocal)
    {
        printf("Estoque insuficiente!\n");
        system("pause");
        return;
    }

    // Verifica se o produto já está no carrinho
    int indiceCarrinho = -1;
    for (int i = 0; i < gNumProdCarrinho; i++)
    {
        if (gCarrinho[i].produto.codigo == codigoLocal)
        {
            gCarrinho[i].quantidade += quantidadeLocal;
            indiceCarrinho = i;
            break;
        }
    }

    // se não estiver, será adicionado no carrinho
    if (indiceCarrinho == -1)
    {
        gCarrinho[gNumProdCarrinho].produto = *ponteiro;
        gCarrinho[gNumProdCarrinho].quantidade = quantidadeLocal;
        gNumProdCarrinho++;
    }

    // Atualiza a quantidade do produto no estoque
    ponteiro->estoque -= quantidadeLocal;
    printf("Produto adicionado ao carrinho!\n");
    system("pause");
}

// Exibe os itens no carrinho
void verCarrinho()
{
    printf("----------- ITENS NO CARRINHO -----------\n ");
    if (gNumProdCarrinho > 0)
    {
        for (int i = 0; i < gNumProdCarrinho; i++)
        {
            printf("\n--- Item (%d) ---\n", i + 1);
            printf("Produto: %s\n", gCarrinho[i].produto.nome);
            printf("Quantidade: %d\n", gCarrinho[i].quantidade);
            printf("Preco total: R$ %.2f\n", gCarrinho[i].produto.preco * gCarrinho[i].quantidade);
        }
    }
    else
    {
        printf("Carrinho vazio!\n");
    }
    system("pause");
}

// Função para finalizar a compra e calcular o total
void fecharCarrinho()
{
    printf("----------- FECHAR CARRINHO -----------\n ");
    float total = 0;

    for (int i = 0; i < gNumProdCarrinho; i++)
    {
        printf("\n--- Item (%d) ---\n", i + 1);
        printf("Produto: %s\n", gCarrinho[i].produto.nome);
        printf("Preco: R$ %.2f\n", gCarrinho[i].produto.preco);
        printf("Quantidade: %d\n", gCarrinho[i].quantidade);
        total += gCarrinho[i].produto.preco * gCarrinho[i].quantidade;
    }

    if (total == 0)
    {
        printf("Carrinho vazio!\n");
    }
    else
    {
        printf("Valor total da compra: R$ %.2f\n", total);
        gNumProdCarrinho = 0; // Limpa o carrinho
    }
    system("pause");
}

// Função para adicionar estoque de produtos já cadastrados
void adicionarEstoque()
{
    printf("----------- ADICIONAR ESTOQUE -----------\n ");
    int codigo, quantidade;
    printf("Informe o codigo do produto: \n");
    scanf("%d", &codigo);

    Produto *ponteiro = produtoPorCodigo(codigo);
    if (ponteiro == NULL)
    {
        printf("Produto nao encontrado!\n");
        system("pause");
        return;
    }

    printf("Produto selecionado: %s\n", ponteiro->nome);
    printf("Quantidade a ser adicionada: \n");
    scanf("%d", &quantidade);

    if (quantidade <= 0)
    {
        printf("Quantidade invalida!\n");
    }
    else
    {
        ponteiro->estoque += quantidade;
        printf("Estoque atualizado com sucesso!\n");
    }
    system("pause");
}

// Função para remover um produto cadastrado
void removerProdutoCadastrado()
{
    printf("----------- REMOVER PRODUTO -----------\n ");

    // Mostra as listas de produtoss
    for (int i = 0; i < gNumProdutos; i++)
    {
        printf("\n--- Produto (%d) ---\n", i + 1);
        printf("Codigo: %d \n", gProdutos[i].codigo);
        printf("Nome: %s \n", gProdutos[i].nome);
        printf("Preco por unidade: R$ %.2f \n", gProdutos[i].preco);
    }

    int codigo;
    printf("Informe o codigo do produto a ser removido: \n");
    scanf("%d", &codigo);

    // Busca o produto pelo codigo digitado
    Produto *ponteiro = produtoPorCodigo(codigo);
    if (ponteiro == NULL)
    {
        printf("Produto nao encontrado!\n");
        system("pause");
        return;
    }

    for (int i = 0; i < gNumProdutos; i++)
    {
        if (gCarrinho[i].produto.codigo == codigo)
        {
            for (int j = i; j < gNumProdCarrinho - 1; j++)
            {
                gCarrinho[j] = gCarrinho[j + 1]; // Desloca os itens do carrinho
            }
            gNumProdCarrinho--; // Reduz o número total de itens no carrinho
        }
        if (gProdutos[i].codigo == codigo)
        {
            for (int j = i; j < gNumProdutos - 1; j++)
            {
                gProdutos[j] = gProdutos[j + 1]; // Desloca os produtos
            }
            gNumProdutos--; // Reduz o número total de produtos
            printf("Produto removido com sucesso!\n");
            break;
        }
    }

    system("pause");
}

// Função para remover item do carrinho
void removerProdCarrinho()
{
    printf("---------- REMOVER PRODUTOS CARRINHO ----------\n ");
    int codigo;

    // Mostra as listas de produtoss
    for (int i = 0; i < gNumProdutos; i++)
    {
        printf("\n--- Produto (%d) ---\n", i + 1);
        printf("Codigo: %d \n", gProdutos[i].codigo);
        printf("Nome: %s \n", gProdutos[i].nome);
        printf("Preco por unidade: R$ %.2f \n", gProdutos[i].preco);
    }

    printf("Informe o codigo do produto a ser removido: \n");
    scanf("%d", &codigo);

    for (int i = 0; i < gNumProdCarrinho; i++)
    {
        if (gCarrinho[i].produto.codigo == codigo)
        {
            for (int j = i; j < gNumProdCarrinho - 1; j++)
            {
                gCarrinho[j] = gCarrinho[j + 1]; // Desloca os itens do carrinho
            }
            gNumProdCarrinho--; // Reduz o número total de itens no carrinho
            printf("Item removido com sucesso!\n");
            system("pause");
            return;
        }
    }
    printf("Item nao encontrado no carrinho!\n");
    system("pause");
}

// Função principal do programa
int main()
{
    menu(); // Inicia o menu principal
    return 0;
}