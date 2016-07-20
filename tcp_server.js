var net = require('net');

var server = net.createServer(function(socket) {
    socket.write('Echo server\r\n');
    // socket.pipe(socket);
    // 我们获得一个连接 - 该连接自动关联一个socket对象
    console.log('CONNECTED: ' + socket.remoteAddress + ':' + socket.remotePort);

    // 为这个socket实例添加一个"data"事件处理函数
    socket.on('data', function(data) {
        console.log('DATA ' + socket.remoteAddress + ': ' + data);
        // 回发该数据，客户端将收到来自服务端的数据
        socket.write('From Remote Port: ' + socket.remoteAddress + ':' + socket.remotePort + ", You said " + data);

        console.log([data.toString()]);

        try{
            if(data.toString().replace(/\r|\n/g, '') === 'exit')
                socket.destroy();
        }
        catch(e){
            console.log(e);
        }
    });

    // 为这个socket实例添加一个"close"事件处理函数
    socket.on('close', function(data) {
        console.log('CLOSED: ' +
            socket.remoteAddress + ' ' + socket.remotePort);
    });
});

console.log('$ telnet 0.0.0.0 3333')
server.listen(3333, '0.0.0.0');
