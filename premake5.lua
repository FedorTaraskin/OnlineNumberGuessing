function sharedThings()
	kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    --targetdir "bin/%{cfg.buildcfg}" --Old version, doesn't  separate Server from Client
	targetdir "%{wks.location}/bin/%{prj.name}/%{cfg.buildcfg}"
    files { "src/shared/**.hpp",
            "src/shared/**.cpp" }

    --links { "asio" } --Perhaps needed?
	    
	includedirs { "asio" }

	filter "configurations:Debug"
		defines { "_DEBUG" }
		symbols "On"
		optimize "Off"
		
	filter "configurations:Release"
		defines { "_RELEASE"}
		symbols "Off" --Debugging symbols
		optimize "Speed"
		
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
