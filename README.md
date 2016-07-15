#### TCP Server .recv( BufferSize )

- Client send 0 bytes 的 Packet 給 Server 代表關閉連線。

```
socket.close() 會寄送，但是無法使用 conn.send('') 這種寫法來寄。
```

![Alt text](https://raw.githubusercontent.com/scott1028/unix-socket-study/master/recv_buffer_size.jpg "Recv Buffer Size")
![Alt text](https://raw.githubusercontent.com/scott1028/unix-socket-study/master/recv_buffer_size_client.jpg "Recv Buffer Size")

- Multithread Handle 或許可以嘗試加每個 Socket 的調用 Timestamp 不論是在接收或是寄送。然後檢查太久沒使用的就從 ConnectionPool Remove 讓 GC 去處理 .close()！

![Alt text](https://raw.githubusercontent.com/scott1028/unix-socket-study/master/socket_close_conception.jpg "Recv Buffer Size")

- About GC: https://docs.python.org/2/library/gc.html
