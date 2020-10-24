#include<stdio.h>
#include<stdlib.h>
#define TAM 30


// typedef struct sBook {
//     int cod;
//     int ssn;
//     char name[TAM];
// }Book;

typedef struct sNodo{
    struct sNodo* left;
    struct sNodo* right;
    int* data;
}Nodo;

Nodo* inicialize(){
    return NULL;
}

Nodo* criaNodo(){
    Nodo* nodo = (Nodo*) malloc (sizeof(Nodo));

    if(nodo == NULL){
        printf("Memoria nao alocada");
    }

    nodo->left = NULL;
    nodo->right = NULL;
    nodo->data = NULL;
    return nodo;

}

Nodo* insertNode(Nodo* root, int data){
    if(root == NULL){
        Nodo* aux = criaNodo();
        aux->data = data;
        return aux;
    }
    else {
        if( data > root->data ){
            root->right = insertNode(root->right,data);
        }else{
            if(data < root->data){
                root->left = insertNode(root->left,data);
            }
        }
    }
    return root;
}

Nodo* searchNode(Nodo* root, int data){
    int* encontrou = 0;
    if(root != NULL){
        if(root->data == data){
            return root;
        }else{
            if(data > root->data){
                return searchNode(root->right,data);
                
            }else{
                return searchNode(root->left,data);
                
            }
        }
    }
    return NULL;
}

void printTree(Nodo* root){
    if(root != NULL){
        printf("%d ",root->data);
        printTree(root->left);
        printTree(root->right);
    }
}

void verify(Nodo* temp){
    if(temp == NULL){
        printf("\nElemento nao encontrado");
    }else{
        printf("\nElemento encontrado -> %d",temp->data);
    }
}

int main(){
    int inserir;
    Nodo* root = inicialize();
    
    printf("Digite o numero que desenha inserir\n");
    scanf("%d",&inserir);
    root = insertNode(root,inserir);

    printf("Digite o numero que desenha inserir\n");
    scanf("%d",&inserir);
    root = insertNode(root,inserir);

    root = insertNode(root,10);
    root = insertNode(root,7);
    root = insertNode(root,12);
    root = insertNode(root,22); 
    root = insertNode(root,3);
   
   printTree(root);

    Nodo* temp = searchNode(root,22);
    verify(temp);
    
    return 0;
}