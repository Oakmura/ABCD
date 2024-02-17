workspace "ABCD"
	architecture "x64"
  startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "ABCD"
	location "ABCD"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"AB_PLATFORM_WINDOWS",
			"AB_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "AB_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AB_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "AB_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"ABCD/vendor/spdlog/include",
		"ABCD/src"
	}

	links
	{
		"ABCD"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"AB_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "AB_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AB_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "AB_DIST"
		optimize "On"