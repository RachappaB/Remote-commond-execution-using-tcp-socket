# Remote-commond-execution-using-tcp-socket

This project help to execute the commond from client to run in server machine using TCP-SOCKET

## Installation

you must have gcc compiler 

```bash
sudo apt-get install gcc
sudo apt-get update
```

## RUN
server
```bash
cd server

# compile the server.c file
gcc server.c

# run a.out file
./a.out
```
 on client machine
client 
```bash
cd client

# compile the server.c file
gcc client.c

# run a.out file
./a.out

# enter server ip addresss
127.0.0.1
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.


## License

[MIT](https://choosealicense.com/licenses/mit/)
