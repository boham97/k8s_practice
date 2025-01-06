#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int init_sock();

int main() {
    srand(time(NULL));
    int random = rand();
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;
    char buffer[BUFFER_SIZE] = {0};
	char response[BUFFER_SIZE] = {0};
    int opt = 1;
	int len = 0;
    // 1. 소켓 생성
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    // 2. 소켓 옵션 설정 (재사용 가능하도록)
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt))) 
    {
        perror("Setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 3. 서버 주소 설정
    {
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY; // 모든 IP에서의 연결을 수락
        server_addr.sin_port = htons(PORT);
    }

    // 4. 소켓에 주소 바인딩
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) 
    {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    while(1)
    {

        // 5. 연결 대기 상태로 설정
        if (listen(server_fd, 3) < 0) 
        {
            perror("Listen failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        printf("Server is listening on port %d\n", PORT);

        addr_len = sizeof(client_addr);
        // 6. 클라이언트 연결 수락
        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len)) < 0) {
            perror("Accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        printf("Connection established with client\n");

        // 7. 데이터 송수신
        int valread = read(client_fd, buffer, BUFFER_SIZE);
        printf("Client: %s\n", buffer);
	    snprintf(response, sizeof(response),
            "HTTP/1.1 200 OK\r\n"
            "\r\n"
            "{"
                "\"message\": \"hello, API!\""
                "\"rand\": %d"
            "}"
            , random
        );

    
        len = send(client_fd, response, strlen(response), 0);
        printf("Response sent to client %d\n", len);

        // 8. 소켓 닫기
        close(client_fd);
    }
    close(server_fd);

    return 0;
}