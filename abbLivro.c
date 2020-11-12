#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 30

/* Aluno: Icaro Peretti 
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

Nodo *inicialize()
{
    return NULL;
}

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

Nodo *memoryAllocation()
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
        Nodo *aux = memoryAllocation();
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
    if (root != NULL)
    {
        if (root->book->issn == issn)
        {
            return root;
        }
        else
        {
            if (issn > root->book->issn)
            {
                return searchNode(root->right, issn);
            }
            else
            {
                return searchNode(root->left, issn);
            }
        }
    }
    return NULL;
}

void found(Nodo *temp)
{
    if (temp == NULL)
    {
        printf("\nLivro nao encontrado");
        printf("\n");
    }
    else
    {
        printf("\nLivro encontrado -> ISSN:%d Nome do livro:%s", temp->book->issn, temp->book->name);
        printf("\n");
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
            return aux;
        }
    }
    return NULL;
}

Nodo *deleteNode(Nodo *root, int issn)
{
    if (root == NULL)
    {
        printf("\nElemento nao encontrado para remover");
        return root;
    }
    if (issn < root->book->issn)
    {
        root->left = deleteNode(root->left, issn);
    }
    else if (issn > root->book->issn)
    {
        root->right = deleteNode(root->right, issn);
    }
    else
    {
        if (root->right == NULL)
        {
            Nodo *temp = root->left;
            free(root);
            return temp;
        }
        else if (root->left == NULL)
        {
            Nodo *temp = root->right;
            free(root);
            return temp;
        }
        else
        {
            //Remoção se tiver 2 nodos filhos
            Nodo *aux = searchMin(root->right);
            root->book = aux->book;
            root->right = deleteNode(root->right, aux->book->issn);
        }
    }
    return root;
}

int main()
{
    Nodo *root = inicialize();
    char name[TAM];

    printf("Digite o nome da obra: ");
    scanf(" %[^\n]", &name);
    Book *book = createBook(name, 10);

    printf("Digite o nome da obra: ");
    scanf(" %[^\n]", &name);
    Book *book1 = createBook(name, 20);

    printf("Digite o nome da obra: ");
    scanf(" %[^\n]", &name);
    Book *book2 = createBook(name, 8);

    printf("Digite o nome da obra: ");
    scanf(" %[^\n]", &name);
    Book *book3 = createBook(name, 19);

    root = insertNode(root, book);
    root = insertNode(root, book1);
    root = insertNode(root, book2);
    root = insertNode(root, book3);

    //root = deleteNode(root,10);

    printf("Pre Ordem\n");
    preOrder(root);

    printf("\n\nEm ordem\n");
    inOrder(root);

    printf("\n\nPost ordem\n");
    postOrder(root);

    Nodo *temp = searchNode(root, 20);
    found(temp);

    return 0;
}
