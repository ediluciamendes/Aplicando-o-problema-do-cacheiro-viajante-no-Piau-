#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_CIDADES 10

const char *nomesCidades[TOTAL_CIDADES] = {
    "Corrente", "Gilbués", "Bom Jesus", "Floriano", "Oeiras",
    "Teresina", "Campo Maior", "Piripiri", "Luís Correia", "Parnaíba"
};


typedef struct {
    int matriz[TOTAL_CIDADES][TOTAL_CIDADES];
    int numVertices;
} Grafo;


Grafo* criarGrafo(int vertices) {
    Grafo* g = malloc(sizeof(Grafo));
    g->numVertices = vertices;
    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            g->matriz[i][j] = 0;
    return g;
}


void adicionarEstrada(Grafo* g, int v, int w) { // v = origem, w = destino
    g->matriz[v][w] = 1; // Aresta direcionada
}

// função para visualizar o que foi conectado
void mostrarMapa(Grafo* g) {
    printf("\nConexões entre as cidades:\n");
    for (int i = 0; i < g->numVertices; i++) {
        printf("%s -> ", nomesCidades[i]);
        for (int j = 0; j < g->numVertices; j++) {
            if (g->matriz[i][j])
                printf("%s  ", nomesCidades[j]);
        }
        printf("\n");
    }
}

// Variáveis do maior e menor caminho encontrados
int todosCaminhos = 0;
int melhorCaminho[100], piorCaminho[100];
int tamMelhor = 1e9, tamPior = -1;


void buscarTodosOsCaminhos(Grafo* g, int atual, int destino, int visitado[], int caminho[], int nivel) {
    visitado[atual] = 1;
    caminho[nivel] = atual;

    if (atual == destino) {
        todosCaminhos++;
        printf("Caminho %d: ", todosCaminhos);
        for (int i = 0; i <= nivel; i++)
            printf("%s%s", nomesCidades[caminho[i]], (i == nivel) ? "\n" : " -> ");

        if (nivel < tamMelhor) {
            tamMelhor = nivel;
            memcpy(melhorCaminho, caminho, sizeof(int) * (nivel + 1));
        }

        if (nivel > tamPior) {
            tamPior = nivel;
            memcpy(piorCaminho, caminho, sizeof(int) * (nivel + 1));
        }
    } else {
        for (int v = 0; v < g->numVertices; v++) {
            if (g->matriz[atual][v] && !visitado[v]) {
                buscarTodosOsCaminhos(g, v, destino, visitado, caminho, nivel + 1);
            }
        }
    }

    visitado[atual] = 0;
}

// Função para mostrar o menor e maior caminho encontrados na DFS
void mostrarMelhorEPior() {
    printf("\nMenor caminho encontrado:\n");
    for (int i = 0; i <= tamMelhor; i++)
        printf("%s%s", nomesCidades[melhorCaminho[i]], (i == tamMelhor) ? "\n" : " -> ");

    printf("\nMaior caminho encontrado:\n");
    for (int i = 0; i <= tamPior; i++)
        printf("%s%s", nomesCidades[piorCaminho[i]], (i == tamPior) ? "\n" : " -> ");
}

// usando busca em largura (BFS) para o menor caminho em termos de número de estradas
void encontrarCaminhoMaisCurto(Grafo* g, int origem, int destino) {
    int fila[100], visitado[TOTAL_CIDADES] = {0}, anterior[TOTAL_CIDADES];
    int inicio = 0, fim = 0;

    for (int i = 0; i < TOTAL_CIDADES; i++) anterior[i] = -1;

    fila[fim++] = origem;
    visitado[origem] = 1;

    while (inicio < fim) {
        int atual = fila[inicio++];

        if (atual == destino) break;

        for (int v = 0; v < g->numVertices; v++) {
            if (g->matriz[atual][v] && !visitado[v]) {
                fila[fim++] = v;
                visitado[v] = 1;
                anterior[v] = atual;
            }
        }
    }

    // reconstruindo o caminho do destino até a origem
    int caminho[100], tamanho = 0, v = destino;
    while (v != -1) {
        caminho[tamanho++] = v;
        v = anterior[v];
    }

    printf("\nCaminho mais curto (BFS):\n");
    for (int i = tamanho - 1; i >= 0; i--)
        printf("%s%s", nomesCidades[caminho[i]], (i == 0) ? "\n" : " -> ");
}


int main() {
    Grafo* mapa = criarGrafo(TOTAL_CIDADES);

    adicionarEstrada(mapa, 0, 1); // Corrente → Gilbués
    adicionarEstrada(mapa, 1, 2); // Gilbués → Bom Jesus
    adicionarEstrada(mapa, 2, 3); // Bom Jesus → Floriano
    adicionarEstrada(mapa, 3, 4); // Floriano → Oeiras
    adicionarEstrada(mapa, 4, 5); // Oeiras → Teresina
    adicionarEstrada(mapa, 5, 6); // Teresina → Campo Maior
    adicionarEstrada(mapa, 6, 7); // Campo Maior → Piripiri
    adicionarEstrada(mapa, 7, 8); // Piripiri → Luís Correia
    adicionarEstrada(mapa, 8, 9); // Luís Correia → Parnaíba

    // Rotas alternativas
    adicionarEstrada(mapa, 5, 9); // Teresina → Parnaíba
    adicionarEstrada(mapa, 2, 5); // Bom Jesus → Teresina

    mostrarMapa(mapa);


    printf("\n--- Explorando todos os caminhos de Corrente a Parnaíba ---\n");
    int visitado[TOTAL_CIDADES] = {0};
    int caminhoAtual[100];
    buscarTodosOsCaminhos(mapa, 0, 9, visitado, caminhoAtual, 0);
    mostrarMelhorEPior();
    printf("\n--- Menor caminho em número de estradas (via BFS) ---\n");
    encontrarCaminhoMaisCurto(mapa, 0, 9);

    return 0;
}
