Considere o problema calcular a soma de um grande n´umero de n´umeros. Vocˆe deve projetar e
implementar um programa multithreaded para resolver este problema, visando reduzir o tempo
de execu¸c˜ao. Assuma que os n´umeros a serem somados est˜ao armazenados em um vetor de
tamanho N e seus valores s˜ao n´umeros aleat´orios no intervalo [−100, 100]. Seu programa deve
ter como parˆametro K, que representa o n´umero de threads que ir˜ao trabalhar simultaneamente.
Uma forma de resolver o problema ´e dividir a soma em K parcelas com N/K valores
e deixar cada thread realizar a soma de cada parcela, somando o resultado em um acumulador
compartilhado. Como v´arias threads v˜ao escrever no acumulador, o acesso ao mesmo deve ser
serializado.
Para serializar o acesso ao acumulador compartilhado, implemente um spinlock como vimos
em aula. Vocˆe deve implementar o spinlock utilizando instru¸c˜oes atˆomicas, como a test-and-set,
utilizando busy wait para bloquear a thread. Em particular, implemente as fun¸c˜oes acquire()
e release() para entrar e sair da regi˜ao cr´ıtica, como visto em aula, e defina sua regi˜ao cr´ıtica
adequadamente.
Para o estudo de caso, considere N = 10^8
, N = 10^9
e N = 10^10. Vocˆe deve alocar mem´oria
utilizando apenas um byte para cada n´umero, e preencher o vetor de forma aleat´oria (com
n´umeros no intervalo [−100, 100]). Utilize os valores de K = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 20, 30.
Para cada combina¸c˜ao de valores N, K, obtenha o tempo de execu¸c˜ao do seu programa, rodando
o programa 10 vezes para calcular o tempo m´edio de execu¸c˜ao (para cada combina¸c˜ao de valores,
teremos um tempo m´edio de execu¸c˜ao). Apresente um gr´afico mostrando o tempo m´edio de
execu¸c˜ao em fun¸c˜ao do n´umero de threads para cada valor de N (cada N deve ser uma curva
no gr´afico).
