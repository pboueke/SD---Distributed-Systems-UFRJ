package main

import (
	"log"
	"os"
	"time"
	"fmt"
	"sync"
	"net/http"
	_ "net/http/pprof"
	"encoding/json"
	//rand "math/rand"
	math "math"
	"strconv"
	"golang.org/x/net/context"
	"google.golang.org/grpc"
	pb "trabalho3/proto"
)

const (
	address     = "localhost:50051"
)

var c pb.OperadorClient = nil
var threads int = 1
var operation string = ""
var power int64 = 0

func main() {
	go func() {
    	log.Println(http.ListenAndServe("localhost:6061", nil))
    }()	

	n := 50000000
	values := make([]float32, 0, n)
	fillArray(&values, n)

	fmt.Println("Starting")
	start := time.Now()

	// Set up a connection to the server.
	conn, err := grpc.Dial(address, grpc.WithInsecure())
	if err != nil {
		log.Fatalf("did not connect: %v", err)
	}
	defer conn.Close()
	c = pb.NewOperadorClient(conn)

	if len(os.Args) >= 2 {
		threads, _ = strconv.Atoi(os.Args[1])
		operation = os.Args[2]
		if operation == "pow" {
			pow, _:= strconv.ParseInt(os.Args[3], 10, 32)
			power = pow
		}
	}

	fmt.Println(operation)

	interval := int(math.Ceil(float64(len(values))/float64(threads)))

	var wg sync.WaitGroup

	switch operation {
		case "log":
			wg.Add(threads)
			for i := 0; i < len(values); i += interval {
	    		batch := values[i:min(i+interval, len(values))]
	 			go func(){
					defer wg.Done()
					doLog(batch)
				}()
			}
		case "sqrt":
			wg.Add(threads)
			for i := 0; i < len(values); i += interval {
	    		batch := values[i:min(i+interval, len(values))]
	 			go func(){
					defer wg.Done()
					doSqrt(batch)
				}()
			}
		case "pow":
			wg.Add(threads)
			for i := 0; i < len(values); i += interval {
	    		batch := values[i:min(i+interval, len(values))]
	 			go func(){
					defer wg.Done()
					doPow(batch, int32(power))
				}()
			}
		default:
			fmt.Println("Unknown operation " + operation)


	}

    wg.Wait()

    elapsed := time.Since(start)
    fmt.Printf("demorou %s\n",elapsed)
    fmt.Printf("done - threads: %v, operation: %v\n", threads, operation)
	
}

func fillArray(array *[]float32, n int) {
	for i:=0; i < n; i++{
		*array = append(*array, float32(10+i))//float32(rand.Int31()))
	}
}

func doLog(slice []float32){
	stringJson, err := json.Marshal(slice)
	r, err := c.RpcLog(context.Background(), &pb.Numbers{Array: stringJson, Size: int32(len(slice))})
	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}
	err = json.Unmarshal(r.Array, &slice)	
	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}
}

func doSqrt(slice []float32){
	stringJson, err := json.Marshal(slice)
	r, err := c.RpcSqrt(context.Background(), &pb.Numbers{Array: stringJson, Size: int32(len(slice))})
	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}
	err = json.Unmarshal(r.Array, &slice)	
	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}
}

func doPow(slice []float32, power int32){
	stringJson, err := json.Marshal(slice)
	r, err := c.RpcPower(context.Background(), &pb.NumbersPower{Array: stringJson, Size: int32(len(slice)), Power: power})
	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}
	err = json.Unmarshal(r.Array, &slice)	
	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}
}

func min(a, b int) int {
    if a <= b {
        return a
    }
    return b
}