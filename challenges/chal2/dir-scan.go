package main

import (
	"fmt"
	"os"
	"path/filepath"
)

func scanDir(dir string) error {

	directories := 0
	symbolicLinks := 0
	other := 0

	// Scan
	filepath.Walk(dir, func(path string, f os.FileInfo, err error) error {
		if f.IsDir() {
			directories++
		}
		if f.Mode()&os.ModeSymlink != 0 {
			symbolicLinks++
		}
		if f.Mode().IsRegular() {
			other++
		}
		return nil
	})
	fmt.Printf("Path: %s\n", dir)
	fmt.Printf("Directories: %d\n", directories)
	fmt.Printf("Symbolic Links: %d\n", symbolicLinks)
	fmt.Printf("Other Files: %d\n", other)
	return nil
}

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Usage: ./dir-scan <directory>")
		os.Exit(1)
	}
	directoryPath := os.Args[1]
	scanDir(directoryPath)
}
