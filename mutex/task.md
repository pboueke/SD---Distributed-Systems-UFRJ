Considere o problema de garantir exclus˜ao m´utua a uma regi˜ao cr´ıtica entre processos. Projete
e implemente o algoritmo centralizado visto em aula, implementando as primitivas request,
grant e release. Para a troca de mensagens entre processos, vocˆe pode utilizar sockets (como no
1
primeiro trabalho) ou qualquer outra primitiva de mais alto n´ıvel, como RPC. Instrumente o
processo coordenador para logar os trˆes tipos de mensagens com o tempo do rel´ogio local (RTC)
de cada mensagem, gerando um arquivo.

Para o estudo de caso, considere que K processos clientes tem acesso ao mesmo sistema
de arquivos (por exemplo, executam na mesma m´aquina). Todos os processos clientes desejam
escrever no mesmo arquivo, opera¸c˜ao esta que precisa ser realizada exclusivamente para o bom
funcionamento do sistema. Cada processo cliente dorme por um tempo aleat´orio entre [0, T]
segundos e ao acordar adiciona uma frase a um arquivo compartilhado entre todos os processos.
A regi˜ao cr´ıtica envolve abrir o arquivo, escrever uma frase1 no final do arquivo, e fechar o
arquivo. O processo deve repetir este procedimento e escrever X frases no arquivo, para depois
concluir sua execu¸c˜ao.

Considere duas formas dos processos entrarem no sistema distribu´ıdo: (i) bulk arrival, todos
os processos iniciam execu¸c˜ao simultaneamente; (ii) sequential arrival, um processo entra por
vez no sistema, com o intervalo de tempo de Y segundos entre eles. Implemente estas duas
formas dos processos entrarem no sistema.
Para o estudo de caso, considere T = 1, K = 1, 2, 4, 8, 16, 32, 64, 128, X = 100, e Y = 1.
Teste seu programa para as duas formas de entrada de processos. Fa¸ca um programa que verifica
se o arquivo gerado pelos processos est´a correto, ou seja, se n˜ao h´a inconsistˆencias nas frases
escritas no arquivo. Por fim, calcule o tempo para execu¸c˜ao do sistema, ou seja, o intervalo de
tempo desde a chegada do primeiro processo at´e a sa´ıda do ´ultimo processo. Fa¸ca um gr´afico
do tempo de execu¸c˜ao em fun¸c˜ao de K, executando 10 vezes cada cen´ario e reportando a m´edia
amostral do tempo de execu¸c˜ao. O gr´afico deve ter duas curvas, correspondendo as duas formas
de entrada no sistema.
