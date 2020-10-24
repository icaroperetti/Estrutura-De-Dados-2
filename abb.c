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
    if(root != NULL){
        if(data > root->data){
            root->right = delete(root->right,data);
        }else if (data < root->data){
            root->left = delete(root->left,data);
        }else{
            //Se o nó não tiver nenhum filho, da um free
            if((root->left == NULL) && (root->right == NULL)){
                free(root);
                return NULL;
            }else{
                //Se tiver filho a direita, guarda em uma variavel auxiliar
                //e da um free no pai e retorna o aux que ocupa o lugar vazio
                if(root->left == NULL && root->right != NULL){
                   Nodo* aux = root->right;
                   free(root); 
                   return aux;
                }else{
                    //Se tiver filho a esquerda, guarda em uma variavel auxiliar
                    //e da um free no pai e retorna o aux que ocupa o lugar vazio
                    if(root->right == NULL && root->left != NULL ){
                        Nodo* aux = root->left;
                        free(root);
                        return aux;
                    }else{
                        Nodo* aux = searchMin(root); //Buscando menor valor da arvore
                        Nodo* keep = aux->data; //Faz uma copia do menor valor da arvore
                        root = delete(root,keep->data);
                        root->data = keep;
                    }
                }
            }
        }
        return root;
    }
    return NULL;
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

    root = insertNode(root,10);
    root = insertNode(root,7);
    root = insertNode(root,12);
    root = insertNode(root,22); 
    root = insertNode(root,3);
    
    root = delete(root,22);

    printTree(root);

    Nodo* temp = searchNode(root,22);
    verify(temp);
    
    return 0;
}