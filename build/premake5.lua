function sharedThings()
	kind "ConsoleApp"
	
	--Language
    language "C++"
    cppdialect "C++20"
	cdialect "C17"

    --Source files
	targetdir "%{wks.location}/bin/%{cfg.system}/%{cfg.buildcfg}"
    files { "%{wks.location}/src/shared/*", "%{wks.location}/src/shared/**" }
	includedirs {	
		"%{wks.location}/external/asio/asio/include",
	  	"%{wks.location}/external/cereal/include/cereal", "%{wks.location}/external/cereal/include",
      	"%{wks.location}/src/**" 	
    }

	--Miscellaneous
	fpu "Hardware"
	defines { "ASIO_STANDALONE" }

	filter "configurations:Debug"
		defines { "_DEBUG" }
		symbols "On"
		optimize "Off"
		linktimeoptimization "Off"
		
	filter "configurations:Release"
		defines { "_RELEASE"}
		symbols "Off"
		optimize "Speed"
		linktimeoptimization "On"
		floatingpoint "Fast"
		sanitize { 
					--"Address", --Removed due to Visual Studio not compiling
					"Fuzzer", 
					"Thread", 
					"UndefinedBehavior" 
				 } --Compiler checks for everything

	filter "system:windows"
		links { "ws2_32", "mswsock" }  -- Required Windows sockets libraries
		defines { "_WIN32_WINNT=0x0A00" }  -- Windows 10 or newer

	filter "platforms:Win64"
		architecture "x64"

	filter "platforms:Win32"
		architecture "x32"

	filter "toolset:msc"
		flags { "MultiProcessorCompile" }
	 --[[Following lines are a stupid workaround,
	 for some reasion when making vs2022 files
	 every .cpp file gets marked as "excluded"
	 from the project. So, nothing gets built.]]--
	 --[[filter { "files:**.cpp", "files:**.hpp" }
        removeflags {"ExcludeFromBuild"}]]
     filter {}  -- Reset filter
end

workspace "OnlineNumberGuessing"
    configurations { "Debug", "Release" }
    platforms { "Win64", "Win32", "otherPlatorms" }
    location ".."

--More specifically: the server _frontend_
project "Server"
	sharedThings()
    files { "%{wks.location}/src/server/**.hpp", 
		 "%{wks.location}/src/server/**.cpp" }

--Again, _frontend_
--(though the client doesn't really have a "backend")
project "Client"
	sharedThings()
    files { "%{wks.location}/src/client/**.hpp",
		 "%{wks.location}/src/client/**.cpp" }

