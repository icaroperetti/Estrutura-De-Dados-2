#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 30

/* 
    Aluno: Icaro Peretti 
    Arvore AVL
*/

typedef struct sBook
{
    int issn;
    char name[30];
} Book;

typedef struct sNode
{
    struct sNode *left;
    struct sNode *right;
    Book *book;
    int height;
} Node;

Node *inicialize()
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
        return 0;
    }
    book->issn = issn;
    strcpy(book->name, name);
    return book;
}

Node *createNode()
{
    Node *node;
    node = (Node *)malloc(sizeof(Node));

    if (node == NULL)
    {
        printf("Memoria nao alocada nodo");
        return 0;
    }
    node->left = NULL;
    node->right = NULL;
    node->book = NULL;
    node->height = 0; //Altura da sub-arvore
    return node;
}

//Calcula a altura do no
int getHeight(Node *root)
{
    if (root == NULL)
    {
        return -1;
    }
    else
    {
        return root->height;
    }
}

//Fator Balanceamento
int getBalance(Node *root)
{
    //Funão da stdlib que volta o valor absoluto
    return labs(getHeight(root->left) - getHeight(root->right));
}

//Calcula o maior valor
int maxValue(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

Node *rotateLL(Node *root)
{
    Node *aux = root->left; //Recebe o filho a esquerda do root

    //Faz a rotação
    root->left = aux->right; //O filho a esquerda do root recebe a direita do auxiliar(direita da esquerda)
    aux->right = root;       //Filho a direita do auxiliar recebe a raiz

    //Calcula a altura (maior altura + 1)
    root->height = maxValue(getHeight(root->left), getHeight(root->right)) + 1;
    aux->height = maxValue(getHeight(aux->left), getHeight(aux->right)) + 1;

    return aux;
}

Node *rotateRR(Node *root)
{
    Node *aux = root->right; //Recebe o filho a direita da raiz

    root->right = aux->left; //Recebe o filho a esquerda do auxiliar(esquerda da direita)
    aux->left = root;        //Filho a esquerda do auxiliar recebe a raiz

    //Calcula a altura (maior altura + 1)
    root->height = maxValue(getHeight(root->left), getHeight(root->right)) + 1;
    aux->height = maxValue(getHeight(aux->left), getHeight(aux->right)) + 1;

    return aux;
}


Node *insertNode(Node *root, Book *book)
{
    if (root == NULL)
    {
        Node *aux = createNode();
        aux->book = book;
        return aux;
    }
    if (book->issn < root->book->issn)
    {
        root->left = insertNode(root->left, book);
        if (getBalance(root) >= 2) //Caclula o balanceamento
        {
            //Se o valor inserido for menor que o filho da esquerda da raiz faz rotação
            if (book->issn < root->left->book->issn)
            {
                 rotateLL(root); //Rotação para a direita (left left)
            }
            else
            {
                root->left = rotateRR(root->left); //Se o valor não for maior, rotação LR(left -> right)
                return rotateLL(root);
            }
        }
    }
    else
    {
        if (book->issn > root->book->issn)
        {
            root->right = insertNode(root->right, book);
            if ((getBalance(root) >= 2))
            {
                //Se o valor inserido for maior que o filho da direita da raiz faz rotação
                if (book->issn > root->right->book->issn)
                {
                    rotateRR(root); //Rotação para a  esquerda
                }
                else
                {
                    root->right = rotateLL(root->right); //Se não é uma rotação RL(right -> left)
                    return rotateRR(root);
                }
            }
        }
    }
    //Atualiza a altura
    root->height = maxValue(getHeight(root->left), getHeight(root->right)) + 1;
    return root;
}

//----- Percursos -----

//impressão root -> esquerda -> direita
void preOrder(Node *root)
{
    if (root != NULL)
    {
        printf("ISSN:%d ", root->book->issn);
        printf("Livro:%s\n", root->book->name);
        preOrder(root->left);
        preOrder(root->right);
    }
}

//Impressão esquerda -> root-> direita
void inOrder(Node *root)
{   
    if (root != NULL)
    {   
        inOrder(root->left);
        printf("ISSN:%d ", root->book->issn);
        printf("Livro:%s\n", root->book->name);
        inOrder(root->right);
    }
}

//Impressão esquerda -> direita -> root
void postOrder(Node *root)
{
    if (root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("ISSN:%d ", root->book->issn);
        printf("Livro:%s\n", root->book->name);
    }
}


Node *searchNode(Node *root, int issn)
{
    if (root == NULL)
    {
        printf("Elemento nao encontrado");
        return -1;
    }
    else if (issn > root->book->issn)
    {
        searchNode(root->right, issn);
    }
    else if (issn < root->book->issn)
    {
        return searchNode(root->left, issn);
    }
    else if (issn == root->book->issn)
    {
        printf("\nLivro encontrado -> ISSN:%d Nome do livro:%s", root->book->issn, root->book->name);
        return root;
    }
}

Node *searchMin(Node *root)
{
    if (root != NULL)
    {
        Node *aux = root->left;
        while(aux->left != NULL)
        {
            aux = aux->left; 
        }
        return aux;
    }
    else 
    {
      return NULL;
    }
}

Node *deleteNode(Node *root, int issn)
{
    if (root == NULL)
    {
        printf("\nElemento nao encontrado para remover");
        return root;
    }
    if (issn < root->book->issn)
    {
        root->left = deleteNode(root->left, issn);
        if (getBalance(root) >= 2)
        {
            //Como nesse caso o filho da esquerda está sendo removido
            //é necessario verificar se a arvore da direita ficou desbalanceada
            //Dependendo da altura encontrada faz uma rotação a esquerda ou direita esquerda
            if (getHeight(root->right->left) <= getHeight(root->right->right))
            {
                //printf("Alturas: %d -> %d\n",root->right->left,root->right->right);
                return rotateRR(root); //Rotação esquerda (caso inserção direita direita)
            }
            else
            {
                //Rotação right -> left
                //Caso cotovelo (inserção direita esquerda)
                root->right = rotateLL(root->right); 
                return rotateRR(root);
            }
        }
    }
    else if (issn > root->book->issn)
    {
        //Como nesse caso o filho da direita está sendo removido
        //é necessario verificar se a arvore da esquerda ficou desbalanceada
        //Dependendo da altura encontrada faz uma rotação a direita ou esquerda direita
        root->right = deleteNode(root->right,issn);
        if (getBalance(root) >= 2)
        {
            if (getHeight(root->left->right) <= getHeight(root->left->left))
            {
                return rotateLL(root); //Rotação a direita (caso inserção esquerda esquerda)
            }
            else
            {
                //Rotação left -> right
                //Caso cotovelo (inserção esquerda direita)
                root->left = rotateRR(root->left); 
                return rotateRR(root);
            }
        }
    }
    else
    {
        if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        else if (root->left == NULL)
        {
           
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else
        {
           
            Node *substitute = searchMin(root->right);
            root->book = substitute->book;
            root->right = deleteNode(root->right, substitute->book->issn); //Deleta o menor valor da direita
            if(getBalance(root) >= 2 )
            {
                if(getHeight(root->left->right) <= getHeight(root->left->left))
                {
                    printf("Cheguei aqui \n");
                    return rotateLL(root); //Rotação direita
                }
                else
                {
                    //Rotação LR
                    root->left = rotateRR(root->left); 
                    return rotateLL(root);
                }
            }
        }
    }
    return root;
}



Node *destroy(Node *root)
{
    if (root != NULL)
    {
        destroy(root->left);
        destroy(root->right);
        free(root);
    }
    return NULL;
}

void menu()
{
    char name[TAM];
    int op = 0, issn = 0;
    Node *root = inicialize();

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
            scanf("%d", &issn);
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
            root = destroy(root);
        }
        if(op == 0)
        {   
            root = destroy(root);
            printf("Finalizando o programa...");
            exit(0);
        }
        if(op <= 0 || op > 7)
        {
            printf("Comando invalido");
        }
    }
}

int main()
{
    menu();
    return 0;
}
