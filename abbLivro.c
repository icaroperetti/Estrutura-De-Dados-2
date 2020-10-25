#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TAM 30

/* Aluno: Icaro Peretti */

typedef struct sBook {
    int issn;
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

Book* createBook(char* name,int issn){
    Book* book;
    book = (Book*)malloc(sizeof(Book));
    if(book == NULL){
        printf("Memoria nao alocada livro");
    }
    book->issn = issn;
    strcpy(book->name,name);
    return book;
}

Nodo* memoryAllocation(){
    Nodo* nodo;
    nodo = (Nodo*)malloc(sizeof(Nodo));
    if(nodo == NULL){
        printf("Memoria nao alocada nodo");
    }
    nodo->left = NULL;
    nodo->right = NULL;
    nodo->book = NULL;
    return nodo;
}

Nodo* insertNode(Nodo* root,Book* book){
    if (root == NULL) {
        Nodo *aux = memoryAllocation();
        aux->book = book;
        return aux;
    }
    else{
        if (book->issn > root->book->issn){
            root->right = insertNode(root->right, book);
        }
        else if (book->issn < root->book->issn){
            root->left = insertNode(root->left, book);
        }
    }
    return root;
}

void printTree(Nodo* root){
    if(root != NULL){
        printf("ISSN:%d ",root->book->issn);
        printf("Livro:%s, ",root->book->name);
        printTree(root->left);
        printTree(root->right);
    }
}

Nodo* searchNode(Nodo* root, int issn){
    if(root != NULL){
        if(root->book->issn == issn){
            return root;
        }else{
            if(issn > root->book->issn){
                return searchNode(root->right,issn);
                
            }else{
                return searchNode(root->left,issn);
            }
        }
    }
    return NULL;
}

void found(Nodo* temp){
     if(temp == NULL){
        printf("\nElemento nao encontrado");
        printf("\n");
    }else{
        printf("\nElemento encontrado -> ISSN:%d, Nome do livro:%s",temp->book->issn,temp->book->name);
        printf("\n");
    }
}

int main(){
    Nodo* root = inicialize();
    char livro[TAM];

    printf("Digite o nome da obra: ");
    scanf(" %[^\n]",livro);
    Book* book = createBook(livro,10);

    printf("Digite o nome da obra: ");
    scanf( " %[^\n]",livro);
    Book* book1 = createBook(livro,20);

    printf("Digite o nome da obra: ");
    scanf( " %[^\n]",livro);
    Book* book2 = createBook(livro,9);

    printf("Digite o nome da obra: ");
    scanf( " %[^\n]",livro);
    Book* book3 = createBook(livro,22);

    printf("Digite o nome da obra: ");
    scanf( " %[^\n]",livro);
    Book* book4 = createBook(livro,8);

    root = insertNode(root,book);
    root = insertNode(root,book1);
    root = insertNode(root,book2);
    root = insertNode(root,book3);
    root = insertNode(root,book4);

    Nodo* temp = searchNode(root,28);
    found(temp);
    
    printTree(root);

    return 0;
}
