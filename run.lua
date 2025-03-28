local os_target = os.host()

if os_target == "windows" then
    print("Generating Visual Studio project...")
    os.execute("premake5 vs2022")
    print("Open the generated project in Visual Studio to build and run.")
elseif os_target == "linux" or os_target == "macosx" then
    print("Generating Makefile...")
    os.execute("premake5 gmake")
    print("Building the project...")
    os.execute("make")
    print("Running the server...")
    os.execute("./bin/Debug/Server &")
    print("Running the client...")
    os.execute("./bin/Debug/Client")
else
    print("Unsupported OS: " .. os_target)
end
