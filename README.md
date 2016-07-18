#### TCP Server .recv( BufferSize )

- Client send 0 bytes 的 Packet 給 Server 代表關閉連線。
- .recv( buffer ) 為每次處理最大的接收 buffer Size。
- 如果超過就分段處理再 Append 起來才是 Client 寄送的 Data。在 EOF 之前都是同一筆資料。
- EOF 就是 Client 送了 0 Bytes 長度的資料給 Server 代表 socket.close()。

```
socket.close() 會寄送，但是無法使用 conn.send('') 這種寫法來寄。
```

![Alt text](https://raw.githubusercontent.com/scott1028/unix-socket-study/master/recv_buffer_size.jpg "Recv Buffer Size")
![Alt text](https://raw.githubusercontent.com/scott1028/unix-socket-study/master/recv_buffer_size_client.jpg "Recv Buffer Size")

- Multithread Handle 或許可以嘗試加每個 Socket 的調用 Timestamp 不論是在接收或是寄送。然後檢查太久沒使用的就從 ConnectionPool Remove 讓 GC 去處理 .close()！

![Alt text](https://raw.githubusercontent.com/scott1028/unix-socket-study/master/socket_close_conception.jpg "Recv Buffer Size")

- About GC: https://docs.python.org/2/library/gc.html

![Alt text](https://raw.githubusercontent.com/scott1028/unix-socket-study/master/python_gc_testing.jpg "Recv Buffer Size")

- 已 Single Thread 來說一次只會處理一個其他的連線會放在 Connection Queue 等待處理。但 Connection Queue 到達上線會出現 ECONNREFUSED Error。

![Alt text](https://raw.githubusercontent.com/scott1028/unix-socket-study/master/socket_connection_queue_limit_by_listen_func.png "Connection Queue Limit")
![Alt text](https://raw.githubusercontent.com/scott1028/unix-socket-study/master/backlog_detail.png "backlog")
