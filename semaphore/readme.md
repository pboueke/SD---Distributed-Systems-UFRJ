Implemente um programa Produtor-Consumidor multithreaded com mem´oria compartilhada
limitada. Assuma que a mem´oria compartilhada ´e um vetor de tamanho N de n´umeros inteiros.
O valor 0 denota que a posi¸c˜ao do vetor est´a livre. O n´umero de threads do tipo produtor
e consumidor s˜ao parˆametros do programa dados por Np e Nc, respectivamente. A thread
1
produtor deve gerar n´umeros inteiros aleat´orios entre 1 e 10^7
e colocar o n´umero em uma posi¸c˜ao
livre da mem´oria compartilhada. A thread consumidor deve retirar um n´umero produzido por
um produtor da mem´oria compartilhado e verificar se o mesmo ´e primo, imprimindo o resultado
terminal.
Repare que a mem´oria compartilhada ser´a escrita e lida por v´arias threads e por o acesso
deve ser serializado, evitando condi¸c˜oes de corrida. Utilize sem´aforos para serializar o acesso `a
mem´oria compartilhada. Repare ainda que quando a mem´oria compartilhada estiver cheia ou
vazia (sem posi¸c˜oes livres ou sem posi¸c˜oes com n´umeros) as threads produtor ou consumidor
devem aguardar, respectivamente. Ou seja, uma thread produtor aguarda at´e que haja uma
posi¸c˜ao de mem´oria livre, e uma thread consumidor aguarda at´e que haja uma posi¸c˜ao de
mem´oria ocupada. Utilize sem´aforos contadores para esta sincroniza¸c˜ao (que devem ter como
parˆametro N), como vimos em aula.
Dica: Vocˆe pode implementar um algoritmo bem simples para encontrar uma posi¸c˜ao livre
na mem´oria compartilhada, como percorrer o vetor do in´ıcio at´e encontrar o valor 0. O mesmo
para encontrar um posi¸c˜ao ocupada (a ser processada), como percorrer o vetor do in´ıcio at´e
encontrar um valor n˜ao zero. A thread consumidor deve copiar o n´umero a ser processado para
sua mem´oria local, liberando o espa¸co na mem´oria compartilhada.
Para o estudo de caso, considere que o programa termina sua execu¸c˜ao ap´os o consumidor
processar M = 10^4 n´umeros. Considere ainda os valores N = 2, 4, 8, 16, 32, com os seguintes
combina¸c˜oes de n´umero de threads produtor/consumidor:
(Np, Nc) = {(1, 1),(2, 2),(5, 5),(10, 10),(2, 10),(10, 2)}.
Para cada combina¸c˜ao de parˆametros, obtenha o tempo de execu¸c˜ao do seu programa,
rodando o programa 10 vezes para calcular o tempo m´edio de execu¸c˜ao (para cada combina¸c˜ao
de valores, teremos um tempo m´edio de execu¸c˜ao). Apresente um gr´afico mostrando o tempo
m´edio de execu¸c˜ao em fun¸c˜ao do n´umero de threads produtor/consumidor para cada valor de
N (cada N deve ser uma curva no gr´afico).
