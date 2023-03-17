//Aluno: Gabriel Sobrinho Sahdo - 21850589
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct st_cliente{
	int hora;
	int min;
	char placa[8];
	char classe;

};

typedef struct st_cliente cliente;

struct st_estacionamento{
	cliente carro;
	int alt;
	struct st_estacionamento *leftside;
	struct st_estacionamento *rightside;
};

typedef struct st_estacionamento estacionamento;

estacionamento* criaEstacionamento(){

	return NULL;

}

int EstacionamentoVazio(estacionamento* t){
	return t == NULL;
}

void mostraEstacionamento(estacionamento* t){

	if (!EstacionamentoVazio(t)){

		printf("%d, %d, %s, %c\n %d\n", t->carro.hora,t->carro.min,t->carro.placa,t->carro.classe,t->alt);
		mostraEstacionamento(t->leftside);
		mostraEstacionamento(t->rightside);

	}

}

int alt_NO (estacionamento* no){
	if(no == NULL){
		return -1;
	}
	else{
		return no->alt;
	}


}

int fatorBalanceamento(estacionamento* no){
	return labs(alt_NO(no->leftside) - alt_NO(no->rightside));
}

int maior(int x, int y){
	if(x > y){
		return x;
	}
	else{
		return y;
	}
}

void RotacaoSimplesDireita(estacionamento *raiz){//Rotação Simples Pra Direita da AVL
	estacionamento *no;
	no = raiz->leftside;
	raiz->leftside = no->rightside;
	no->rightside = raiz;
	raiz->alt = maior(alt_NO(raiz->leftside),alt_NO(raiz->rightside)) + 1;

	no->alt = maior(alt_NO(no->leftside),raiz->alt) + 1;
	raiz = no;
}

void RotacaoSimplesEsquerda(estacionamento *raiz){//Rotação Simples Pra Esquerda da AVL
	estacionamento *no;
	no = raiz->rightside;
	raiz->rightside = no->leftside;
	no->leftside = raiz;
	raiz->alt = maior(alt_NO(raiz->leftside),alt_NO(raiz->rightside)) + 1;

	no->alt = maior(alt_NO(no->rightside),raiz->alt) + 1;
	raiz = no;
}

void RotacaoDuplaDireita(estacionamento *raiz){//Rotação Dupla Pra Direita da AVL
	RotacaoSimplesEsquerda(raiz->leftside);
	RotacaoSimplesDireita(raiz);
}

void RotacaoDuplaEsquerda(estacionamento *raiz){//Rotação Dupla Pra Esquerda da AVL
	RotacaoSimplesDireita(raiz->rightside);
	RotacaoSimplesEsquerda(raiz);
}

int insereEstacionamento(estacionamento** raiz, cliente valor){//Insere Carro no Estacionamento
	int res;
	if (*raiz == NULL){
		estacionamento *novo;
		novo = (estacionamento*)malloc(sizeof(estacionamento));
		if(novo == NULL){
			return 0;
		}
		novo->carro = valor;
		novo->alt = 0;
		novo->leftside = NULL;
		novo->rightside = NULL;
		*raiz = novo;
		return 1;
	}
	estacionamento *atual = *raiz;
	if(valor.hora < atual->carro.hora){
		if((res=insereEstacionamento (&(atual->leftside), valor)) == 1){
			if(fatorBalanceamento(atual) >= 2){
				if(valor.hora < (*raiz)->leftside->carro.hora){
					RotacaoSimplesDireita(*raiz);
				}else{
					RotacaoDuplaDireita(*raiz);
				}
			}
		}

	}else{
		if(valor.hora > atual->carro.hora){
			if((res = insereEstacionamento(&(atual->rightside),valor)) == 1){
				if(fatorBalanceamento(atual) >= 2){
					if((*raiz)->rightside->carro.hora < valor.hora){
						RotacaoSimplesEsquerda(*raiz);
					}else{
						RotacaoDuplaEsquerda(*raiz);
					}
				}
			}
		}if (valor.hora == atual->carro.hora){
			if(valor.min < atual->carro.min){
					if((res = insereEstacionamento(&(atual->leftside), valor)) == 1){
						if(fatorBalanceamento(atual) >= 2){
							if(valor.min < (*raiz)->leftside->carro.min){
								RotacaoSimplesDireita(*raiz);
							}else{
								RotacaoDuplaDireita(*raiz);
							}
						}
					}

				}else{
					if(valor.min > atual->carro.min){
						if((res = insereEstacionamento(&(atual->rightside),valor)) == 1){
							if(fatorBalanceamento(atual) >= 2){
								if((*raiz)->rightside->carro.min < valor.min){
									RotacaoSimplesEsquerda(*raiz);
								}else{
									RotacaoDuplaEsquerda(*raiz);
								}
							}
						}
					}else{
						return 0;
					}
				}
		}
	}
	atual->alt = maior(alt_NO(atual->leftside),alt_NO(atual->rightside)+1);
	return res;


}



int main(){
	estacionamento *shopping;
	shopping = criaEstacionamento();
	cliente carro1;
	carro1.hora = 12;
	carro1.min = 55;
	strcpy(carro1.placa,"ABC0123");
	carro1.classe = 'C';
	insereEstacionamento(&shopping,carro1);
	cliente carro2;
	carro2.hora = 11;
	carro2.min = 05;
	strcpy(carro2.placa,"ABL0124");
	carro2.classe = 'B';
	insereEstacionamento(&shopping,carro2);
	cliente carro3;
	carro3.hora = 10;
	carro3.min = 05;
	strcpy(carro3.placa,"ABL1124");
	carro3.classe = 'A';
	insereEstacionamento(&shopping,carro3);
	cliente carro4;
	carro4.hora = 9;
	carro4.min = 05;
	strcpy(carro4.placa,"AHL1224");
	carro4.classe = 'A';
	insereEstacionamento(&shopping,carro4);
	mostraEstacionamento(shopping);
	printf("%s",shopping->carro.placa);


	return 0;

}
