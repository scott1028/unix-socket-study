#### TCP Server .recv( BufferSize )

- Client send 0 bytes 的 Packet 給 Server 代表關閉連線( socket.close() 會寄送，但是無法使用 conn.send('') 這種寫法來寄 )

![Alt text](https://raw.githubusercontent.com/scott1028/unix-socket-study/master/recv_buffer_size.jpg "Recv Buffer Size")
![Alt text](https://raw.githubusercontent.com/scott1028/unix-socket-study/master/recv_buffer_size_client.jpg "Recv Buffer Size")
