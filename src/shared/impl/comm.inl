// Internal details, do not matter outside of this file.
namespace internal {
    using returnType = std::variant<bool, std::string, int32_t, std::vector<cLobby>>;
    static returnType getParamType(action_t act) {
        using namespace actions;
        switch (act) {
        case sendName:
            return std::string();
        default:
            break;
        }
    }
}

// What is shown to other code.
namespace comm {
    template <validParameter Parameter>
    inline void send(const Packet<Parameter>& data, asio::ip::tcp::socket& localSock) {
        using namespace asio;

        // First we send the action in fixed size
        write(localSock, buffer(g_Serialize(data.action)));

        // Second, we send the parameter size (also fixed) only if the parameter is not void
        // If the parameter is void (that is, no parameter) we skip this to save bandwidth.
        if (!std::is_same_v<Parameter, void>) write(localSock, buffer(g_Serialize(data.size())));

        // Now, because the other side can deduce the parameter type based on
        // the action, we send the parameter itself.
        write(localSock, buffer(g_Serialize(data.parameter)));
    }

    template<validParameter Parameter>
    inline Packet<Parameter> read(asio::ip::tcp::socket& s) {
        std::string buffer; // Not to be confused with any asio::buffer

        // Resize to fit a serialized(action_t)
        buffer.resize(serializedActionSize);

        // Read the action into our buffer
        asio::read(s, asio::buffer(buffer));
        action_t act = g_Deserialize<action_t>(buffer);

        // Depending on the action, we know the parameter (and its type).


        // The header tells us how much data is about to be sent.
        // Resize to fit all the data to be received.
        //buffer.resize(size); // TODO

        // Read data and deserialize it
        //asio::read(mainSocket, asio::buffer(buffer.data(), size)); // TODO
        return g_Deserialize<Packet<Parameter>>(buffer);
    }
}