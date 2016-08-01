Nesta tarefa vocˆe tem que escrever dois programas.
* O primeiro programa deve ser capaz de enviar um sinal a qualquer outro processo. Este
programa recebe como parˆametros o n´umero do processo destino e o sinal que deve ser
enviado. Se o processo destino n˜ao existir, seu programa deve retornar um erro. Caso
contr´ario, seu programa deve enviar o sinal desejado.
* O segundo programa deve ser capaz de receber um ou mais sinais espec´ıficos. Para isto,
vocˆe vai precisar definir signal handlers. Seu programa deve capturar e reagir a trˆes sinais
diferentes (de sua escolha), ou mais, imprimindo no terminal uma mensagem diferente
para cada sinal. Al´em disso, um dos sinais sendo capturados deve terminar a execu¸c˜ao
do programa, ou seja, sua signal handler deve terminar o processo. Repare que ap´os
estipular as signal handlers seu programa fica aguardando a chegada de sinais. Vocˆe deve
implementar duas formas de esperar, busy wait e blocking wait (passado como parˆametro
para o programa). Descubra como implementar cada um destas formas de esperar.
* Teste seus programas fazendo com que um envie sinais para o outro. Use tamb´em o
programa kill para enviar sinais para o seu segundo programa.
