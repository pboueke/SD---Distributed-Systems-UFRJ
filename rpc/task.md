Considere o problema de aplicar uma fun¸c˜ao matem´atica sobre os elementos de um vetor. Por
exemplo, calcular o logaritmo de cada elemento do vetor. Considere ainda que o processamento
ser´a feito in place, ou seja que o resultado da fun¸c˜ao matem´atica ir´a substituir o valor original
no vetor. Projete e implemente um servi¸co utilizando RPC que ofere¸ca esta funcionalidade.
Vocˆe deve implementar ao menos trˆes fun¸c˜oes matem´aticas, com ao menos uma delas sendo
parametrizada. Por exemplo, a fun¸c˜ao potˆencia onde o parˆametro ´e o valor da potˆencia ao qual
cada elemento do vetor ser´a elevado: int potencia rpc(double a, double *vec, int vec size) eleva
cada elemento do vetor vec que possui tamanho vec size a potˆencia a.

Projete e implemente um programa multithreaded que vai utilizar o servi¸co oferecido via
RPC. Seu programa deve alocar um vetor de N posi¸c˜oes e inicializ´a-lo com valores aleat´orios.
Para agilizar o processamento, o programa deve utilizar K threads que far˜ao uso do servi¸co
RPC simultaneamente. Uma forma de dividir o problema ´e instruir cada thread para trabalhar
com N/K posi¸c˜oes cont´ıguas do vetor, cada uma fazendo apenas uma chamada RPC. Instrumente
o tempo necess´ario para aplicar a fun¸c˜ao matem´atica no vetor (sem contar o tempo de
inicializa¸c˜ao).

Para o estudo de caso, considere N = 10^8
e K = 1, 2, 4, 8, 16, 32, 64, 128, e utilize as diferentes
fun¸c˜oes que foram implementadas no servi¸co. Para cada valor de K e fun¸c˜ao matem´atica,
obtenha o tempo de execu¸c˜ao rodando o programa 10 vezes para calcular o tempo m´edio de
execu¸c˜ao (para cada combina¸c˜ao de valores, teremos um tempo m´edio de execu¸c˜ao). Apresente
um gr´afico mostrando o tempo m´edio de execu¸c˜ao em fun¸c˜ao do n´umero de threads para cada
valor de K (cada fun¸c˜ao matem´atica deve ser uma curva no gr´afico). Discuta os resultados
obtidos.
