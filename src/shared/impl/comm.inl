namespace comm {
    template <validParameter Parameter>
    inline void send(const Packet<Parameter>& data, asio::ip::tcp::socket& localSock) {
        using namespace asio;

        // First we send the action in fixed size
        write(localSock, buffer(g_Serialize(data.action)));

        // Second, we send the parameter size (also fixed)
        write(localSock, buffer(g_Serialize(data.size())));

        // Now, because the other side can deduce the parameter type based on
        // the action, we send the parameter itself.
        write(localSock, buffer(g_Serialize(data.parameter)));
    }

    template<validParameter Parameter>
    inline Packet<Parameter> read(asio::ip::tcp::socket& s) {
        std::string buffer; // Not to be confused with any asio::buffer

        // Resize to fit the average packet
        buffer.resize(serializedActionSize);

        // Read the action and deserialize it
        asio::read(s, asio::buffer(buffer));
        //asio::read(s, asio::buffer(buffer.data(), buffer.size()));
        action_t size = g_Deserialize<header_t>(buffer);

        // The header tells us how much data is about to be sent.
        // Resize to fit all the data to be received.
        //buffer.resize(size); // TODO

        // Read data and deserialize it
        //asio::read(mainSocket, asio::buffer(buffer.data(), size)); // TODO
        return g_Deserialize<Packet<Parameter>>(buffer);
    }
}