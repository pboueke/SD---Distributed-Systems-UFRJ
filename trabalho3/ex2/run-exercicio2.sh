#!/bin/bash
listOfNames="log sqrt"
listOfNames2="pow"

for t in 128 64 32 16 8 4 2 1
do
	for op in $listOfNames
	do
		killall server
		go run server/server.go &
		echo "running t=$t, op=$op\n"
		go run client/client.go $t $op >> output-exercicio1.txt
		echo "----------------------------\n" >> output-exercicio1.txt
	done
	for op in $listOfNames2
	do
		killall server
		go run server/server.go &
		echo "running t=$t, op=$op\n"
		go run client/client.go $t $op 2 >> output-exercicio1.txt
		echo "----------------------------\n" >> output-exercicio1.txt
	done
done

