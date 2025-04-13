#pragma once
#include <asio.hpp>
#include "globals.hpp"

template <class Parameter>
struct Packet {
    action_t action;
    Parameter parameter;

    header_t size();
    void send(asio::ip::tcp::socket& socket);
    Packet(action_t actionToSet, Parameter& parameterToSet) 
        : action(actionToSet), parameter(parameterToSet) {}

    //Cereal support
    template <class Archive>
    void serialize(Archive& archive) { archive(action, parameter); }
};