# :hammer_and_wrench: Índice-Remissivo

### :trophy: Integrantes

[Alexandre Tupinambá](https://github.com/Alexandre-Tupinamba) <br/>
[Alcir Castro](https://github.com/PedroLucasMendes) <br/>
[Guilherme Duarte](https://github.com/guilhermesilveiraa) <br/>
[Pedro Mendes](https://github.com/PedroLucasMendes) <br/>

## :books: Sobre o projeto

Este projeto descreve os processos envolvidos durante a implementação de um programa que faz a criação de índices remissivos a partir da leitura
de arquivos. São os conceitos da disciplina
algoritmo e estrutura de dados 2, e as decisões de projeto envolvidas durante a
implementação.

## :book: Pré-processamento

O pré-processamento foi realizado para retirar as stopwords, que são palavras com nenhum significado associado e devem ser removidas antes do processamento de um texto
em linguagem natural. Para isso decidimos usar dicionário estático com o intuito de armazenar as stopwords em um vetor, e depois comparar as palavras do livro com as palavras
armazenadas no dicionário de stopwords. Para tanto os TAD’s utilizados e disponibilizados na pasta **TAD_StopWord** foram:

* **Dicionário Estático** (destatico.c, destatico.h);
* **Tratamento Stopwords** (sSTW.c, sSTW.h);
* **Main de Tratamento Stopwords** (main.c);

## :file_folder: Compilação e Saída

Para compilar os arquivos da pasta **TAD_StopWord** foi utilizado a seguinte diretiva:

~~~cmd
   gcc *.c -o a;
   ./a livro.base stopword.txt > livrotratado.txt
~~~

## :book: Processamento

O processamento foi uma etapa realizada para obter as estatísticas das palavras do arquivo, e enfim criar o índice remissivo solicitado. Para isso foi decidido usar duas estruturas em paralelo: **Dicionário Dinâmico**, **Lista encadeada** e **Vetor**, a figura abaixo mostra
graficamente o funcionamento destas três estruturas.

#IMAGEM AQUI


Ao utilizar estas três estruturas em paralelo podemos realizar buscas de maneira
otimizada no dicionário dinâmico e assim utilizar as operações necessárias para a criação
de um índice remissivo na lista encadeada

Para isso os TAD’s utilizados foram:

* **Dicionário Dinâmico** (ddinamico.c, ddinamico.h);
* **Lista Simplesmente Encadeada** (lse.c, lse.h);
* **Vetor**;
* **Tratamento de Palavras** (palavra.c, palavra.h);

## :file_folder: Compilação e Saída

Para compilar os arquivos da pasta **TAD_Palavra** foi utilizado a seguinte diretiva:


~~~cmd
   gcc *.c -o a -lm;
   ./a livrotratado.txt > indiceremissivo.txt
~~~

Caso queira fazer a busca de apenas uma unica palavra você deverá tirar o comentário
encontrado no arquivo usapalavra.c e executar o código da seguinte forma

~~~cmd
   gcc *.c -o a -lm;
   ./a livrotratado.txt
~~~

### :syringe: Testes Realizados

Os testes mostram o desempenho da implementação realizada considerando o tempo de
execução e o número de comparações realizadas na busca. Os testes foram realizados
utilizandos os três arquivos disponibilizados. Os arquivos são:

* NovoGuarani.txt: 33653 palavras;
* NovoAventuras.txt: 42852 palavras;
* Paralelismo.txt: 43485 palavras;

### :bar_chart: Número médio de comparações

 Arquivo | Média de colisões
--------- | ------
 Novo Paralelismo | 4.5560
 Novo Aventuras | 4.4878 
 Novo Guarani | 4.4573 
 
 ### :heavy_check_mark: Conclusões
 
 Portanto foi concluído que a busca sequencial em um dicionário dinámico para a geração
de um índice remissivo possui eficiência congruente com o que diz a literatura. No entanto pode ser aprimorado utilizando estruturas de dados como árvores
binárias de busca balanceada, afim de se ter mais eficiência. Durante
os estudos foram reforçados os conhecimentos acerca dicionários estáticos e dinâmicos
bem como sua utilidade em soluções de problemas reais. 
