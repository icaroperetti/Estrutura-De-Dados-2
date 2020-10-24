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

void printInOrder(Nodo* root){
    if (root != NULL){
        printTree(root->left);
        printf("%d ", root->data);
        printTree(root->right);
    }
}

void found(Nodo* temp){
    if(temp == NULL){
        printf("\nElemento nao encontrado");
    }else{
        printf("\nElemento encontrado -> %d",temp->data);
    }
}

Nodo* searchMin(Nodo* root){
    if(root != NULL){
        Nodo* aux = root;
        while(root->left != NULL){
            aux = aux->left;
            return aux;
        }
    }
    return NULL;
}

Nodo* delete(Nodo* root,int data){
    if(root == NULL){
        return root;
    }
    if(data < root->data){
        root->left = delete(root->left, data); 
    } else if(data > root->data){
        root->right = delete(root->right,data);
    }
    else{
        if(root->right == NULL){
            Nodo* temp = root->left;
            free(root);
            return temp;

        }else if(root->left == NULL){
            Nodo* temp = root->right;
            free(root);
            return temp;
        } else{
            Nodo* aux = searchMin(root->left);
            root->data = aux->data;
            root->left = delete(root->left,aux->data);
        }
    }
    return root;
}

int main(){
    int inserir;
    Nodo* root = inicialize();

    // printf("Digite o numero que desenha inserir\n");
    // scanf("%d",&inserir);
    // root = insertNode(root,inserir);

    // printf("Digite o numero que desenha inserir\n");
    // scanf("%d",&inserir);
    // root = insertNode(root,inserir);

    root = insertNode(root,50);
    root = insertNode(root,20);
    root = insertNode(root,30);
    root = insertNode(root,22); 
    root = insertNode(root,3);
    
    root = delete(root,50);
    
    printTree(root);
    printf("\n");
    printInOrder(root);

    Nodo* temp = searchNode(root,12);
    found(temp);
    
    return 0;
}
