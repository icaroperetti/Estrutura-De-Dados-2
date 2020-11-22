#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 30

/* 
    Aluno: Icaro Peretti 
    Arvore binaria de busca com livros
*/

typedef struct sBook
{
    int issn;
    char name[30];
} Book;

typedef struct sNodo
{
    struct sNodo *left;
    struct sNodo *right;
    Book *book;
} Nodo;

Book *createBook(char *name, int issn)
{
    Book *book;
    book = (Book *)malloc(sizeof(Book));
    if (book == NULL)
    {
        printf("Memoria nao alocada livro");
    }
    book->issn = issn;
    strcpy(book->name, name);
    return book;
}

Nodo *createNodo()
{
    Nodo *nodo;
    nodo = (Nodo *)malloc(sizeof(Nodo));

    if (nodo == NULL)
    {
        printf("Memoria nao alocada nodo");
    }
    nodo->left = NULL;
    nodo->right = NULL;
    nodo->book = NULL;
    return nodo;
}

Nodo *insertNode(Nodo *root, Book *book)
{
    if (root == NULL)
    {
        Nodo *aux = createNodo();
        aux->book = book;
        return aux;
    }
    else
    {
        if (book->issn > root->book->issn)
        {
            root->right = insertNode(root->right, book);
        }
        else if (book->issn < root->book->issn)
        {
            root->left = insertNode(root->left, book);
        }
    }
    return root;
}

void preOrder(Nodo *root)
{
    if (root != NULL)
    {
        printf("ISSN:%d ", root->book->issn);
        printf("Livro:%s, ", root->book->name);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Nodo *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("ISSN:%d ", root->book->issn);
        printf("Livro:%s, ", root->book->name);
        inOrder(root->right);
    }
}

void postOrder(Nodo *root)
{
    if (root == NULL)
    {
        return;
    }
    if (root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("ISSN:%d ", root->book->issn);
        printf("Livro:%s, ", root->book->name);
    }
}

Nodo *searchNode(Nodo *root, int issn)
{
    if (root == NULL)
    {
        printf("Elemento nao encontrado");
        return root;
    }
   
    else if (issn > root->book->issn)
    {
        searchNode(root->right, issn);
    }
    else if(issn < root->book->issn)
    {
        return searchNode(root->left, issn);
    }
     else if (root->book->issn == issn)
    {
        printf("\nLivro encontrado -> ISSN:%d Nome do livro:%s", root->book->issn, root->book->name);
        return root;
    }
}

Nodo *searchMin(Nodo *root)
{
    Nodo *aux = root;
    if (root != NULL)
    {
        while (root->left != NULL)
        {
            aux = aux->left; 
        }
        return aux;
    }
    return NULL;
}


Nodo *deleteNode(Nodo *root, int issn)
{
    if(root == NULL)
    {
        return root;
    }
    if(issn < root->book->issn)
    {
        root->left = deleteNode(root->left,issn);
    }
    else if(issn > root->book->issn)
    {
        root->right = deleteNode(root->right,issn);
    }else
    {

        if(root->left == NULL)
        {
            Nodo* temp = root->right;
            free(root);
            return temp;

        }
        else if(root->right == NULL)
        {
            
            Nodo* temp = root->left;
            free(root);
            return temp;
        }

        //Encontrar o menor elemento da subarvore da direita
        Nodo* substitute = searchMin(root->right);
        Book* aux = substitute; //Faz uma copia do elemento encontrado

        root->right = deleteNode(root->right,substitute->book->issn); //Deleta o menor valor
        root->book = substitute->book; //Joga o menor valor guardado como root
        
    } 
    return root;  
}


void destroy(Nodo* root)
{   
    if (root != NULL)
    {
        destroy(root->left);
        destroy(root->right);
        free(root->book);
    }
}

void menu()
{
    char name[TAM];
    int op = 0, issn = 0;
    Nodo *root = NULL;

    for (;;)
    {
        printf("\nSelecione uma opcao:\n0 - Sair\n1 - Inserir\n2 - Imprimir em ordem\n3 - Imprimir em pre-ordem\n4 - Imprimir em pos-ordem\n5 - Buscar\n6 - Remover\n7 - Destruir arvore\n");
        scanf("%d", &op);

        if (op == 1)
        {
            printf("Digite o nome da obra: ");
            scanf(" %[^\n]", &name);

            printf("Digite o ISSN:");
            scanf("%d", &issn);
            Book *book = createBook(name, issn);
            root = insertNode(root, book);
           
        }
        if (op == 2)
        {
            inOrder(root);
        }
        if (op == 3)
        {
            preOrder(root);
        }
        if (op == 4)
        {
            postOrder(root);
        }
        if (op == 5)
        {
            printf("Digite o issn:");
            scanf("%d",&issn);
            searchNode(root, issn);
        }
        if (op == 6)
        {
            printf("Digite o issn:");
            scanf("%d", &issn);
            root = deleteNode(root, issn);
        }
        if (op == 7)
        {
            destroy(root);
            printf("Insira novos elementos");
        }
        if (op <= 0 || op > 7)
        {
            printf("Programa finalizdo!...");
            exit(0);
        }
    }
}

int main()
{
    menu();
    return 0;
}
