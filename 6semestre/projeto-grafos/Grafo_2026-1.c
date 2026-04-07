/*
 * REPRESENTACAO DE GRAFOS - Versao 2026/1
 *
 * Juan Nacif - 10428509
 * Matheus Gabriel - 10420444
 * Mihael Xavier - 10239617
 * Richard Barbosa Sanches - 10420179
 * Totti Ferreira Gomes - 10428490
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Estrutura de dados para representar grafos.
 */
typedef struct a {
	int vizinho;
	struct a *prox;
} Aresta;

typedef struct v {
	int nome;
	Aresta *prim;
} Vertice;

/*
 * Declaracoes das funcoes para manipulacao de grafos.
 */
void criaGrafo(Vertice **G, int ordem);
void destroiGrafo(Vertice **G, int ordem);
int acrescentaAresta(Vertice G[], int ordem, int v1, int v2);
void imprimeGrafo(Vertice G[], int ordem);

int eConexo(Vertice G[], int ordem);
int contaComponentesConexas(Vertice G[], int ordem);
int contaVerticesDeCorte(Vertice G[], int ordem, int vertices[]);
int contaArestasDeCorte(Vertice G[], int ordem, int origem[], int destino[]);

static int contaComponentesRestrita(Vertice G[], int ordem, int verticeIgnorado, int arestaA, int arestaB);
static void propagaMarcacao(Vertice G[], int ordem, int marcacao[], int verticeIgnorado, int arestaA, int arestaB, int origem);
static int arestaIgnorada(int v1, int v2, int arestaA, int arestaB);

/*
 * Criacao de um grafo com ordem predefinida e, inicialmente, sem nenhuma aresta.
 */
void criaGrafo(Vertice **G, int ordem) {
	int i;

	*G = (Vertice *) malloc(sizeof(Vertice) * ordem);
	if (*G == NULL) {
		return;
	}

	for (i = 0; i < ordem; i++) {
		(*G)[i].nome = i;
		(*G)[i].prim = NULL;
	}
}

/*
 * Desaloca a memoria dinamica usada para armazenar um grafo.
 */
void destroiGrafo(Vertice **G, int ordem) {
	int i;
	Aresta *a;
	Aresta *n;

	if (G == NULL || *G == NULL) {
		return;
	}

	for (i = 0; i < ordem; i++) {
		a = (*G)[i].prim;
		while (a != NULL) {
			n = a->prox;
			free(a);
			a = n;
		}
	}

	free(*G);
	*G = NULL;
}

/*
 * Acrescenta uma nova aresta em um grafo previamente criado.
 */
int acrescentaAresta(Vertice G[], int ordem, int v1, int v2) {
	Aresta *A1;
	Aresta *A2;
	Aresta *anterior;

	if (v1 < 0 || v1 >= ordem) {
		return 0;
	}
	if (v2 < 0 || v2 >= ordem) {
		return 0;
	}

	A1 = (Aresta *) malloc(sizeof(Aresta));
	if (A1 == NULL) {
		return 0;
	}
	A1->vizinho = v2;
	A1->prox = G[v1].prim;
	G[v1].prim = A1;

	if (v1 == v2) {
		return 1;
	}

	A2 = (Aresta *) malloc(sizeof(Aresta));
	if (A2 == NULL) {
		anterior = G[v1].prim;
		if (anterior == A1) {
			G[v1].prim = A1->prox;
		} else {
			while (anterior != NULL && anterior->prox != A1) {
				anterior = anterior->prox;
			}
			if (anterior != NULL) {
				anterior->prox = A1->prox;
			}
		}
		free(A1);
		return 0;
	}
	A2->vizinho = v1;
	A2->prox = G[v2].prim;
	G[v2].prim = A2;

	return 1;
}

/*
 * Imprime um grafo com uma notacao similar a uma lista de adjacencia.
 */
void imprimeGrafo(Vertice G[], int ordem) {
	int i;
	Aresta *aux;

	printf("\nOrdem: %d", ordem);
	printf("\nLista de Adjacencia:\n");

	for (i = 0; i < ordem; i++) {
		printf("\n    v%d:", i);
		aux = G[i].prim;
		for (; aux != NULL; aux = aux->prox) {
			printf("  v%d", aux->vizinho);
		}
	}
	printf("\n\n");
}

/*
 * Algoritmo para decidir conexidade.
 */
int eConexo(Vertice G[], int ordem) {
	return contaComponentesRestrita(G, ordem, -1, -1, -1) == 1;
}

/*
 * Calcula a quantidade de componentes conexas do grafo.
 */
int contaComponentesConexas(Vertice G[], int ordem) {
	return contaComponentesRestrita(G, ordem, -1, -1, -1);
}

/*
 * Calcula os vertices de corte.
 * O vetor vertices deve ter tamanho pelo menos igual a ordem do grafo.
 */
int contaVerticesDeCorte(Vertice G[], int ordem, int vertices[]) {
	int i;
	int componentesOriginais;
	int componentesSemVertice;
	int total;

	componentesOriginais = contaComponentesConexas(G, ordem);
	total = 0;

	for (i = 0; i < ordem; i++) {
		componentesSemVertice = contaComponentesRestrita(G, ordem, i, -1, -1);
		if (componentesSemVertice > componentesOriginais) {
			vertices[total] = i;
			total++;
		}
	}

	return total;
}

/*
 * Calcula as arestas de corte.
 * Os vetores origem e destino devem ter tamanho suficiente para todas as arestas do grafo.
 */
int contaArestasDeCorte(Vertice G[], int ordem, int origem[], int destino[]) {
	int i;
	Aresta *aux;
	int componentesOriginais;
	int componentesSemAresta;
	int total;

	componentesOriginais = contaComponentesConexas(G, ordem);
	total = 0;

	for (i = 0; i < ordem; i++) {
		aux = G[i].prim;
		for (; aux != NULL; aux = aux->prox) {
			if (i < aux->vizinho) {
				componentesSemAresta = contaComponentesRestrita(G, ordem, -1, i, aux->vizinho);
				if (componentesSemAresta > componentesOriginais) {
					origem[total] = i;
					destino[total] = aux->vizinho;
					total++;
				}
			}
		}
	}

	return total;
}

/*
 * Procura componentes conexas usando a propagacao iterativa de marcacoes.
 */
int contaComponentesRestrita(Vertice G[], int ordem, int verticeIgnorado, int arestaA, int arestaB) {
	int *marcacao;
	int i;
	int total;

	marcacao = (int *) malloc(sizeof(int) * ordem);
	if (marcacao == NULL) {
		return 0;
	}

	for (i = 0; i < ordem; i++) {
		marcacao[i] = 0;
	}

	total = 0;
	for (i = 0; i < ordem; i++) {
		if (i != verticeIgnorado && marcacao[i] == 0) {
			total++;
			propagaMarcacao(G, ordem, marcacao, verticeIgnorado, arestaA, arestaB, i);
		}
	}

	free(marcacao);
	return total;
}

void propagaMarcacao(Vertice G[], int ordem, int marcacao[], int verticeIgnorado, int arestaA, int arestaB, int origem) {
	int mudou;
	int i;
	Aresta *aux;

	marcacao[origem] = 1;
	mudou = 1;

	while (mudou) {
		mudou = 0;
		for (i = 0; i < ordem; i++) {
			if (i != verticeIgnorado && marcacao[i] == 1) {
				aux = G[i].prim;
				for (; aux != NULL; aux = aux->prox) {
					if (aux->vizinho != verticeIgnorado && !arestaIgnorada(i, aux->vizinho, arestaA, arestaB) && marcacao[aux->vizinho] == 0) {
						marcacao[aux->vizinho] = 1;
						mudou = 1;
					}
				}
			}
		}
	}
}

/*
 * Retorna 1 se a aresta informada deve ser ignorada.
 */
int arestaIgnorada(int v1, int v2, int arestaA, int arestaB) {
	if (arestaA < 0 || arestaB < 0) {
		return 0;
	}
	if ((v1 == arestaA && v2 == arestaB) || (v1 == arestaB && v2 == arestaA)) {
		return 1;
	}
	return 0;
}

/*
 * Programa principal para testar os algoritmos implementados.
 */
int main(int argc, char *argv[]) {
	Vertice *G;
	int ordemG;
	int componentes;
	int conexo;
	int *verticesCorte;
	int *origemCorte;
	int *destinoCorte;
	int totalVerticesCorte;
	int totalArestasCorte;
	int i;

	(void) argc;
	(void) argv;

	ordemG = 12;
	G = NULL;

	criaGrafo(&G, ordemG);
	if (G == NULL) {
		printf("Falha na alocacao de memoria.\n");
		return 1;
	}

	/* Exemplo mais abstrato: blocos cíclicos ligados por pontes e uma cauda. */
	acrescentaAresta(G, ordemG, 0, 1);
	acrescentaAresta(G, ordemG, 1, 2);
	acrescentaAresta(G, ordemG, 2, 0);

	acrescentaAresta(G, ordemG, 2, 3);

	acrescentaAresta(G, ordemG, 3, 4);
	acrescentaAresta(G, ordemG, 4, 5);
	acrescentaAresta(G, ordemG, 5, 3);

	acrescentaAresta(G, ordemG, 5, 6);
	acrescentaAresta(G, ordemG, 6, 7);
	acrescentaAresta(G, ordemG, 7, 8);
	acrescentaAresta(G, ordemG, 8, 5);

	acrescentaAresta(G, ordemG, 8, 9);
	acrescentaAresta(G, ordemG, 9, 10);
	acrescentaAresta(G, ordemG, 10, 11);

	imprimeGrafo(G, ordemG);

	conexo = eConexo(G, ordemG);
	componentes = contaComponentesConexas(G, ordemG);

	verticesCorte = (int *) malloc(sizeof(int) * ordemG);
	origemCorte = (int *) malloc(sizeof(int) * (ordemG * ordemG));
	destinoCorte = (int *) malloc(sizeof(int) * (ordemG * ordemG));

	if (verticesCorte == NULL || origemCorte == NULL || destinoCorte == NULL) {
		printf("Falha na alocacao de memoria auxiliar.\n");
		free(verticesCorte);
		free(origemCorte);
		free(destinoCorte);
		destroiGrafo(&G, ordemG);
		return 1;
	}

	totalVerticesCorte = contaVerticesDeCorte(G, ordemG, verticesCorte);
	totalArestasCorte = contaArestasDeCorte(G, ordemG, origemCorte, destinoCorte);

	printf("Grafo conexo: %s\n", conexo ? "sim" : "nao");
	printf("Quantidade de componentes conexas: %d\n", componentes);

	printf("Vertices de corte:");
	if (totalVerticesCorte == 0) {
		printf(" nenhum");
	} else {
		for (i = 0; i < totalVerticesCorte; i++) {
			printf(" v%d", verticesCorte[i]);
		}
	}
	printf("\n");

	printf("Arestas de corte:");
	if (totalArestasCorte == 0) {
		printf(" nenhuma");
	} else {
		for (i = 0; i < totalArestasCorte; i++) {
			printf(" (v%d, v%d)", origemCorte[i], destinoCorte[i]);
		}
	}
	printf("\n");

	free(verticesCorte);
	free(origemCorte);
	free(destinoCorte);
	destroiGrafo(&G, ordemG);

	return 0;
}