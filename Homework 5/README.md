# Homework 5

> *FTP Server*

* Implement a simple version of FTP protocal server with `pthread` & `select()`, and a corresponding client

## Compile

* Server

```bash
gcc server_select.c -o server_select -pthread
gcc server_thread.c -o server_thread -pthread
```

* Client

```bash
gcc main.c -o client
```

## Usage

* Start Server

  * `pthread`

  ```bash
  ./server_thread
  ```

  * `select()`

  ```bash
  ./server_select
  ```

* Start Client

```bash
./client
```

* Commands
  * `ls`: list current directory (working directory of server process)
  * `cd`: open directory
  * `download [filename]`: download `[filename]` from current session directory at server to local
  * `upload [filename]`: upload `[filename]` from local to current session directory at server

## Demo

* Server side

[![server_demo](server.gif)](https://asciinema.org/a/343161)

* Client side

[![client_demo](client.gif)](https://asciinema.org/a/343160)

