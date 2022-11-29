/*
 * socket_server.cxx
 *
 * Copyright 2022 samhblee <samhblee@samhblee-nvme>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */
//c++ all in one header
#include <bits/stdc++.h>

// C headers
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 2345

int main(int argc, char **argv)
{
    struct addrinfo *server;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));/*set hints*/
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

	int sockfd;
	int len;
	struct sockaddr_in addr;
	int addr_len = sizeof(struct sockaddr_in);
	char buffer[256];

	if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
	{
        perror("socket");
        exit(1);
    }

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd, reinterpret_cast<const sockaddr *>(&addr), sizeof(addr)) < 0)
    {
	    perror("connect");
	    exit(1);
    }

	while(1)
    {
	    bzero(buffer, sizeof(buffer));
	    len = recvfrom(sockfd, buffer, sizeof(buffer), 0, reinterpret_cast<sockaddr *>(&addr),
                       reinterpret_cast<socklen_t *>(&addr_len));
	    printf("receive from %s\n", inet_ntoa(addr.sin_addr));
        printf("receive : %s", buffer);
	    sendto(sockfd, buffer, len, 0, reinterpret_cast<const sockaddr *>(&addr), addr_len );
    }
	return 0;
}

