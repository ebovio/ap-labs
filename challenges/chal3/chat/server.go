// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 254.
//!+

// Chat is a server that lets clients chat with each other.
package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"net"
	"strings"
	"time"
)

//!+broadcaster
type client chan<- string // an outgoing message channel

type user struct {
	username string
	ip       string
}

var (
	entering    = make(chan client)
	leaving     = make(chan client)
	messages    = make(chan string) // all incoming client messages
	listUsers   []user
	destination client
	clientHash  []client
	check       = 0
)

func broadcaster(host string, port string) {
	fmt.Printf("irc-server > Simple IRC Server started at %s:%s\n", host, port)
	fmt.Printf("irc-server > Ready for receiving new clients\n")
	clients := make(map[client]bool) // all connected clients
	for {
		select {
		case msg := <-messages:
			// Broadcast incoming message to all
			// clients' outgoing message channels.
			if check == 0 {
				for cli := range clients {
					addHash(cli)
					cli <- msg
				}
			} else {
				check = 0
				for cli := range clients {
					if destination == cli {
						cli <- msg
					}
				}
			}
		case cli := <-entering:
			clients[cli] = true

		case cli := <-leaving:
			delete(clients, cli)
			close(cli)
		}
	}
}

//!-broadcaster

//!+handleConn
func handleConn(conn net.Conn) {
	ch := make(chan string) // outgoing client messages
	go clientWriter(conn, ch)

	/*buf := make([]byte, 1024)
	conn.Read(buf)
	username := string(buf)*/
	var users = ""
	var message = ""
	var other = ""
	var username = ""
	var login = 1

	who := conn.RemoteAddr().String()
	ch <- "Welcome to the Simple IRC Server."
	ch <- "Your IP is " + who
	ch <- "Introduce your username: "
	input := bufio.NewScanner(conn)
	for input.Scan() {
		inputChat := strings.Split(input.Text(), " ")
		if login == 1 {
			listUsers = append(listUsers, user{inputChat[0], who})
			username = inputChat[0]
			login = 0
			entering <- ch
			messages <- username + " has joined"
		} else {
			if inputChat[0] == "/users" {
				users = listUsers[0].username
				for i := 1; i < len(listUsers); i++ {
					users = users + ", " + listUsers[i].username
				}
				ch <- "irc-server > " + users
			} else if inputChat[0] == "/time" {
				time := time.Now()
				ch <- "irc-server > " + time.String()
			} else if inputChat[0] == "/user" {
				if len(inputChat) == 2 {
					var showed = 0
					for i := 0; i < len(listUsers); i++ {
						if listUsers[i].username == inputChat[1] {
							ch <- "username: " + listUsers[i].username + ", IP: " + listUsers[i].ip
							showed = 1
						}
					}
					if showed == 0 {
						ch <- "Not found"
					}
				} else {
					ch <- "Usage: /user <username>"
				}
			} else if inputChat[0] == "/msg" {
				if len(inputChat) == 3 {
					check = 1
					other = inputChat[1]
					for i := 2; i < len(inputChat); i++ {
						message = message + inputChat[i]
					}
					for i := 0; i < len(listUsers); i++ {
						if listUsers[i].username == other {
							destination = clientHash[i]
						}
					}
					messages <- username + ": " + message
				} else {
					ch <- "Usage: /msg <username> <message>"
				}
			} else {
				messages <- username + ": " + input.Text()
			}
		}
	}
	// NOTE: ignoring potential errors from input.Err()
	leaving <- ch
	fmt.Printf("irc-server > " + username + " left\n")
	for i := 0; i < len(listUsers); i++ {
		if listUsers[i].username == username {
			listUsers = removeUser(listUsers, i)
			clientHash = removeHash(clientHash, i)
		}
	}
	messages <- username + " has left"
	conn.Close()
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
	}
}

//!-handleConn

func addHash(cli client) {
	for i := 0; i < len(clientHash); i++ {
		if clientHash[i] == cli {
			return
		}
	}
	clientHash = append(clientHash, cli)
}

func removeHash(clis []client, i int) []client {
	clis[i] = clis[len(clis)-1]
	return clis[:len(clis)-1]
}

func removeUser(s []user, i int) []user {
	s[i] = s[len(s)-1]
	return s[:len(s)-1]
}

//!+main
func main() {
	host := flag.String("host", "", "Host name")
	port := flag.String("port", "", "Port chat")
	flag.Parse()
	listener, err := net.Listen("tcp", *host+":"+*port)
	if err != nil {
		log.Fatal(err)
	}

	go broadcaster(*host, *port)
	for {
		conn, err := listener.Accept()
		who := conn.RemoteAddr().String()

		if err != nil {
			log.Print(err)
			continue
		} else {
			fmt.Println("New user connected at: ", who)
		}
		go handleConn(conn)
	}
}

//!-main
