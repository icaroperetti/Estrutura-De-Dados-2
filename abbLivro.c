#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TAM 30

typedef struct sBook {
    int ssn;
    char name[30];
}Book;

typedef struct sNodo{
    struct sNodo* left;
    struct sNodo* right;
    Book* book;
}Nodo;

Nodo* inicialize(){
    return NULL;
}

Book* createBook(char* name,int ssn){
    Book* book;
    book = (Book*)malloc(sizeof(Book));
    book->ssn = ssn;
    strcpy(book->name,name);
    return book;
}

Nodo* createNode(){
    Nodo* nodo;
    nodo = (Nodo*)malloc(sizeof(Nodo*));
    nodo->left = NULL;
    nodo->right = NULL;
    nodo->book = NULL;
    return nodo;
}

Nodo* insertNode(Nodo* root,Book* book){
    if (root == NULL) {
        Nodo *aux = createNode();
        aux->book = book;
        return aux;
    }
    else{
        if (book->ssn > root->book->ssn){
            root->right = insertNode(root->right, book);
        }
        else if (book->ssn < root->book->ssn){
            root->left = insertNode(root->left, book);
        }
    }
    return root;
}

void printTree(Nodo* root){
    if(root != NULL){
        printf("%d ",root->book->ssn);
        printf("%s ",root->book->name);
        printTree(root->left);
        printTree(root->right);
    }
}


int main(){
    Nodo* root = inicialize();
    char livro[TAM];

    printf("Digite o nome da obra: ");
    fgets(livro,TAM,stdin);
    Book* book = createBook(livro,10);

    printf("Digite o nome da obra: ");
    fgets(livro,TAM,stdin);
    Book* book1 = createBook(livro,20);

    printf("Digite o nome da obra: ");
    fgets(livro,TAM,stdin);
    Book* book2 = createBook(livro,9);

    root = insertNode(root,book);
    root = insertNode(root,book1);
     root = insertNode(root,book2);
    printTree(root);

    return 0;
}