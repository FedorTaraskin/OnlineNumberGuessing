function sharedThings()
	kind "ConsoleApp"

	--Language
	language "C++"
	cppdialect "C++20"
	cdialect "C17"

--Source files
	targetdir "%{wks.location}/build/bin/%{cfg.system}/%{cfg.buildcfg}"
	files { "%{wks.location}/src/shared/*", "%{wks.location}/src/shared/**" }
	includedirs { "%{wks.location}/external/cereal/include",
				  "%{wks.location}/external/asio/asio/include",
				  "%{wks.location}/src/**" }

	--Miscellaneous
	fpu "Hardware"
	defines {	"ASIO_STANDALONE",
				--"HUGE_NUMBER_GEN" --Uncomment for a more sophisticated rng algorithm.
	}

	--Debug and Release differences
	filter "configurations:Debug"
		defines { "_DEBUG" }
		symbols "On" --Overriden for vs2017+ later
		optimize "Off"
		linktimeoptimization "Off"
		intrinsics "off"
		inlining "Disabled"
	filter { "configurations:Debug", "action:vs2017 or 2019 or 2022" }
		symbols "Full"

	filter "configurations:Release"
		defines { "_RELEASE"}
		symbols "Off"
		optimize "Speed"
		linktimeoptimization "On"
		floatingpoint "Fast"
		intrinsics "on"
		inlining "Auto"
		--[[sanitize {  --Compiler checks for everything
					--"Address", --Commented out due to Visual Studio not compiling
					"Fuzzer",
					"Thread",
					"UndefinedBehavior"
						 }]]--

	filter "system:windows"
		links { "ws2_32", "mswsock" }  -- Required Windows sockets libraries
		defines { "_WIN32_WINNT=0x0A00" }  -- Windows 10 or newer

	filter { "toolset:msc" }
		flags { "MultiProcessorCompile" }

	filter { "action:vs*", "toolset:not clang" }
		buildoptions { "/Zc:__cplusplus" }
		print ">>LOG: Applying __cplusplus fix"

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
platforms { "Default" }
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
files {	"%{wks.location}/src/client/**.hpp",
		"%{wks.location}/src/client/**.cpp" }
