# Eurotrip

Um projeto em C++ orientado a objetos que implementa algoritmos de grafos para otimização de rotas de viagem pela Europa.  O projeto utiliza os algoritmos de Dijkstra e Kruskal para encontrar caminhos mínimos e árvores geradoras mínimas, considerando diferentes critérios: custo, distância e tempo. 

## Estrutura do Grafo

O projeto modela uma rede de cidades europeias conectadas, partindo do Brasil até destinos turísticos como Lisboa, Paris, Roma, Torre Eiffel, Coliseu, entre outros.  Cada aresta do grafo possui três pesos distintos:
- **Custo** (em EUR)
- **Distância** (em km)
- **Tempo** (em horas)

## Organização dos Arquivos

```
├── include/
│   ├── Dijkstra.h
│   ├── Edge.h
│   ├── Graph.h
│   └── Kruskal.h
├── src/
│   ├── Dijkstra.cpp
│   ├── Edge.cpp
│   ├── Graph.cpp
│   └── Kruskal.cpp
├── eurotrip.exe
├── main.cpp
└── README.md
```

## Funcionalidades Implementadas

### Algoritmo de Dijkstra
Encontra o caminho mínimo entre o Brasil e o Coliseu, otimizando por:
- Menor custo total.
- Menor distância total.
- Menor tempo de viagem.

### Algoritmo de Kruskal
Gera a Árvore Geradora Mínima (AGM) da rede de cidades, minimizando:
- Custo total de conexão.
- Distância total de conexão.
- Tempo total de conexão.

### Análise Comparativa
O programa realiza uma análise custo-benefício comparando os três critérios de otimização, utilizando normalização e ponderação para determinar a melhor estratégia de viagem.

### Compilar
```bash
g++ -g main.cpp src/*.cpp -I include/ -o eurotrip
```

### Execução
Execute o arquivo `eurotrip.exe` gerado na raiz do projeto:
```bash
./eurotrip
```

## Saída do Programa

O programa exibe:
1. Lista de vértices (cidades) do grafo.
2. Representação do grafo original.
3. Matrizes de adjacência para cada critério (custo, distância, tempo).
4. Caminhos mínimos calculados pelo algoritmo de Dijkstra.
5. Árvores geradoras mínimas calculadas pelo algoritmo de Kruskal.
6. Análise comparativa dos resultados.
7. Conclusões sobre o melhor custo-benefício.

## Repositório do Github
https://github.com/DebugoDev/DataStructureEurotrip