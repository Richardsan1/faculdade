/* 
 * REPRESENTACAO DE GRAFOS - Versao 2026/1
 */
// Richard Barbosa Sanches - 10420179
// juan Nacif
// Matheus
// Mihael Xavier

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<memory.h>


/* 
 * Estrutura de dados para representar grafos
 */
typedef struct a{ /* Celula de uma lista de arestas */
	int    vizinho;
	struct a *prox;
}Aresta;

typedef struct v{  /* Cada vertice tem um ponteiro para uma lista de arestas incidentes nele */
	int nome;
	Aresta *prim;
}Vertice;

/*
 * Declaracoes das funcoes para manipulacao de grafos 
 */
void criaGrafo(Vertice **G, int ordem);
void destroiGrafo(Vertice **G, int ordem);
int  acrescentaAresta(Vertice G[], int ordem, int v1, int v2);
void imprimeGrafo(Vertice G[], int ordem);
int eConexo(Vertice G[], int ordemG);
int contaComponentesConexas(Vertice G[], int ordemG);
int listaVerticesDeCorte(Vertice G[], int ordemG, int verticesCorte[]);
int listaArestasDeCorte(Vertice G[], int ordemG, int arestaV1[], int arestaV2[]);

void marcaAlcancaveis(Vertice G[], int ordemG, int mapa[], int verticeIgnorado, int arestaIgnV1, int arestaIgnV2);
int contaComponentesComRestricao(Vertice G[], int ordemG, int verticeIgnorado, int arestaIgnV1, int arestaIgnV2);
int contaArestasNaoOrientadas(Vertice G[], int ordemG);
 

/*
 * Criacao de um grafo com ordem predefinida (passada como argumento),
 *   e, inicilamente, sem nenhuma aresta 
 */
void criaGrafo(Vertice **G, int ordem){
	int i;
	*G= (Vertice*) malloc(sizeof(Vertice)*ordem); /* Alcacao dinamica de um vetor de vertices */
	
	for(i=0; i<ordem; i++){
		(*G)[i].nome= i;
		(*G)[i].prim= NULL;    /* Cada vertice sem nenhuma aresta incidente */
	}
}

/*
 * Deasaloca a memoria dinamica usada para armazenar um grafo.
 */
void destroiGrafo(Vertice **G, int ordem){
	int i;
    Aresta *a, *n;
    
	for(i=0; i<ordem; i++){ /* Remove lista de adjacencia de cada vertice */
	    a= (*G)[i].prim;
        while (a!= NULL){
              n= a->prox;
              free(a);
              a= n;
        }
	}
    free(*G);  /* Remove o vetor de vertices */
}

/*  
 * Acrescenta uma nova aresta em um grafo previamente criado. 
 *   Devem ser passados os extremos v1 e v2 da aresta a ser acrescentada 
 * Como o grafo nao e orientado, para uma aresta com extremos i e j, quando
 *   i != j, serao criadas, na estrutura de dados, arestas (i,j) e (j,i) .
 */
int acrescentaAresta(Vertice G[], int ordem, int v1, int v2){
    Aresta *A1, *A2;
    
	if (v1<0 || v1 >= ordem) /* Testo se vertices sao validos */
	   return 0;
	if (v2<0 || v2 >= ordem)
	   return 0;
	
	/* Acrescento aresta na lista do vertice v1 */
	A1= (Aresta *) malloc(sizeof(Aresta));
	A1->vizinho= v2;
	A1->prox= G[v1].prim;
	G[v1].prim= A1;

	if (v1 == v2) return 1; /* Aresta e um laco */

	/* Acrescento aresta na lista do vertice v2 se v2 != v1 */	
	A2= (Aresta *) malloc(sizeof(Aresta));
	A2->vizinho= v1;
	A2->prox= G[v2].prim;
	G[v2].prim= A2;
	
	return 1;
}


/*  
 * Imprime um grafo com uma notacao similar a uma lista de adjacencia.
 */
void imprimeGrafo(Vertice G[], int ordem){
	int i;
	Aresta *aux;

	printf("\nOrdem:   %d",ordem);
	printf("\nLista de Adjacencia:\n");

	for (i=0; i<ordem; i++){
		printf("\n    v%d: ", i);
		aux= G[i].prim;
		for( ; aux != NULL; aux= aux->prox)
			printf("  v%d", aux->vizinho);
	}
	printf("\n\n");

}


int eConexo(Vertice G[], int ordemG) {
	/* mapa[i] = 1 significa que o vertice i foi alcancado a partir de v0 */
    int mapa[ordemG];
    memset(mapa, 0, sizeof mapa);

	/* iterado[i] = 1 significa que ja expandimos os vizinhos de i */
    int iterado[ordemG];
    memset(iterado, 0, sizeof iterado);

	/* comeca a busca pelo vertice 0 */
    mapa[0] = 1;

	/* repete a expansao enquanto existir vertice marcado e nao iterado */
    for(int i = 0; i < ordemG; i++){
        if (iterado[i] == 0 && mapa[i] == 1){
            Aresta *a = G[i].prim;

			/* marca todos os vizinhos de i como alcancaveis */
            while (a != NULL){
                mapa[a->vizinho] = 1;
                a = a->prox;
            }

            iterado[i] = 1;

			/* reinicia para verificar novos vertices que acabaram de ser marcados */
            i = 0;
        }
    }
    
	/* se algum vertice nao foi alcancado, o grafo nao e conexo */
    for (int i = 0; i < ordemG; i++){
        if (mapa[i] == 0){
            return 0;
        }
    }

	/* todos foram alcancados */
    return 1;
}


/*
 * Marca os vertices alcancaveis de acordo com o algoritmo de marcacao por arestas,
 * com opcao de ignorar um vertice ou uma aresta especifica.
 */
void marcaAlcancaveis(Vertice G[], int ordemG, int mapa[], int verticeIgnorado, int arestaIgnV1, int arestaIgnV2){
	int houveNovo;

	do{
		int i;
		houveNovo= 0;

		for(i=0; i<ordemG; i++){
			Aresta *a;

			if (i == verticeIgnorado) continue;
			if (mapa[i] == 0) continue;

			a= G[i].prim;
			while(a != NULL){
				int j= a->vizinho;
				int ignoraAresta= 0;

				if (j == verticeIgnorado){
					a= a->prox;
					continue;
				}

				if (arestaIgnV1 >= 0 && arestaIgnV2 >= 0){
					if ((i == arestaIgnV1 && j == arestaIgnV2) || (i == arestaIgnV2 && j == arestaIgnV1)){
						ignoraAresta= 1;
					}
				}

				if (!ignoraAresta && mapa[j] == 0){
					mapa[j]= 1;
					houveNovo= 1;
				}

				a= a->prox;
			}
		}
	} while(houveNovo);
}


/*
 * Conta componentes conexas aplicando opcionalmente a remocao virtual de
 * um vertice ou de uma aresta.
 */
int contaComponentesComRestricao(Vertice G[], int ordemG, int verticeIgnorado, int arestaIgnV1, int arestaIgnV2){
	int componentes= 0;
	int i, j;
	int *visitado;
	int *mapa;

	if (ordemG <= 0) return 0;

	visitado= (int*) malloc(sizeof(int) * ordemG);
	mapa= (int*) malloc(sizeof(int) * ordemG);
	if (visitado == NULL || mapa == NULL){
		if (visitado != NULL) free(visitado);
		if (mapa != NULL) free(mapa);
		return 0;
	}

	for(i=0; i<ordemG; i++){
		visitado[i]= 0;
	}
	if (verticeIgnorado >= 0 && verticeIgnorado < ordemG){
		visitado[verticeIgnorado]= 1;
	}

	for(i=0; i<ordemG; i++){
		if (visitado[i] == 1) continue;

		for(j=0; j<ordemG; j++){
			mapa[j]= 0;
		}
		mapa[i]= 1;
		marcaAlcancaveis(G, ordemG, mapa, verticeIgnorado, arestaIgnV1, arestaIgnV2);

		for(j=0; j<ordemG; j++){
			if (mapa[j] == 1){
				visitado[j]= 1;
			}
		}

		componentes++;
	}

	free(visitado);
	free(mapa);
	return componentes;
}


int contaComponentesConexas(Vertice G[], int ordemG){
	return contaComponentesComRestricao(G, ordemG, -1, -1, -1);
}


int listaVerticesDeCorte(Vertice G[], int ordemG, int verticesCorte[]){
	int i;
	int qtd= 0;
	int base= contaComponentesConexas(G, ordemG);

	for(i=0; i<ordemG; i++){
		int compsSemVertice= contaComponentesComRestricao(G, ordemG, i, -1, -1);
		if (compsSemVertice > base){
			verticesCorte[qtd]= i;
			qtd++;
		}
	}

	return qtd;
}


int contaArestasNaoOrientadas(Vertice G[], int ordemG){
	int i;
	int qtd= 0;

	for(i=0; i<ordemG; i++){
		Aresta *a= G[i].prim;
		while(a != NULL){
			if (i < a->vizinho){
				qtd++;
			}
			a= a->prox;
		}
	}

	return qtd;
}


int listaArestasDeCorte(Vertice G[], int ordemG, int arestaV1[], int arestaV2[]){
	int i;
	int qtd= 0;
	int base= contaComponentesConexas(G, ordemG);

	for(i=0; i<ordemG; i++){
		Aresta *a= G[i].prim;
		while(a != NULL){
			if (i < a->vizinho){
				int compsSemAresta= contaComponentesComRestricao(G, ordemG, -1, i, a->vizinho);
				if (compsSemAresta > base){
					arestaV1[qtd]= i;
					arestaV2[qtd]= a->vizinho;
					qtd++;
				}
			}
			a= a->prox;
		}
	}

	return qtd;
}



/*
 * Programa simples para testar a representacao de grafo
 */

int main(int argc, char *argv[]) {
    int i;
	Vertice *G;
	int qtdComponentes;
	int *verticesCorte;
	int qtdVerticesCorte;
	int qtdArestas;
	int *arestasCorteV1;
	int *arestasCorteV2;
	int qtdArestasCorte;
	int ordemG= 10; /* Vertices identificado de 0 ate 9 */
		
	criaGrafo(&G, ordemG);
	acrescentaAresta(G,ordemG,0,1);
	acrescentaAresta(G,ordemG,0,2);
	acrescentaAresta(G,ordemG,0,7);
	acrescentaAresta(G,ordemG,2,4);
	acrescentaAresta(G,ordemG,2,2);
	acrescentaAresta(G,ordemG,2,5);
	acrescentaAresta(G,ordemG,3,5);
	acrescentaAresta(G,ordemG,4,6);
	acrescentaAresta(G,ordemG,3,6);
	acrescentaAresta(G,ordemG,7,7);
	acrescentaAresta(G,ordemG,8,9);

	acrescentaAresta(G,ordemG,8,0);

	imprimeGrafo(G, ordemG);
    
	eConexo(G, ordemG) ? printf("e conexo\n\n") : printf("Nao e conexo\n\n");

	qtdComponentes= contaComponentesConexas(G, ordemG);
	printf("Quantidade de componentes conexas: %d\n\n", qtdComponentes);

	verticesCorte= (int*) malloc(sizeof(int) * ordemG);
	if (verticesCorte == NULL){
		printf("Falha de memoria para vertices de corte.\n");
		destroiGrafo(&G, ordemG);
		return 1;
	}

	qtdVerticesCorte= listaVerticesDeCorte(G, ordemG, verticesCorte);
	if (qtdVerticesCorte == 0){
		printf("Nao ha vertices de corte.\n\n");
	} else {
		printf("Vertices de corte:");
		for(i=0; i<qtdVerticesCorte; i++){
			printf(" v%d", verticesCorte[i]);
		}
		printf("\n\n");
	}

	qtdArestas= contaArestasNaoOrientadas(G, ordemG);
	arestasCorteV1= (int*) malloc(sizeof(int) * (qtdArestas > 0 ? qtdArestas : 1));
	arestasCorteV2= (int*) malloc(sizeof(int) * (qtdArestas > 0 ? qtdArestas : 1));
	if (arestasCorteV1 == NULL || arestasCorteV2 == NULL){
		printf("Falha de memoria para arestas de corte.\n");
		if (arestasCorteV1 != NULL) free(arestasCorteV1);
		if (arestasCorteV2 != NULL) free(arestasCorteV2);
		free(verticesCorte);
		destroiGrafo(&G, ordemG);
		return 1;
	}

	qtdArestasCorte= listaArestasDeCorte(G, ordemG, arestasCorteV1, arestasCorteV2);
	if (qtdArestasCorte == 0){
		printf("Nao ha arestas de corte.\n\n");
	} else {
		printf("Arestas de corte:");
		for(i=0; i<qtdArestasCorte; i++){
			printf(" (v%d,v%d)", arestasCorteV1[i], arestasCorteV2[i]);
		}
		printf("\n\n");
	}

	free(verticesCorte);
	free(arestasCorteV1);
	free(arestasCorteV2);
	
	destroiGrafo(&G, ordemG);


	printf("Pressione uma tecla para terminar");
    getchar();
    printf("\n");
	return(0);
}


// No seu projeto, deverão ser implementados algoritmos
// para:
//  calcular a quantidade de componentes conexas do
// grafo,
//  exibir todos os vértices de corte do grafo, e
//  exibir todas as arestas de corte do grafo.
// Adicionalmente, dependendo da quantidade de alunos no
// grupo, deverá ser implementado um algoritmo para:
//  avaliar se o o grafo é hamiltoniano.
