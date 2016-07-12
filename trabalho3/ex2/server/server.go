package main

import (
	"log"
	"net"
	"net/http"
	_ "net/http/pprof"
	"math"
	"sync"
	"runtime"
	"encoding/json"
	"golang.org/x/net/context"
	"google.golang.org/grpc"
	pb "trabalho3/proto"
)

const (
	port = ":50051"
)

type OperadorServer struct{}

func (s *OperadorServer) RpcLog(ctx context.Context, in *pb.Numbers) (*pb.Result, error) {
	defer clean()
	array := make([]float32, 0, in.Size)
	_ = json.Unmarshal(in.Array, &array)

	for i, elem := range array {
		array[i] = float32(math.Log(float64(elem)))
	}

	stringJson, _ := json.Marshal(array)
	array = nil
	
	return &pb.Result{Array: stringJson}, nil
}

func (s *OperadorServer) RpcSqrt(ctx context.Context, in *pb.Numbers) (*pb.Result, error) {
	defer clean()
	array := make([]float32, 0, in.Size)
	_ = json.Unmarshal(in.Array, &array)

	var wg sync.WaitGroup

	wg.Add(1)
	go func(){
		defer wg.Done()
		for i, elem := range array {
			array[i] = float32(math.Sqrt(float64(elem)))
		}
	}()

	wg.Wait()
	stringJson, _ := json.Marshal(array)
	array = nil
	return &pb.Result{Array: stringJson}, nil
}

func (s *OperadorServer) RpcPower(ctx context.Context, in *pb.NumbersPower) (*pb.Result, error) {
	defer clean()
	array := make([]float32, 0, in.Size)
	_ = json.Unmarshal(in.Array, &array)

	var wg sync.WaitGroup

	wg.Add(1)
	go func(){
		defer wg.Done()
		for i, elem := range array {
			array[i] = float32(math.Pow(float64(elem), float64(in.Power)))
		}
	}()

	wg.Wait()

	stringJson, _ := json.Marshal(array)
	array = nil
	return &pb.Result{Array: stringJson}, nil
}

func main() {
	// Start: Para perfilamento
	go func() {
    	log.Println(http.ListenAndServe("localhost:6061", nil))
    }()	
    // End: perfilamento
    
	lis, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}
	s := grpc.NewServer()
	pb.RegisterOperadorServer(s, &OperadorServer{})
	err = s.Serve(lis)
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}
}

func clean(){
	runtime.GC()
}