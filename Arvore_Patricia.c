// Gabriel Sobrinho Sahdo - 21850589

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArvorePatricia{
    int ind;
    char comparar;
    int prefixo;
    char palavra[27];
    struct ArvorePatricia *pai;
    struct ArvorePatricia *esq, *dir;
} ArvorePatricia;

ArvorePatricia *criarNo(ArvorePatricia *pai, int ind, char palavra[27]){
    ArvorePatricia *no = malloc(sizeof(ArvorePatricia));
    no->pai = pai;
    no->comparar = palavra[0];
    no->ind = ind;
    no->esq = malloc(sizeof(ArvorePatricia));
    no->dir = malloc(sizeof(ArvorePatricia));
    no->esq->pai = no;
    no->dir->pai = no;
    strcpy(no->esq->palavra, palavra);
    no->esq->prefixo = 1;
    no->dir->prefixo = 0;
    return no;
}

void mostrarArvore(ArvorePatricia *arv){ // Exibe arvore da palavra mais a esquerda pra palavra mais a direita
    if (arv != NULL){
        if (arv->esq->prefixo == 2)
            mostrarArvore(arv->esq);
        else if (arv->esq->prefixo == 1)
            puts(arv->esq->palavra);
        if (arv->dir->prefixo == 2)
            mostrarArvore(arv->dir);
        else if (arv->dir->prefixo == 1)
            puts(arv->dir->palavra);
    }
}

ArvorePatricia *buscarArvore(ArvorePatricia *arv, char palavra[27], int cont){ // Busca de uma palavra na arvore que retorna o no associado a ela
    if ((arv->esq->prefixo == 1 && strcmp(arv->esq->palavra, palavra) == 0) || (arv->dir->prefixo == 1 && strcmp(arv->dir->palavra, palavra) == 0)){
        return arv;
    } else {
        if (palavra[cont-1] > arv->comparar)
            return buscarArvore(arv->dir, palavra, cont + arv->dir->ind);
        else
            return buscarArvore(arv->esq, palavra, cont + arv->esq->ind);
    }
}

ArvorePatricia *insereEsquerdo(ArvorePatricia *arv, char palavra[27], int cont){
    ArvorePatricia *novoNo;
    int i = 0, posicaoLetraDiferente = 0, achouLetraDiferente = 0;
    while (i < strlen(palavra) && achouLetraDiferente == 0){
        if (palavra[i] != arv->esq->palavra[i]){
            posicaoLetraDiferente = i;
            achouLetraDiferente = 1;
        } else
            i++;
    }
    int indNovoNo = posicaoLetraDiferente + 1 - cont;
    if (palavra[posicaoLetraDiferente] <= arv->esq->palavra[posicaoLetraDiferente]){
        novoNo = criarNo(arv, indNovoNo, palavra);
        strcpy(novoNo->dir->palavra, arv->esq->palavra);
        novoNo->dir->prefixo = 1;
        novoNo->prefixo = 2;
    } else {
        novoNo = criarNo(arv, indNovoNo, arv->esq->palavra);
        strcpy(novoNo->dir->palavra, palavra);
        novoNo->dir->prefixo = 1;
        novoNo->prefixo = 2;
    }
    /*printf("Palavra esquerda do novo no: ");
    puts(novoNo->esq->palavra);
    printf("Palavra direita do novo no: ");
    puts(novoNo->dir->palavra); */
    return novoNo;
}

ArvorePatricia *insereDireito(ArvorePatricia *arv, char palavra[27], int cont){
    ArvorePatricia *novoNo;
    int i = 0, posicaoLetraDiferente = 0, achouLetraDiferente = 0;
    while (i < strlen(palavra) && achouLetraDiferente == 0){
        if (palavra[i] != arv->dir->palavra[i]){
            posicaoLetraDiferente = i;
            achouLetraDiferente = 1;
        } else
            i++;
    }
    int indNovoNo = posicaoLetraDiferente + 1 - cont;
    if (palavra[posicaoLetraDiferente] <= arv->dir->palavra[posicaoLetraDiferente]){
        novoNo = criarNo(arv, indNovoNo, palavra);
        strcpy(novoNo->dir->palavra, arv->dir->palavra);
        novoNo->dir->prefixo = 1;
        novoNo->prefixo = 2;
    } else {
        novoNo = criarNo(arv, indNovoNo, arv->dir->palavra);
        strcpy(novoNo->dir->palavra, palavra);
        novoNo->dir->prefixo = 1;
        novoNo->prefixo = 2;
    }
    /*printf("Palavra esquerda do novo no: ");
    puts(novoNo->esq->palavra);
    printf("Palavra direita do novo no: ");
    puts(novoNo->dir->palavra); */
    return novoNo;
}

ArvorePatricia *insereMeioEsq(ArvorePatricia *arv, char palavra[27], int cont){
    //printf("Inserir entre no esquerdo\n");
    ArvorePatricia *novoNo;
    if (palavra[cont] < arv->esq->esq->palavra[cont] || palavra[cont] < arv->esq->dir->palavra[cont]){ // vai inserir entre a arv e o filho
        novoNo = criarNo(arv, arv->esq->ind-arv->ind, palavra);
        novoNo->prefixo = 2;
        novoNo->dir = arv->esq;
        novoNo->dir->prefixo = 2;
        novoNo->dir->pai = novoNo;
    } else {
        novoNo = criarNo(arv, arv->esq->ind-arv->ind, palavra);
        novoNo->comparar = arv->esq->dir->palavra[cont];
        strcpy(novoNo->dir->palavra, novoNo->esq->palavra);
        novoNo->prefixo = 2;
        novoNo->dir->prefixo = 1;
        novoNo->esq = arv->esq;
        novoNo->esq->prefixo = 2;
        novoNo->esq->pai = novoNo;
    }
    /*ArvorePatricia *novoNo = criarNo(arv, cont-1, palavra);
    novoNo->prefixo = 2;
    novoNo->dir = arv->esq;
    novoNo->dir->prefixo = 2;
    novoNo->dir->pai = novoNo; */
    return novoNo;
}

ArvorePatricia *insereMeioDir(ArvorePatricia *arv, char palavra[27], int cont){
    printf("Inserir entre no direito\n");
    ArvorePatricia *novoNo;
    if (palavra[cont-arv->ind] < arv->dir->esq->palavra[cont-arv->ind] || palavra[cont-arv->ind] < arv->dir->dir->palavra[cont-arv->ind]){ // vai inserir entre a arv e o filho
        novoNo = criarNo(arv, arv->dir->ind-cont, palavra);
        puts(novoNo->esq->palavra);
        novoNo->prefixo = 2;
        novoNo->dir = arv->dir;
        novoNo->dir->prefixo = 2;
        novoNo->dir->pai = novoNo;
    } else { // vai inserir depois do filho
        novoNo = criarNo(arv, arv->dir->ind-cont, palavra);
        novoNo->comparar = arv->dir->dir->palavra[arv->ind];
        strcpy(novoNo->dir->palavra, novoNo->esq->palavra);
        novoNo->prefixo = 2;
        novoNo->dir->prefixo = 1;
        novoNo->esq = arv->dir;
        novoNo->esq->prefixo = 2;
        novoNo->esq->pai = novoNo;
    }
    return novoNo;
}

ArvorePatricia *insereArvore(ArvorePatricia *arv, char palavra[27], int cont){
    if (arv == NULL)
        return criarNo(NULL, 1, palavra);
    else {
        if (palavra[cont-1] == arv->comparar){ // vai para sub-arvore esquerda e verifica qual caso do no esquerdo
            if (arv->esq->prefixo == 1){
                arv->esq = insereEsquerdo(arv, palavra, cont);
                //printf("Inseriu caso E\n");
            } else if (arv->esq->prefixo == 2){ // olha pro filho esquerdo
                if (arv->esq->ind > cont-1 && palavra[cont-1] != arv->esq->dir->palavra[cont-1]){ // verifica se precisa inserir entre o no e o filho E
                    arv->esq = insereMeioEsq(arv, palavra, cont);
                } else {
                    cont += arv->esq->ind;
                    arv->esq = insereArvore(arv->esq, palavra, cont);
                }
            } else if (arv->esq->prefixo == 2){
                strcpy(arv->esq->palavra, palavra);
                arv->esq->prefixo = 1;
                //printf("Palavra inserida: ");
                //puts(arv->esq->palavra);
                //printf("Inseriu caso N\n");
            }
        }else if (palavra[cont-1] < arv->comparar)
        {
            printf("palavra de letra menor q \n");
        }
        else { // vai para sub arvore direita e verifica qual caso do no direito
            if (arv->dir->prefixo == 1){
                arv->dir = insereDireito(arv, palavra, cont);
                //printf("Inseriu caso E\n");
            } else if (arv->dir->prefixo == 2){ // olha pro filho direito
                if (arv->dir->ind > cont-1 && palavra[cont-1] != arv->dir->dir->palavra[cont-1]){ // verifica se precisa inserir entre o no e o filho D
                    arv->dir = insereMeioDir(arv, palavra, cont);
                } else {
                    cont += arv->dir->ind;
                    arv->dir = insereArvore(arv->dir, palavra, cont);
                }
            } else if (arv->dir->prefixo == 2){
                strcpy(arv->dir->palavra, palavra);
                arv->dir->prefixo = 1;
                //printf("Palavra inserida: ");
                //puts(arv->dir->palavra);
                //printf("Inseriu caso N\n");
            }
        }
        return arv;
    }
}

void atualizarindices(ArvorePatricia *arv, int indsoma){
    if (arv->esq->prefixo == 2)
        atualizarindices(arv->esq, indsoma);
    arv->ind += indsoma;
    if (arv->dir->prefixo == 2)
        atualizarindices(arv->dir, indsoma);
}

ArvorePatricia *removeArvore(ArvorePatricia *arv, char palavra[27], int cont){
    ArvorePatricia *noAux = buscarArvore(arv, palavra, cont); // noAux eh o no pai ao qual esta associado a palavra que se deseja remover
    if (noAux != NULL){ // a palavra esta na arvore
        if (noAux->esq->prefixo == noAux->dir->prefixo){ // o noAux ta ligado em duas palavras
            if (strcmp(noAux->esq->palavra, palavra) == 0){ // a palavra ta do lado esquerdo
                strcpy(noAux->esq->palavra, "");
                noAux->esq->prefixo = 2;
            } else { // a palavra ta do lado direito
                strcpy(noAux->dir->palavra, "");
                noAux->dir->prefixo = 2;
            }
        } else if (noAux->esq->prefixo == 2 || noAux->dir->prefixo == 2){ // o noAux ta ligado em uma palavra apenas
            if (strcmp(noAux->esq->palavra, palavra) == 0){ // a palavra ta do lado direito
                strcpy(noAux->esq->palavra, "");
                noAux->esq->prefixo = 2;
            } else {
                strcpy(noAux->dir->palavra, "");
                noAux->dir->prefixo = 2;
            }
            //if (noAux->pai == NULL) // apagar a arv
            free(noAux);
        } else { // no ligado a uma palavra (que se deseja remover) e a um outro no
            if (strcmp(noAux->esq->palavra, palavra) == 0){ // palavra ta do lado esquerdo e existe um no do lado direito
                if (noAux->pai->esq == noAux) // noAux eh o filho esquerdo do pai e o filho esquerdo aponta pro filho direito do no buscado
                    noAux->pai->esq = noAux->dir;
                else  // noAux eh o filho direito do pai e o filho direito aponta pro filho direito do no buscado
                    noAux->pai->dir = noAux->dir;
                atualizarindices(noAux->dir, noAux->ind);
                noAux->dir->pai = noAux->pai;
            } else { // palavra ta do lado direito e existe um no do lado esquerdo
                if (noAux->pai->esq == noAux)
                    noAux->pai->esq = noAux->esq;
                else
                    noAux->pai->dir = noAux->esq;
                atualizarindices(noAux->esq, noAux->ind);
                noAux->esq->pai = noAux->pai;
            }
            free(noAux); // libera o espaco do no
        }
    }
    return noAux;
}

int main(){
    int op;
    char palavra[27];
    ArvorePatricia *noAux, *noAuxRemove;
    printf("Palavra da arv: ");
    gets(palavra);
    ArvorePatricia *arv = criarNo(NULL, 1, palavra);
    printf("arv criada com a palavra: ");
    puts(arv->esq->palavra);
    printf("1 - Inserir\n 2 - Mostrar arvore\n 3 - Remover palavra\n, outros numeros - encerrar programa\n");
    scanf("%d",&op);
    while (op>=1 && op<4)
    {
        if (op==1)
        {
           // printf("Palavra nova: ");
            fflush(stdin);
            scanf("%s",palavra);
            arv = insereArvore(arv, palavra, 1);
        }
        else if (op==2)
        {
            printf("\nPalavras inseridas na arvore:\n");
            mostrarArvore(arv);
        }
        else if (op==3)
        {
            printf("\nPalavra pra ser removida: ");
            gets(palavra);
            noAuxRemove = removeArvore(arv, palavra, 1);
            /*printf("Palavra pra ser removida: ");
            gets(palavra);
            noAuxRemove = removeArvore(arv, palavra, 1);
            printf("Palavra pra ser removida: ");
            gets(palavra);
            noAuxRemove = removeArvore(arv, palavra, 1);
            */
            printf("\nPalavras na arvore apos a remocao:\n");
            mostrarArvore(arv);

        }
        scanf("%d",&op);
    }

    return 0;
}
