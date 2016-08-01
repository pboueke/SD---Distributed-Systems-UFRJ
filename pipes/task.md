Implemente o programa Produtor-Consumidor como vimos em aula com dois processos que
utilizam pipes (anonymous pipes, para ser mais preciso) para fazer a comunica¸c˜ao. O programa
produtor deve gerar n´umeros inteiros aleat´orios e crescentes e o programa consumidor deve
receber o n´umero e verificar se o mesmo ´e primo, imprimindo o resultado terminal. Seu programa
deve primeiramente criar um pipe e depois fazer um fork() para duplicar o processo, de forma
que os dois processos (pai e filho) tenham as duas duas respectivas pontas do pipe (write end
e read end). O programa consumidor deve terminar quando receber o n´umero 0, assim como o
programa produtor, ap´os enviar o zero. O programa produtor tem como parˆametro o n´umero
de n´umeros a serem gerados, depois do qual o zero ´e enviado. Cuidado com a representa¸c˜ao
num´erica atrav´es do pipe! Uma dica: converta para texto. Teste o seu programa mostrando
seu funcionamento para alguns casos.
