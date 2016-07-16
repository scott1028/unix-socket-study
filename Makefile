server:
	rm -rf server.out
	g++ microservice_server.cpp -lpthread -o server.out
	./server.out 7777

client:
	g++ microservice_client.cpp -o client.out
	./client.out localhost 7777
