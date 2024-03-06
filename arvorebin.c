#include <stdio.h>
#include <stdlib.h>



typedef struct no{
    int valor;
    struct no *direita, *esquerda;
}NoArv;


//inserir valores na arvore
NoArv* inserir_versao_1(NoArv *raiz, int num){
    if(raiz == NULL){
        NoArv *aux = malloc(sizeof(NoArv));
        aux->valor = num;
        aux->esquerda = NULL;
        aux->direita = NULL;
        return aux;
    }
    else{
        if(num < raiz->valor)
            raiz->esquerda = inserir_versao_1(raiz->esquerda, num);
        else
            raiz->direita = inserir_versao_1(raiz->direita, num);
        return raiz;
    }
}
//buscar valores na arvore
NoArv* buscar_versao_1(NoArv *raiz, int num){
    if(raiz){
        if(num == raiz->valor)
            return raiz;
        else if(num < raiz->valor)
            return buscar_versao_1(raiz->esquerda, num);
        else
            return buscar_versao_1(raiz->direita, num);
    }
    return NULL;
}

//altura da arvore
int altura(NoArv *raiz){
    if(raiz == NULL)
        return -1;
    else{
        int esq = altura(raiz->esquerda);
        int dir = altura(raiz->direita);
        if(esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }
}

//qtd de nós da arvore
int qtd_no(NoArv *raiz){
    if(raiz == NULL)
        return 0;
    else
        return 1 + qtd_no(raiz->esquerda) + qtd_no(raiz->direita);
}

//qtd de folhas de uma arvore
int qtd_folhas(NoArv *raiz){
    if(raiz == NULL)
        return 0;
    else if(raiz->esquerda == NULL && raiz->direita == NULL)
        return 1;
    else
        return qtd_folhas(raiz->esquerda) + qtd_folhas(raiz->direita);
}

//imprimimir arvore
void imprimir_versao_1(NoArv *raiz){
    if(raiz){
        printf("%d ", raiz->valor);
        imprimir_versao_1(raiz->esquerda);
        imprimir_versao_1(raiz->direita);
    }/*else
        printf("Arvore vazia...");
    */
}

//imprimir ordenado
void imprimir_versao_2(NoArv *raiz){
    if(raiz){
        imprimir_versao_2(raiz->esquerda);
        printf("%d ", raiz->valor);
        imprimir_versao_2(raiz->direita);
    }/*else
        printf("Arvore vazia...");
    */
}


//remover uma folha 
NoArv* remover(NoArv *raiz, int chave) {
    if(raiz == NULL){
        printf("Valor nao encontrado!\n");
        return NULL;
    } else { // procura o nó a remover
        if(raiz->valor == chave) {
            // remove nós folhas (nós sem filhos)
            if(raiz->esquerda == NULL && raiz->direita == NULL) {
                free(raiz);
                printf("Elemento folha removido: %d !\n", chave);
                return NULL;
            }
            else{
                // remover nós que possuem 1 ou 2 filhos
                if(raiz->esquerda != NULL && raiz->direita != NULL){// no que possue dois filhos
                    NoArv *aux = raiz->esquerda;
                    while(aux->direita != NULL)
                        aux = aux->direita;
                    raiz->valor = aux->valor;
                    aux->valor = chave;
                    printf("\nElemento trocado: %d !\n",chave);
                    raiz->esquerda = remover(raiz->esquerda, chave);
                    return raiz;
                }else{//remover no que tem 1 filho
                    NoArv *aux;
                    if(raiz->esquerda != NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;
                    free(raiz);
                    printf("O elemento com 1 filho foi removido: %d !\n",chave);
                    return aux;
                }
            }
        } else {
            if(chave < raiz->valor)
                raiz->esquerda = remover(raiz->esquerda, chave);
            else
                raiz->direita = remover(raiz->direita, chave);
            return raiz;
        }
    }
}


int main(){

    NoArv *busca,*raiz = NULL;
    int opcao, valor;

    do{
        printf("\nMenu para uma Arvore Binaria, escholha sua opcao:\n");
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Buscar\n\t4 - Altura\n\t5 - Tamanho\n\t6 - Folhas\n\t7 - Remover\n");
        printf("\nSua opcao e: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 0:
                printf("\n\tSaindo...\n");
                break;
            case 1:
                printf("\n\tDigite um valor: ");
                scanf("%d", &valor);
                raiz = inserir_versao_1(raiz, valor);
                break;
            case 2:
                printf("\nPrimeira impresao:\n");
                imprimir_versao_1(raiz);
                printf("\n");
                printf("\nimpresao ordenada:\n");
                imprimir_versao_2(raiz);
                printf("\n");
                break;
            case 3:
                printf("\n\tDigite o valor a ser procurado: ");
                scanf("%d", &valor);
                busca = buscar_versao_1(raiz, valor);
                if(busca)
                    printf("\n\tValor encontrado: %d\n", busca->valor);
                else
                    printf("\n\tValor nao encontrado!\n");
                break;
            case 4: 
                printf("\n\tA altura da arvore e: %d\n\n",altura(raiz));
                break;
            case 5:
                printf("\n\tA quantidade de nos da arvore e: %d\n",qtd_no(raiz));
                break;
            case 6:
                printf("\n\tA quantidade de folhas da arvore e: %d\n",qtd_folhas(raiz));
                break;
            case 7:
                printf("\t");
                imprimir_versao_2(raiz);
                printf("\ninsira o valor a ser removido: ");
                scanf("%d",&valor);
                raiz = remover(raiz, valor);
                break;
            default:
                if(opcao != 0)
                    printf("\n\tOpcao invalida!!!\n");
        }
        printf("\nPressione qualquer tecla para continuar...\n");
        getchar(); // Para limpar o buffer de entrada
        getchar(); // Para aguardar a entrada do usuário
        system("clear");
    }while(opcao != 0);

    return 0;
}