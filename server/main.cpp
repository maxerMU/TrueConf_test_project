#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int main(void)
{
    int master_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(8080);
    sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int rc = bind(master_socket, (struct sockaddr *) &sa, sizeof(sa));
    /*TODO check rc*/

    rc = listen(master_socket, SOMAXCONN);
    /*TODO check rc*/

    while (1)
    {
        int slave_socket = accept(master_socket, NULL, NULL);
        /*TODO check rc*/
        
        char buffer[5] = {0};
        recv(slave_socket, buffer, 4, MSG_NOSIGNAL);
        printf("%s\n", buffer);

        shutdown(slave_socket, SHUT_RDWR);
        close(slave_socket);
    }

    return 0;
}
