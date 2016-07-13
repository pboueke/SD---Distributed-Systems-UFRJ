package main

import (
	"log"
	"os"
	"time"
	"fmt"
	"sync"
	"net/http"
	_ "net/http/pprof"
	"encoding/binary"
	"bytes"
	"math/rand"
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
	// Start: Para perfilamento
	go func() {
    	log.Println(http.ListenAndServe("localhost:6061", nil))
    }()	
    // End: perfilamento

	n := 100000000
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
    //fmt.Println(values)
    fmt.Printf("demorou %s\n",elapsed)
    fmt.Printf("done - threads: %v, operation: %v\n", threads, operation)
	
}

func fillArray(array *[]float32, n int) {
	for i:=0; i < n; i++{
		*array = append(*array, float32(rand.Int31()))
	}
}

func doLog(slice []float32){
	buffer := new(bytes.Buffer)
	err := binary.Write(buffer, binary.LittleEndian, slice)

	r, err := c.RpcLog(context.Background(), &pb.Numbers{Array: buffer.Bytes(), Size: int32(len(slice))})
	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}
	//err = enc.Unmarshal(r.Array, &slice)	
	buffer.Reset()
	buffer.Write(r.Array)

	err = binary.Read(buffer, binary.LittleEndian, &slice)
	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}
}

func doSqrt(slice []float32){
	buffer := new(bytes.Buffer)
	err := binary.Write(buffer, binary.LittleEndian, slice)

	r, err := c.RpcSqrt(context.Background(), &pb.Numbers{Array: buffer.Bytes(), Size: int32(len(slice))})
	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}

	buffer.Reset()
	buffer.Write(r.Array)

	err = binary.Read(buffer, binary.LittleEndian, &slice)
	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}
}

func doPow(slice []float32, power int32){
	buffer := new(bytes.Buffer)
	err := binary.Write(buffer, binary.LittleEndian, slice)

	r, err := c.RpcPower(context.Background(), &pb.NumbersPower{Array: buffer.Bytes(), Size: int32(len(slice)), Power: power})
	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}

	buffer.Reset()
	buffer.Write(r.Array)

	err = binary.Read(buffer, binary.LittleEndian, &slice)
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