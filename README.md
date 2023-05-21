# Simple Page Rank

Este projeto consiste em um ranqueador de páginas simples feito com a linguagem C. Ele foi feito para disciplina de ED2 da UFES.</br>
Para descobrir qual das estruturas tinha o melhor desempenho, esse projeto foi feito usando 3 estruturas, sendo cada uma delas feita em uma branch, 
a branch principal, foi feita usando uma red-black tree, a "master" branch foi feita usando uma trie, e a branch "tst" foi feita com uma ternary search tree.

## Usage

O ranqueador lê arquivos com nomes específicos num diretório de entrada, que precisa conter os seguintes arquivos:

- index.txt

O index deve conter o nome dos arquivos das páginas, separados por uma quebra de linha, no exemplo da branch main ele consiste de:
```
a.txt
b.txt
c.txt
d.txt
e.txt
```

- stopwords.txt

O arquivo stopwords deve conter uma lista de palavras que devem ser ignoradas pelo ranqueador, separadas por uma quebra de linha, exemplo:
```
de
da
do
e
a
o
em
```

- graph.txt

O arquivo graph deve conter os "links" de cada página, no seguinte formato: ```<página> <num_links> <link1> <link2> ...\n```, exemplo:
```
a.txt 3 b.txt c.txt d.txt
b.txt 0
c.txt 2 a.txt d.txt
...
```

- pages

O diretório pages que deve conter todos arquivos de páginas informados no arquivo 'index.txt'.</br>

Existe um exemplo de entrada na branch main.</br>
A estrutura desse exemplo seria:
```
.
+-- entradas
|   +-- pages
|   |   +-- a.txt
|   |   +-- b.txt
|   |   +-- c.txt
|   |   +-- d.txt
|   |   +-- e.txt
|   +-- index.txt
|   +-- graph.txt
|   +-- stopwords.txt
+-- trab3
+-- Makefile
+-- ...
```

Para usar o projeto primeiro é necessário compilá-lo. Para isso é necessário as ferramentas make e gcc instaladas.</br>
Para compilar use:

- make

Para executar use:

- ./trab3 <diretório_entrada>

Onde <diretório_entrada> consiste no caminho relativo para o diretório de entrada, que contém os arquivos necessários.</br>
Ao executar o projeto, é possível fazer uma pesquisa, e o programa retorna a lista de sites que contém os itens buscados, ordenado de acordo com o ranqueamento das páginas feitas.
  
Condições de execução:

- Se a última linha dos arquivos for apenas um caractere, sem uma quebra de linha ("\n"), o programa não lê essa linha
