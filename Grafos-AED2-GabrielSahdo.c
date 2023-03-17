//Gabriel Sobrinho Sahdo - 21850589

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define true 1
#define false 0

typedef int bool;
typedef int typepeso;

struct st_adjacencia{
	int vertice;
	typepeso peso;
	struct st_adjacencia *prox;
};

typedef struct st_adjacencia adjacencia;

struct st_vertice{
	adjacencia *head;
};

typedef struct st_vertice vertice;

typedef struct st_grafo{
	int vertices;
	int arestas;
	vertice *adj;
}grafo;

struct st_matrizstrings{
	char array[7];
};

typedef struct st_matrizstrings matrizstring;

grafo *criaGrafo (int v) {
	int i;

	grafo *g = (grafo *)malloc(sizeof(grafo)); //aloca espaço para estrtura grafo
	g->vertices = v; //atualizo o numero de vertice
	g->arestas = 0;  //atualizo o numero de vertice
	g->adj = (vertice *)malloc(v*sizeof(vertice)); //ler abaixo
	//Dentro da estrturua tem só o arranjo para o ponteiro de vertice, não o arranjo em si
	// então aloco o arranjo com (v) o numero de vertice desejado
	for (i=0; i<v; i++){
		g->adj[i].head=NULL; //coloco NULL em todas arestas
	}
	return(g);
}


adjacencia *criaAdj(int v, int peso){
	adjacencia *temp = (adjacencia *) malloc (sizeof(adjacencia)); //aloca espaço para um nó
	temp->vertice =v; //vertice alvo da adjacencia
	temp->peso = peso; //peso da aresta
	temp->prox = NULL;
	return(temp); //retorno endereço da adjacencia
}

bool criaAresta(grafo *gr, int vi, int vf, typepeso p) { //vai de vi a vf
	if(!gr) return (false);  //validações se o grafo existe
	if((vf<0)||(vf >= gr->vertices))return(false); //validações se os valores não são neg
	if((vi<0)||(vf >= gr->vertices))return(false); //ou maiores que o numero de vértice do grafo

	adjacencia *novo = criaAdj(vf,p); //crio adjacencia com o vértice final e o peso
	//coloco a adjacencia na lista do vértice inicial
	novo->prox = gr->adj[vi].head; //o campo prox da adjacencia vai receber a cabeça da lista
	gr->adj[vi].head=novo; // e a cabeça da lista passa a ser o novo elemento
	gr->arestas++; // atualizo o numero de aresta no grafo
	return (true);
}

void imprime(grafo *gr,matrizstring *array){

	printf("Vertices: %d. Arestas: %d. \n",gr->vertices,gr->arestas); //imprime numero de vértice e arestas
	int i;



	for(i=0; i<gr->vertices; i++){
		printf("%s: ",array[i].array); //Imprimo em qual aresta estou
		adjacencia *ad = gr->adj[i].head; //chamo a cabeça da lista de adjacencia desta aresta
			while(ad){ //enquanto as adjacencias não forem nula
				printf("%s(%d) ",array[ad->vertice].array,ad->peso); //imprimo a adjacencia e seu peso
				ad = ad->prox; //passo para proxima adjacencia
			}
		printf("\n");
	}
}

void inicializaDjik(grafo *g, int *d, int *p, int s){
	int v;
	for (v=0;v<g->vertices;v++){
		d[v] = INT_MAX/2;
		p[v] = -1;

	}
	d[s] = 0;
}

void relax(grafo *g, int *d, int *p, int u, int v){
	adjacencia *ad = g->adj[u].head;
	while (ad && ad->vertice != v)
		ad = ad->prox;
	if (ad){
		if (d[v] > d[u] + ad->peso){
			d[v] = d[u] + ad->peso;
			p[v] = u;
		}
	}
}

bool existeAberto(grafo *g, int *aberto){
	int i;
	for (i=0;i<g->vertices;i++)
		if (aberto[i]) return (true);
	return(false);
}

int menorDist(grafo *g,int *aberto, int*d){
	int i;
	for (i=0; i<g->vertices; i++)
		if (aberto[i]) break;
	if (i==g->vertices) return(-1);
	int menor = i;
	for (i=menor+1; i<g->vertices; i++)
		if(aberto[i] && (d[menor]>d[i]))
			menor = i;
	return(menor);
}

int *dijkstra(grafo *g,int s){
	int *d = (int *) malloc(g->vertices* sizeof(int));
	int p[g->vertices];
	bool aberto[g->vertices];
	inicializaDjik(g,d,p,s);

	int i;
	for (i=0; i<g->vertices;i++)
		aberto[i] = true;

	while (existeAberto(g,aberto)){
		int u = menorDist(g,aberto,d);
		aberto[u] = false;
		adjacencia *ad = g->adj[u].head;
		while (ad){
			relax(g,d,p,u,ad->vertice);
			ad = ad->prox;
		}
	}
	return(d);
}

int main(void){
	int j;
	printf("Digite um índice de acordo com o estado correspondente:\nAC = 0\nRO = 1\nRS = 2\nSC = 3\nDF = 4\nSP = 5\nPR = 6\nMT = 7\nMS = 8\nGO = 9\nTO = 10\nMG = 11\nAM = 12\nAP = 13\nRR = 14\nPA = 15\nCE = 16\nMA = 17\nRN = 18\nPB_JPA = 19\nPB_CGE = 20\nRJ = 21\nES = 22\nBA = 23\nSE = 24\nAL = 25\nPI = 26\nPE = 27\n");
	scanf("%d", &j);

	grafo *gr = criaGrafo(28);
		criaAresta(gr, 0, 1, 2);
		criaAresta(gr, 1, 0, 2);
		criaAresta(gr, 0, 4, 4);
		criaAresta(gr, 4, 0, 4);
		criaAresta(gr, 9, 4, 6);
		criaAresta(gr, 4, 9, 6);
		criaAresta(gr, 1, 7, 2);
		criaAresta(gr, 7, 1, 2);
		criaAresta(gr, 7, 9, 2);
		criaAresta(gr, 9, 7, 2);
		criaAresta(gr, 7, 8, 6);
		criaAresta(gr, 8, 7, 6);
		criaAresta(gr, 6, 8, 6);
		criaAresta(gr, 8, 6, 6);
		criaAresta(gr, 3, 6, 9);
		criaAresta(gr, 6, 3, 9);
		criaAresta(gr, 2, 6, 5);
		criaAresta(gr, 6, 2, 5);
		criaAresta(gr, 5, 6, 8);
		criaAresta(gr, 6, 5, 8);
		criaAresta(gr, 3, 5, 5);
		criaAresta(gr, 5, 3, 5);
		criaAresta(gr, 5, 4, 15);
		criaAresta(gr, 4, 5, 15);
		criaAresta(gr, 5, 11, 40);
		criaAresta(gr, 11, 5, 40);
		criaAresta(gr, 5, 16, 70);
		criaAresta(gr, 16, 5, 70);
		criaAresta(gr, 4, 10, 12);
		criaAresta(gr, 10, 4, 12);
		criaAresta(gr, 4, 21, 20);
		criaAresta(gr, 21, 4, 20);
		criaAresta(gr, 4, 11, 9);
		criaAresta(gr, 11, 4, 9);
		criaAresta(gr, 4, 16, 17);
		criaAresta(gr, 16, 4, 17);
		criaAresta(gr, 10, 15, 30);
		criaAresta(gr, 15, 10, 30);
		criaAresta(gr, 11, 21, 19);
		criaAresta(gr, 21, 11, 19);
		criaAresta(gr, 11, 23, 6);
		criaAresta(gr, 23, 11, 6);
		criaAresta(gr, 23, 24, 5);
		criaAresta(gr, 24, 23, 5);
		criaAresta(gr, 23, 22, 4);
		criaAresta(gr, 22, 23, 4);
		criaAresta(gr, 22, 21, 7);
		criaAresta(gr, 21, 22, 7);
		criaAresta(gr, 24, 25, 4);
		criaAresta(gr, 25, 24, 4);
		criaAresta(gr, 15, 17, 6);
		criaAresta(gr, 17, 15, 6);
		criaAresta(gr, 12, 14, 7);
		criaAresta(gr, 14, 12, 7);
		criaAresta(gr, 14, 16, 8);
		criaAresta(gr, 16, 14, 8);
		criaAresta(gr, 17, 16, 10);
		criaAresta(gr, 16, 17, 10);
		criaAresta(gr, 16, 18, 9);
		criaAresta(gr, 18, 16, 9);
		criaAresta(gr, 18, 19, 7);
		criaAresta(gr, 19, 18, 7);
		criaAresta(gr, 18, 20, 15);
		criaAresta(gr, 20, 18, 15);
		criaAresta(gr, 19, 20, 7);
		criaAresta(gr, 20, 19, 7);
		criaAresta(gr, 27, 20, 9);
		criaAresta(gr, 20, 27, 9);
		criaAresta(gr, 26, 17, 5);
		criaAresta(gr, 17, 26, 5);
		criaAresta(gr, 25, 26, 7);
		criaAresta(gr, 26, 25, 7);
		criaAresta(gr, 12, 13, 4);
		criaAresta(gr, 13, 12, 4);
		criaAresta(gr, 13, 15, 7);
		criaAresta(gr, 15, 13, 7);
		criaAresta(gr, 23, 27, 11);
		criaAresta(gr, 27, 23, 11);
		criaAresta(gr, 25, 27, 5);
		criaAresta(gr, 27, 25, 5);





		matrizstring *array;
		array = malloc(28*sizeof(matrizstring));
		strcpy(array[0].array,"AC");
		strcpy(array[1].array,"RO");
		strcpy(array[2].array,"RS");
		strcpy(array[3].array,"SC");
		strcpy(array[4].array,"DF");
		strcpy(array[5].array,"SP");
		strcpy(array[6].array,"PR");
		strcpy(array[7].array,"MT");
		strcpy(array[8].array,"MS");
		strcpy(array[9].array,"GO");
		strcpy(array[10].array,"TO");
		strcpy(array[11].array,"MG");
		strcpy(array[12].array,"AM");
		strcpy(array[13].array,"AP");
		strcpy(array[14].array,"RR");
		strcpy(array[15].array,"PA");
		strcpy(array[16].array,"CE");
		strcpy(array[17].array,"MA");
		strcpy(array[18].array,"RN");
		strcpy(array[19].array,"PB_JPA");
		strcpy(array[20].array,"PB_CGE");
		strcpy(array[21].array,"RJ");
		strcpy(array[22].array,"ES");
		strcpy(array[23].array,"BA");
		strcpy(array[24].array,"SE");
		strcpy(array[25].array,"AL");
		strcpy(array[26].array,"PI");
		strcpy(array[27].array,"PE");

		imprime(gr,array);



		int *r = dijkstra(gr,j);

		int i;
		for (i=j;i<gr->vertices;i++)
			printf("D(%s -> %s) = %d\n", array[j].array, array[i].array, r[i]);

	return 0;
}
