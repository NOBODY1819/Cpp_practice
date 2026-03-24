#include <iostream>
#include <cstring>      // for memset, strerror (not used yet but useful)
#include <cerrno>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

// ==================== CROSS-PLATFORM HELPERS ====================
#ifdef _WIN32
    using socket_t = SOCKET;
    #define CLOSE_SOCKET(s)    closesocket(s)
    #define IS_INVALID(s)      ((s) == INVALID_SOCKET)
#else
    using socket_t = int;
    #define CLOSE_SOCKET(s)    close(s)
    #define IS_INVALID(s)      ((s) < 0)
#endif

void print_error(const char* msg) {
#ifdef _WIN32
    std::cerr << msg << " (Winsock error)\n";
#else
    std::cerr << msg << ": " << strerror(errno) << "\n";
#endif
}

int main() {
    std::cout << "=== TCP Echo Server Starting ===\n\n";

    // ────── 1. Windows only: Start Winsock ──────
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }
    std::cout << "Winsock 2.2 initialized\n";
#endif

    // ────── 2. Create the listening socket ──────
    socket_t listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (IS_INVALID(listen_sock)) {
        print_error("socket() failed");
        return 1;
    }
    std::cout << "Socket created (file descriptor obtained)\n";

    // ────── 3. Allow port reuse (super useful in learning) ──────
    int yes = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes));

    // ────── 4. Fill the address structure ──────
    sockaddr_in server_addr{};
    server_addr.sin_family      = AF_INET;           // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;        // 0.0.0.0 = listen on all interfaces
    server_addr.sin_port        = htons(9000);       // port 9000 in network byte order

    // ────── 5. Bind socket to the address ──────
    if (bind(listen_sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        print_error("bind() failed");
        CLOSE_SOCKET(listen_sock);
        return 1;
    }
    std::cout << "Bound to port 9000\n";

    // ────── 6. Start listening ──────
    if (listen(listen_sock, 5) == -1) {   // 5 = max waiting clients
        print_error("listen() failed");
        CLOSE_SOCKET(listen_sock);
        return 1;
    }
    std::cout << "Listening on port 9000... (waiting for clients)\n\n";

    // ────── 7. Infinite loop: accept clients and echo ──────
    while (true) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);

        socket_t client_sock = accept(listen_sock, (sockaddr*)&client_addr, &client_len);
        if (IS_INVALID(client_sock)) {
            print_error("accept() failed");
            continue;
        }

        // Show who connected
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, ip, sizeof(ip));
        std::cout << "Client connected: " << ip << "\n";

        // Echo loop
        char buffer[4096];
        int bytes;
        while ((bytes = recv(client_sock, buffer, sizeof(buffer), 0)) > 0) {
            send(client_sock, buffer, bytes, 0);        // send back exactly same bytes
            std::cout << "  Echoed " << bytes << " bytes\n";
        }

        std::cout << "Client disconnected\n";
        CLOSE_SOCKET(client_sock);
    }

    // We never reach here
    CLOSE_SOCKET(listen_sock);
#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}