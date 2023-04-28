# ⚙️ Implementações de Estruturas de Dados em C++

Este repositório contém implementações em C++ de várias estruturas de dados comuns. As implementações são fornecidas para fins educacionais e podem ser usadas como referência para estudos ou como base para projetos pessoais.

## As estruturas de dados estão listadas abaixo em ordem crescente de complexidade:

- Vector
- Linked List
- Queue
- Stack
- Hash Table
- Heap
- AVL
- Adjacency Matrix

## Vector
O Vector é uma sequência dinâmica de elementos do mesmo tipo. É semelhante a um array, mas com tamanho variável. Os elementos são armazenados em uma área contígua de memória, permitindo acesso aleatório em tempo constante. Quando o tamanho máximo é atingido, o vetor aumenta automaticamente sua capacidade em um fator de crescimento predefinido.

## Linked List
A Linked List é uma estrutura de dados na qual cada elemento, chamado de nó, contém um valor e um ponteiro para o próximo nó. É possível percorrer a lista a partir do início, visitando cada nó sequencialmente. A Linked List permite inserções e remoções em tempo constante, mas não permite acesso aleatório.

## Queue
A Queue é uma estrutura de dados que segue o princípio "primeiro a entrar, primeiro a sair". Novos elementos são adicionados ao final da fila e os elementos são removidos do início da fila. A Queue pode ser implementada usando um Vector ou uma Linked List.

## Stack
A Stack é uma estrutura de dados que segue o princípio "último a entrar, primeiro a sair". Novos elementos são adicionados ao topo da pilha e os elementos são removidos do topo da pilha. A Stack pode ser implementada usando um Vector ou uma Linked List.

## Hash Table
A Hash Table é uma estrutura de dados que permite armazenar e recuperar valores de forma eficiente. Ela usa uma função de hash para mapear uma chave a um índice na tabela. Se duas chaves colidirem, isto é, se elas forem mapeadas para o mesmo índice, a Hash Table pode usar uma lista vinculada para resolver a colisão. A Hash Table é ideal para armazenar grandes quantidades de dados que podem ser acessados aleatoriamente.

## Heap
A Heap é uma estrutura de dados que permite armazenar um conjunto de valores e recuperar o valor máximo (ou mínimo) de forma eficiente. Ela é implementada como uma árvore binária completa em que cada nó é maior (ou menor) do que seus filhos. A Heap é ideal para algoritmos de ordenação e para encontrar o k-ésimo elemento em um conjunto de valores.

## AVL
A AVL é uma árvore binária de busca balanceada que garante que a diferença de altura entre as subárvores esquerda e direita seja no máximo 1. Isso garante que as operações de inserção e remoção tenham complexidade logarítmica. A AVL é ideal para aplicações que exigem um bom desempenho em operações de busca e modificação.

## Adjacency Matrix

A Adjacency Matrix é uma estrutura de dados para representar um grafo em que as arestas são armazenadas em uma matriz. Cada elemento da matriz representa uma possível conexão entre dois vértices do grafo. Essa estrutura é útil para grafos densos, onde o número de arestas é próximo do número máximo possível de arestas, pois permite acesso rápido às informações de conexão entre vértices e verificações de existência de arestas podem ser feitas em tempo constante. No entanto, pode ser ineficiente para grafos esparsos, onde muitas das posições da matriz estarão vazias.