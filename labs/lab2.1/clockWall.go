package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
	"time"
)

func main() {
	finish := make(chan int)

	for i := 1; i < len(os.Args); i++ {
		city := strings.Split(os.Args[i], "=")[0]
		port := strings.Split(os.Args[i], "=")[1]
		conn, err := net.Dial("tcp", port)
		if err != nil {
			log.Fatal(err)
		}
		var err02 error
		for true {
			time.Sleep((1 * time.Second))
			fmt.Printf(city + ": ")
			_, err02 = io.CopyN(os.Stdout, conn, 9)
			if err02 == io.EOF {
				break
			} else if err02 != nil {
				log.Fatal(err02)
			}
		}
		finish <- 2
	}

	_ = <-finish // wait for background goroutine to finish
	close(finish)
}
