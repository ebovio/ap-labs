Simple IRC Server
============================

Implementation of a simple IRC server with a client-server architecture.

| Sub commands           | Description                                          |
|------------------------|------------------------------------------------------|
| /users                 | To list all connected users                          |
| /msg <user> <msg>      | To send a direct message to the specified user       |
| /time                  | Get IRC Server's localtime                           |
| /user <user>           | Get more details about user (Username and IP address)|


To run
--------------------
go run server.go -host <host> -port <port number> (in one terminal)

go run client.go -user <name> -server <server> (you can run as much clients as you wants by opening a new terminal)

