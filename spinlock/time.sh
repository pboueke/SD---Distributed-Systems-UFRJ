SIZES=(100000000 1000000000 10000000000)
THREADS=(1 2 3 4 5 6 7 8 9 10 15 20 30)

TIMEFORMAT=%R

for size in "${SIZES[@]}";
do
    for thread in "${THREADS[@]}";
    do
        for i in {1..10};
        do
            (time (sudo nice --10 ./a.out $size $thread) ; ) 2>> ${size}_${thread}.dat;
        done
    done
done
