// websocket_helper.cpp - Reliable minimal SHA1 + Base64 for WebSocket handshake
#include <string>
#include <vector>
#include <cstdint>
#include <cstring>

std::string base64_encode(const unsigned char* data, size_t len) {
    static const char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string result;
    result.reserve(((len + 2) / 3) * 4);

    for (size_t i = 0; i < len; i += 3) {
        uint32_t val = (data[i] << 16);
        if (i + 1 < len) val |= (data[i + 1] << 8);
        if (i + 2 < len) val |= data[i + 2];

        result.push_back(table[(val >> 18) & 0x3F]);
        result.push_back(table[(val >> 12) & 0x3F]);
        result.push_back((i + 1 < len) ? table[(val >> 6) & 0x3F] : '=');
        result.push_back((i + 2 < len) ? table[val & 0x3F] : '=');
    }
    return result;
}

// Correct minimal SHA1 implementation
std::string sha1(const std::string& input) {
    uint32_t h0 = 0x67452301, h1 = 0xEFCDAB89, h2 = 0x98BADCFE, h3 = 0x10325476, h4 = 0xC3D2E1F0;

    std::vector<uint8_t> msg(input.begin(), input.end());
    uint64_t bit_len = msg.size() * 8;

    msg.push_back(0x80);
    while ((msg.size() % 64) != 56) msg.push_back(0x00);

    for (int i = 7; i >= 0; --i)
        msg.push_back((bit_len >> (i * 8)) & 0xFF);

    for (size_t i = 0; i < msg.size(); i += 64) {
        uint32_t w[80] = {0};

        for (int j = 0; j < 16; ++j) {
            w[j] = (msg[i + j*4] << 24) | (msg[i + j*4 + 1] << 16) |
                   (msg[i + j*4 + 2] << 8)  |  msg[i + j*4 + 3];
        }

        for (int j = 16; j < 80; ++j) {
            w[j] = (w[j-3] ^ w[j-8] ^ w[j-14] ^ w[j-16]);
            w[j] = (w[j] << 1) | (w[j] >> 31);
        }

        uint32_t a = h0, b = h1, c = h2, d = h3, e = h4;

        for (int j = 0; j < 80; ++j) {
            uint32_t f, k;
            if      (j < 20) { f = (b & c) | (~b & d); k = 0x5A827999; }
            else if (j < 40) { f = b ^ c ^ d;          k = 0x6ED9EBA1; }
            else if (j < 60) { f = (b & c) | (b & d) | (c & d); k = 0x8F1BBCDC; }
            else             { f = b ^ c ^ d;          k = 0xCA62C1D6; }

            uint32_t temp = ((a << 5) | (a >> 27)) + f + e + k + w[j];
            e = d; d = c; c = ((b << 30) | (b >> 2)); b = a; a = temp;
        }

        h0 += a; h1 += b; h2 += c; h3 += d; h4 += e;
    }

    unsigned char hash[20];
    for (int i = 0; i < 5; ++i) {
        uint32_t val = (i == 0 ? h0 : i == 1 ? h1 : i == 2 ? h2 : i == 3 ? h3 : h4);
        hash[i*4]   = (val >> 24) & 0xFF;
        hash[i*4+1] = (val >> 16) & 0xFF;
        hash[i*4+2] = (val >> 8)  & 0xFF;
        hash[i*4+3] = val & 0xFF;
    }

    return std::string(reinterpret_cast<char*>(hash), 20);
}

std::string compute_websocket_accept(const std::string& key) {
    const std::string magic = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    std::string combined = key + magic;
    std::string hash = sha1(combined);
    return base64_encode(reinterpret_cast<const unsigned char*>(hash.data()), 20);
}