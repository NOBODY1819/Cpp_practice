// main.cpp - Dual Mode Server: Raw TCP + WebSocket Echo
// Compile with CMake or directly with g++ ... -lws2_32

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdint>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
using socket_t = SOCKET;
#define CLOSE_SOCKET(s) closesocket(s)
#define IS_INVALID(s) ((s) == INVALID_SOCKET)
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using socket_t = int;
#define CLOSE_SOCKET(s) close(s)
#define IS_INVALID(s) ((s) < 0)
#endif

// ==================== WebSocket Helper Functions ====================
// (from websocket_helper.cpp - included here for simplicity)
std::string base64_encode(const unsigned char *data, size_t len);
std::string compute_websocket_accept(const std::string &key);

// Simple error printer
void print_error(const char *msg)
{
#ifdef _WIN32
    std::cerr << msg << " (Winsock error)\n";
#else
    std::cerr << msg << ": " << strerror(errno) << "\n";
#endif
}

// ==================== Main Server ====================
int main()
{
    std::cout << "=== Dual Mode Echo Server (TCP + WebSocket) ===\n";
    std::cout << "TCP clients      : telnet / nc / Python\n";
    std::cout << "WebSocket clients: Browser (JavaScript)\n\n";

#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }
#endif

    socket_t listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (IS_INVALID(listen_sock))
    {
        print_error("socket() failed");
        return 1;
    }

    // Allow quick port reuse during development
    int yes = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&yes, sizeof(yes));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    addr.sin_port = htons(9000);

    if (bind(listen_sock, (sockaddr *)&addr, sizeof(addr)) == -1)
    {
        print_error("bind() failed");
        CLOSE_SOCKET(listen_sock);
        return 1;
    }

    if (listen(listen_sock, 10) == -1)
    { // backlog = 10
        print_error("listen() failed");
        CLOSE_SOCKET(listen_sock);
        return 1;
    }

    std::cout << "Server listening on port 9000\n";
    std::cout << " -> Try in terminal : nc 127.0.0.1 9000\n";
    std::cout << " -> Try in browser  : ws://127.0.0.1:9000\n\n";

    while (true)
    {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);

        socket_t client_sock = accept(listen_sock, (sockaddr *)&client_addr, &client_len);
        if (IS_INVALID(client_sock))
        {
            print_error("accept() failed");
            continue;
        }

        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, ip, sizeof(ip));
        std::cout << "\nNew connection from " << ip << "\n";

        // ====================== Read first data to detect protocol ======================
        char buffer[4096] = {0};
        int bytes = recv(client_sock, buffer, sizeof(buffer) - 1, 0);

        if (bytes <= 0)
        {
            CLOSE_SOCKET(client_sock);
            continue;
        }

        std::string request(buffer, bytes);

        // Check if this is a WebSocket handshake request
        bool is_websocket = (request.find("Upgrade: websocket") != std::string::npos &&
                             request.find("Sec-WebSocket-Key") != std::string::npos);

        if (is_websocket)
        {
            std::cout << "Detected WebSocket client (Browser)\n";

            // Extract Sec-WebSocket-Key
            size_t pos = request.find("Sec-WebSocket-Key: ");
            std::string key;
            if (pos != std::string::npos)
            {
                size_t start = pos + 19;
                size_t end = request.find("\r\n", start);
                key = request.substr(start, end - start);
            }

            std::string accept_key = compute_websocket_accept(key);

            std::string response =
                "HTTP/1.1 101 Switching Protocols\r\n"
                "Upgrade: websocket\r\n"
                "Connection: Upgrade\r\n"
                "Sec-WebSocket-Accept: " + accept_key + "\r\n\r\n";

            send(client_sock, response.c_str(), response.length(), 0);
            std::cout << "WebSocket handshake completed successfully!\n";

            // ====================== WebSocket Echo Loop ======================
            while (true)
            {
                bytes = recv(client_sock, buffer, sizeof(buffer), 0);
                if (bytes <= 0)
                    break;

                // Simple echo for text frames (works with most browser messages)
                // We assume payload length < 126 and client sends masked frames
                if (bytes < 6 ) continue; 

                unsigned char* data = (unsigned char*) buffer;
                if ((data[0] & 0x0F) != 0x01) {
                    std::cout << "  Received non-text frame, ignoring\n";
                    continue;
                }

                bool masked = (data[1] & 0x80) != 0;
                uint8_t payload_len = data[1] & 0x7F;

                if (payload_len > 125 || !masked) {
                    std::cout << "  Unsupported frame (too long or not masked)\n";
                    break;
                }

                // Unmask the payload (browser always masks)
                unsigned char* mask_key = data + 2;
                unsigned char* payload  = data + 6;

                for (int i = 0; i < payload_len; ++i) {
                    payload[i] ^= mask_key[i % 4];
                }

                // Now payload[0..payload_len-1] contains clean text

                std::string message((char*)payload, payload_len);
                std::cout << "  Received: " << message << "\n";

                // ====================== Send echo back ======================
                // Build a proper unmasked text frame from server to client
                unsigned char frame[4096];
                frame[0] = 0x81;                              // FIN + Text frame
                frame[1] = (unsigned char)payload_len; // length

                memcpy(frame + 2, payload, payload_len);
                send(client_sock, (char *)frame, payload_len + 2, 0);

                std::cout << "  Echoed " << bytes << " bytes (WebSocket)\n";
            }
        }
        else
        {
            // ====================== Raw TCP Echo Loop ======================
            std::cout << "Detected Raw TCP client (telnet/nc)\n";
            send(client_sock, "Send 'E' to close the connection\n", 33, 0);

            // Echo back the first message we already received
            std::string line_buffer;
            char ch;
            send(client_sock, buffer, bytes, 0);
            line_buffer.append(buffer, bytes);
             
            while (true)
            {
                bytes = recv(client_sock, &ch, 1, 0);
                if (bytes <= 0)
                break;

                // send(client_sock, &ch, 1, 0);

                if (ch == '\n')
                {
                    if(line_buffer == "E")
                        break;
                    std::string msg = "Message Echoed: '" + line_buffer + "'\r\n";
                    bytes = msg.size();
                    
                    send(client_sock, msg.c_str(), bytes, 0);

                    std::cout << "  Echoed " << bytes << " bytes (TCP)\t: '" << msg <<"'\n";
                    line_buffer.clear();
                }else if(ch == '\r'){
                    continue;
                }else{
                    line_buffer += ch;
                }

            }
        }

        std::cout << "Client disconnected\n";
        CLOSE_SOCKET(client_sock);
    }

    CLOSE_SOCKET(listen_sock);
#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}