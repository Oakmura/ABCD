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

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "ABCD/vendor/GLFW/include"
IncludeDir["Glad"] = "ABCD/vendor/Glad/include"
IncludeDir["ImGui"] = "ABCD/vendor/imgui"
IncludeDir["glm"] = "ABCD/vendor/glm"

group "Dependencies"
	include "ABCD/vendor/GLFW"
  include "ABCD/vendor/Glad"
  include "ABCD/vendor/imgui"
group ""

include "ABCD/vendor/GLFW"
include "ABCD/vendor/Glad"
include "ABCD/vendor/imgui"

project "ABCD"
	location "ABCD"
	kind "SharedLib"
	language "C++"
  staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  pchheader "abpch.h"
  pchsource "ABCD/src/abpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
    "%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

  links 
	{ 
		"GLFW",
    "Glad",
    "ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"AB_PLATFORM_WINDOWS",
			"AB_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
      "_CRT_SECURE_NO_WARNINGS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "AB_DEBUG"
    runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "AB_RELEASE"
    runtime "Release"
		optimize "On"

	filter "configurations:Distribution"
		defines "AB_DIST"
    runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
  staticruntime "off"

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
		"ABCD/src",
		"ABCD/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"ABCD"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"AB_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "AB_DEBUG"
    runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "AB_RELEASE"
    runtime "Release"
		optimize "On"

	filter "configurations:Distribution"
		defines "AB_DIST"
    runtime "Release"
		optimize "On"