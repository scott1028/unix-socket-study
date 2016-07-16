server:
	rm -rf server.out
	g++ microservice_server.cpp -lpthread -o server.out
	./server.out 6666

client:
	g++ microservice_client.cpp -o client.out
	./client.out localhost 6666
