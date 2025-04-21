#pragma once

// Let clients connect to the server.
inline void acceptClients();

// Forces a client to choose a correct name, then places him into idleClients.
inline void sanAndStoreClient();

// Returns whether a client name is allowed or not
inline bool isValidName(std::string_view name);

inline int rng(int min, int max);

// Functionality for clients to discover the server automatically on LAN.
namespace announce {
    extern void start(); // Repeated announcements
    extern void stop();
    extern void announceSelf(); // Single announcement
}

// Lots of important artifacts are here, do look inside.
#include "serverBackend.inl"