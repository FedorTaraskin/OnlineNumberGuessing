function sharedThings()
	kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
	cdialect "C17"
    --targetdir "bin/%{cfg.buildcfg}" --Old version, doesn't  separate Server from Client
	targetdir "%{wks.location}/bin/%{prj.name}/%{cfg.buildcfg}"
    files { "src/shared/**.hpp",
            "src/shared/**.cpp" }

	includedirs { "external/asio/asio/include/**", "external/asio/asio/include"}

	filter "configurations:Debug"
		defines { "_DEBUG" }
		symbols "On"
		optimize "Off"
		
	filter "configurations:Release"
		defines { "_RELEASE"}
		symbols "Off"
		optimize "Speed"
		floatingpoint "Fast"

	filter "system:windows"
		links { "ws2_32", "mswsock" }  -- Required Windows sockets libraries
		defines { "_WIN32_WINNT=0x0601" }  -- Windows 7 or newer
		
	 --[[Following lines are a stupid workaround,
	 for some reasion when making vs2022 files
	 every .cpp file gets marked as "excluded"
	 from the project. So, nothing gets built.]]--
	 --[[filter { "files:**.cpp", "files:**.hpp" }
        removeflags {"ExcludeFromBuild"}]]
     filter {}  -- Reset filter
	 	fpu "value"
end

workspace "OnlineNumberGuessing"
    configurations { "Debug", "Release" }
    location "."

--More specifically: the server _frontend_
project "Server"
	sharedThings()
    files { "src/server/**.hpp", 
			"src/server/**.cpp" }

--Again, _frontend_
--(though the client doesn't really have a "backend")
project "Client"
	sharedThings()
    files { "src/client/**.hpp",
			"src/client/**.cpp" }
