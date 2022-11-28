workspace "Eris_SFML_GameEngineProject"
	architecture "x86_64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.system}_%{cfg.buildcfg}-%{cfg.architecture}"

group "dependencies"
	include "Eris_Utility"
group ""

project "Eris_SFML_GameEngine"
	location "Eris_SFML_GameEngine"
	kind "ConsoleApp" --[[ I don't really want to play with WindowedApp rn ]]
	staticruntime "off"
	language "C++"
	cppdialect "C++17"
	
	defines { 
		"SFML_STATIC"
	}
	
	pchheader "ege_pch.h"
	pchsource "Eris_SFML_GameEngine/src/ege_pch.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin_int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/config/**.ini"
	}
	
	libdirs { 
		"Eris_SFML_GameEngine/dependencies/SFML/lib"
	}
	
	includedirs {
		"%{prj.name}/src",
		"Eris_Utility/include",
		"Eris_SFML_GameEngine/dependencies/SFML/include"
	}
	

	links {
		"Eris_Utility"
	}

	disablewarnings {
		4099 --[[ missing PDB, I'm not compiling SFML so it's normal ]]
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"EGE_PLATFORM_WINDOWS"
		}
	
	filter ""

	filter "configurations:Debug"
		defines "EGE_DEBUG"
		runtime "Debug"
		symbols "On"
		
		links {
			"winmm.lib",
			"opengl32.lib",
			"freetype.lib",
			"gdi32.lib",
			--[[ These are for audio: ]]
			"openal32.lib",
			"flac.lib",
			"vorbisenc.lib",
			"vorbisfile.lib",
			"vorbis.lib",
			"ogg.lib",
			--[[ audio end ]]
			"sfml-system-s-d.lib",
			"sfml-window-s-d.lib",
			"sfml-graphics-s-d.lib",
			"sfml-audio-s-d.lib"
		}

	filter "configurations:Release"
		defines "EGE_RELEASE"
		runtime "Release"
		optimize "On"
		
		links {
			"opengl32.lib",
			"freetype.lib",
			"winmm.lib",
			"gdi32.lib",
			--[[ These are for audio: ]]
			"flac.lib",
			"vorbisenc.lib",
			"vorbisfile.lib",
			"vorbis.lib",
			"ogg.lib",
			--[[ audio end ]]
			"sfml-system-s.lib",
			"sfml-window-s.lib",
			"sfml-graphics-s.lib",
			"sfml-audio-s.lib"
		}

	filter "configurations:Dist"
		defines "EGE_DIST"
		runtime "Release"
		optimize "On"
		
		links {
			"opengl32.lib",
			"freetype.lib",
			"winmm.lib",
			"gdi32.lib",
			--[[ These are for audio: ]]
			"flac.lib",
			"vorbisenc.lib",
			"vorbisfile.lib",
			"vorbis.lib",
			"ogg.lib",
			--[[ audio end ]]
			"sfml-system-s.lib",
			"sfml-window-s.lib",
			"sfml-graphics-s.lib",
			"sfml-audio-s.lib"
		}
