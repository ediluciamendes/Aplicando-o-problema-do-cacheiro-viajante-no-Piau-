# Aplicando-o-problema-do-cacheiro-viajante-no-Piau-

Este projeto em linguagem C simula o planejamento de rotas entre cidades do estado do Piauí,
usando um grafo direcionado. O foco é a compreensão da estrutura de grafos e como percorrê-los.
CIDADES ENVOLVIDAS (índices de 0 a 9):
0 -> Corrente
1 -> Gilbués
2 -> Bom Jesus
3 -> Floriano
4 -> Oeiras
5 -> Teresina
6 -> Campo Maior
7 -> Piripiri
8 -> Luís Correia
9 -> Parnaíba

## Funções principais
1. adicionarEstrada(grafo, origem, destino)
Adiciona uma estrada de uma cidade para outra no grafo.

2. mostrarMapa(grafo)
Imprime todas as conexões entre as cidades (arestas).

3. buscarTodosOsCaminhos(grafo, origem, destino, visitado[], caminho[], nivel)
Essa é a função mais importante.
Ela usa busca em profundidade recursiva (DFS) com backtracking para:
Mostrar todos os caminhos possíveis entre Corrente e Parnaíba;
Salvar o caminho mais curto e o mais longo com base no número de cidades.

4. encontrarCaminhoMaisCurto(grafo, origem, destino)
Implementa busca em largura (BFS) para encontrar o caminho com o menor número de arestas (estradas).

## Explicação da função buscarTodosOsCaminhos
Essa função começa pela cidade de origem (Corrente) e vai explorando todos os caminhos possíveis até chegar a Parnaíba.

Ela funciona assim:
Marca a cidade atual como visitada;
Adiciona essa cidade ao caminho atual;
Se chegou ao destino, imprime o caminho;
Se não chegou, tenta todas as conexões possíveis a partir da cidade atual;
Após explorar todas as opções, "desmarca" a cidade atual para poder usá-la em outros caminhos. (Isso é o chamado backtracking.)
Esse processo recursivo garante que todos os caminhos sejam testados, mesmo os mais longos.



