// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 241.

// Crawl2 crawls web links starting with the command-line arguments.
//
// This version uses a buffered channel as a counting semaphore
// to limit the number of concurrent calls to links.Extract.
//
// Crawl3 adds support for depth limiting.
//
package main

import (
	"flag"
	"fmt"
	"log"
	"os"

	"gopl.io/ch5/links"
)

//!+sema
// tokens is a counting semaphore used to
// enforce a limit of 20 concurrent requests.
var tokens = make(chan struct{}, 20)

func crawl(url string) []string {
	fmt.Println(url)
	tokens <- struct{}{} // acquire a token
	list, err := links.Extract(url)
	<-tokens // release the token

	if err != nil {
		log.Print(err)
	}
	return list
}

//!-sema

var seen = make(map[string]bool)

func crawl3(url string, depth int, done chan bool) {
	if depth <= 0 {
		done <- true
		return
	}
	if visited, ok := seen[url]; visited && ok {
		done <- true
		return
	} else {
		seen[url] = true
	}
	linksDone := make(chan bool)
	links := crawl(url)
	for _, link := range links {
		go crawl3(link, depth-1, linksDone)
		<-linksDone
	}
	done <- true
}

//!+
func main() {
	depth := flag.Int("depth", 1, "")
	url := os.Args[2]
	flag.Parse()
	done := make(chan bool)
	seen[url] = false
	go crawl3(url, *depth, done)
	<-done
}

//!-
