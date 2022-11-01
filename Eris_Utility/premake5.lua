project "Eris_Utility"
	kind "StaticLib"
	staticruntime "off"
	language "C++"

	targetdir ("lib/" .. outputdir .. "/%{prj.name}")
	objdir ("lib_int/" .. outputdir .. "/%{prj.name}")

	files {
		"include/%{prj.name}/**.h",
		"src/**.cpp",
		"src/**.tpp"
	}

	includedirs {
		"include"
	}

	disablewarnings {
		-- 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
		"4251" -- project will be specifically compiled for different compilers separately (will solve issue if I'll decide otherwise)
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"

	filter "configurations:Dist"
		optimize "On"
