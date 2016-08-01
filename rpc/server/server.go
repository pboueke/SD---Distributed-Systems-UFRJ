package main

import (
	"log"
	"net"
	"net/http"
	_ "net/http/pprof"
	"math"
	"runtime"
	"encoding/binary"
	"bytes"
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

	array := make([]float32, in.Size, in.Size)

	buffer := bytes.NewBuffer(in.Array)
	err := binary.Read(buffer, binary.LittleEndian, &array)

	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}

	for i, elem := range array {
		array[i] = float32(math.Log(float64(elem)))
	}

	buffer.Reset()
	err = binary.Write(buffer, binary.LittleEndian, array)

	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}
	
	return &pb.Result{Array: buffer.Bytes()}, nil
}

func (s *OperadorServer) RpcSqrt(ctx context.Context, in *pb.Numbers) (*pb.Result, error) {
	defer clean()

	array := make([]float32, in.Size, in.Size)

	buffer := bytes.NewBuffer(in.Array)
	err := binary.Read(buffer, binary.LittleEndian, &array)

	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}

	for i, elem := range array {
		array[i] = float32(math.Sqrt(float64(elem)))
	}

	buffer.Reset()
	err = binary.Write(buffer, binary.LittleEndian, array)

	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}
	
	return &pb.Result{Array: buffer.Bytes()}, nil
}

func (s *OperadorServer) RpcPower(ctx context.Context, in *pb.NumbersPower) (*pb.Result, error) {
	defer clean()

	array := make([]float32, in.Size, in.Size)

	buffer := bytes.NewBuffer(in.Array)
	err := binary.Read(buffer, binary.LittleEndian, &array)

	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}

	for i, elem := range array {
		array[i] = float32(math.Pow(float64(elem), float64(in.Power)))
	}

	buffer.Reset()
	err = binary.Write(buffer, binary.LittleEndian, array)

	if err != nil {
		log.Fatalf("could not solve: %v", err)
	}
	
	return &pb.Result{Array: buffer.Bytes()}, nil
}

func main() {
	// Start: Para perfilamento
	go func() {
    	log.Println(http.ListenAndServe("localhost:6060", nil))
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