__________________________________________________________________
a.Description of your source code:  what are the supported functions in your program?  How many files are there in your program? how do you implement the client and server? what is the work flow with your program?

The basic function including
1)echo
2)date
3)string manipulate ¨C upper, lower, reverse

The advanced function is that multiple client can connect to server simutaneously.


There are two .c files in my program, including the server and client file.

I implemented the server and client seperately in two files and apply C as programming language.

In my program, firstly the connection is built between server and 
client, and they communicate with each other through local connection.Multiple client can connect to server simutaneously. Then clients can send request to server and get the results.

__________________________________________________________________
b.Compile steps: how do you compile the source code into executable?

Firstly open the terminal and use the following command in the terminal:
gcc -o server server.c

gcc -o client client.c

Then the executable file will been created.
__________________________________________________________________
c.Start server command

In terminal, input the following comand:
./server 
__________________________________________________________________
d.Start client command

1£©In terminal, input the following comand:
./client 0.0.0.0 3333

2£©Then enter the function name followed with the content, such as:
date
echo Hello
upper apple
lower BEAUTIFUL
reverse ABCDEFG

3£©Open other terminals, using the same way to start many client, they  can communicate with the server simutaneously, and the request can be servered.


