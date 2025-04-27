// Internal details, do not matter outside of this file.
namespace impl {
    enum type : uint_fast8_t { 
        MONOSTATE, STRING, BOOL, INT, VECTORCLOBBY 
    };

    static uint_fast8_t getParamType(action_t act) {
        //using namespace actions;
        //using enum actions;
        using namespace impl;
        using enum type;
        switch (act) {
        case actions::sendName: return STRING;
        case actions::approveName: return BOOL;
        case actions::getLobbies: return
            #ifdef _CLIENT
                VECTORCLOBBY
            #elif defined(_SERVER)
                MONOSTATE
            #else
                #error Must define either `_CLIENT` or `_SERVER`.
            #endif
            ;
        default:
            break;
        }
    }
}

// What is shown to other code.
namespace comm {
    inline void send(const Packet& data, asio::ip::tcp::socket& localSock) {
        using namespace asio;

        // First we send the action in fixed size
        write(localSock, buffer(g_Serialize(data.action)));

        #ifdef _DEBUG
        // If this is wrong, comm::read will be trying to read a different amount
        // of data.
        assert(g_Serialize(data.action).size() == serializedActionSize);
        #endif

        // Second, we send the parameter size (also fixed) only if the parameter is not void
        // If the parameter is void (that is, no parameter) we skip this to save bandwidth.
        using dt = std::decay_t<decltype(data)>;
        if constexpr (!std::is_same_v<dt, std::monostate>) 
            // Serialize the packet's size in serialized form and send.
            write(localSock, buffer(g_Serialize(static_cast<header_t>(g_Serialize(data).size()))));

        // Now, because the other side can deduce the parameter type based on
        // the action, we send the parameter itself.
        write(localSock, buffer(g_Serialize(data.parameter)));
    }

    inline Packet read(asio::ip::tcp::socket& s) {
        std::string buffer; // Not to be confused with any asio::buffer

        // Resize to fit a serialized(action_t)
        buffer.resize(serializedActionSize);

        // Read the action into our buffer
        asio::read(s, asio::buffer(buffer));
        action_t act = g_Deserialize<action_t>(buffer);

        // Read the parameter size
        buffer.resize(serializedHeaderSize);
        asio::read(s, asio::buffer(buffer));
        header_t size = g_Deserialize<header_t>(buffer);

        // The parameter size tells us how much data is about to be sent.
        // Resize to fit all the data to be received.
        buffer.resize(size);
        
        // Deserialize the buffer into the actual parameter
        Parameter_t p = g_Deserialize<Parameter_t>(buffer);

        #ifdef _DEBUG
        // Inside of the lambda passed to std::visit, p becomes
        // of its original raw parameter type.
        std::visit(
            [&](auto&& value) {
                using T = std::decay_t<decltype(value)>;
                if constexpr (std::is_same_v<T, std::monostate>) {
                    std::cout << "There is nothing.\n";
                }
                else { std::cout << "There is something\n"; }
            },
        p);
        #endif

        // Make the packet and return it
        return Packet{ act, p };
    }

    template <typename T>
    // Function for reading the parameter of a packet directly if you
    // know the parameter's type before calling.
    inline T readParameter(asio::ip::tcp::socket& s) {
        return std::get<T>(read(s).parameter);
    }
}