#!/bin/bash
listOfNames="log sqrt"
listOfNames2="pow"

for t in 128 64 32 16 8 4 2 1
do
	for op in $listOfNames
	do
		for run in 1 2 3 4 5 6 7 8 9 10
		do
			killall server
			sleep 5s
			go run server/server.go &
			sleep 5s
			echo "running t=$t, op=$op\n run=$run"
			go run client/client.go $t $op >> output100milha-binary.txt
			echo "----------------------------\n" >> output-exercicio1.txt
		done
	done
	for op in $listOfNames2
	do
		for run in 1 2 3 4 5 6 7 8 9 10
		do
			killall server
			sleep 5s
			go run server/server.go &
			sleep 5s
			echo "running t=$t, op=$op\n run=$run"
			go run client/client.go $t $op 2 >> output100milha-binary.txt
			echo "----------------------------\n" >> output-exercicio1.txt
		done
	done
done