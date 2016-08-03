Implemente um programa Produtor-Consumidor com resposta com dois processos e sockets para
fazer a comunica¸c˜ao. Novamente, o programa produtor deve gerar n´umeros inteiros aleat´orios
e crescentes e o programa consumidor deve receber o n´umero e verificar se o mesmo ´e primo.
Diferentemente do exerc´ıcio acima, o programa consumidor deve enviar uma mensagem ao
produtor informando se o n´umero recebido ´e ou n˜ao primo, com este ´ultimo imprimindo o resultado
no terminal. Implemente um protocolo bem simples, onde o produtor gera um n´umero,
envia ao consumidor, e aguarda a resposta de forma bloqueante. O programa consumidor deve
se conectar ao programa produtor, e aguardar a chegada de um n´umero, de forma bloqueante,
para depois processar, enviar o resultado ao produtor, e voltar a aguardar a chegada do
pr´oximo n´umero. Utilize sockets to tipo TCP. Por fim, os programas devem terminar como no
exerc´ıcio acima (enviando zero para terminar o consumidor, tendo como parˆametro o n´umero
de n´umeros a serem gerados). Novamente, cuidado com a representa¸c˜ao num´erica! Dica: converta
para texto. Teste o seu programa mostrando seu funcionamento para alguns casos. Teste
seu programa utilizando computadores diferentes, e se poss´ıvel, que estejam rodando sistemas
operacionais diferentes.
