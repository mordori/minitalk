# minitalk
## ✨ Features
Program that sends a string to another process (identified by its PID) using UNIX signals (SIGUSR1 and SIGUSR2). It first sends the length of the string in bits, then sends the actual string, bit by bit. The receiving process acknowledges each bit via a signal handler.

- Server-client model
- ACK handshake
- Ensures the complete message is received before printing it
- Supports unicode characters

> [!TIP]
> ## 🚀 How to use
Run the following commands to clone the repository and create `server` and `client` applications
``` git
git clone https://github.com/mordori/minitalk.git minitalk
cd minitalk
make
```
Start the server with
``` bash
./server
```
- It will print its process' ID needed as input for the client.

Start the client with the server's PID and a message as arguments, e.g.
``` bash
./client 1234 "Hello"
```
- The server application will print the message it received from the client.

To delete all of the compiled files, use
``` Makefile
make fclean
```
