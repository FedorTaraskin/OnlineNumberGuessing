namespace comm {
    inline void send(const hasSizeMFunc auto& data) {
        asio::write(mainSocket, asio::buffer(g_Serialize(static_cast<header_t>(data.size()))));
        asio::write(mainSocket, asio::buffer(g_Serialize(data)));
    }

    template<typename Parameter>
    inline Packet<Parameter> read(asio::ip::tcp::socket& localSock = mainSocket) {
        std::string buffer;
        // Resize to fit the header in binary form
        buffer.resize(headerRawSize);

        // Read the header and deserialize it
        asio::read(localSock, asio::buffer(buffer.data(), headerRawSize));
        header_t size = g_Deserialize<header_t>(buffer);

        // The header tells us how much data is about to be sent.
        // Resize to fit all the data to be received.
        buffer.resize(size);

        // Read data and deserialize it
        asio::read(mainSocket, asio::buffer(buffer.data(), size));
        return g_Deserialize<Packet<Parameter>>(buffer);
    }
}