# minitalk
## ✨ Features
Small data exchange program that uses UNIX signals.

## 📖 Introduction

> [!TIP]
> ## 🚀 How to use
Run the following command to clone the repository and create `server` and `client` applications
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

Start the client with the server's PID and a message as arguments
``` bash
./client 1234 "Hello"
```
- The server application will print the message it received from the client.

To delete all of the compiled files, use
``` Makefile
make fclean
```
