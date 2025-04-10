#pragma once

asio::io_context context;
asio::ip::tcp::socket mySocket(context);