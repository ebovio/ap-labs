package main

import (
	"golang.org/x/tour/wc"
	"strings"
)

func WordCount(s string) map[string]int {
	m := make(map[string]int)
    for _, i := range strings.Fields(s){
        m[i]++
    }
    return m
}

func main() {
	wc.Test(WordCount)
}