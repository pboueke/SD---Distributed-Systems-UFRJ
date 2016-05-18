#!/usr/bin/env bash
SIZES=(2 4 8 16 32)
THREADS1=(1 2 5 10)
THREADS2=(1 2 5 10)

TIMEFORMAT=%R

for size in "${SIZES[@]}";
do
    for thread1 in "${THREADS1[@]}";
    do
        for thread2 in "${THREADS2[@]}";
        do
            for i in {1..10};
            do
                (time (./pc $thread1 $thread2 $size) ; ) 2>> ${thread1}_${thread2}_${size}.dat;
            done
        done
    done
done
