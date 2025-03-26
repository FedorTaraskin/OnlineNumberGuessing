workspace "ASIO_Networking"
    configurations { "Debug", "Release" }
    location "build"

project "Server"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    files { "src/server.cpp" }
    includedirs { "asio" }

project "Client"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    files { "src/client.cpp" }
    includedirs { "asio" }
