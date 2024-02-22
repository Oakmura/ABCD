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
IncludeDir["stb_image"] = "ABCD/vendor/stb_image"

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
	kind "StaticLib"
	language "C++"
  cppdialect "C++17"
  staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  pchheader "abpch.h"
  pchsource "ABCD/src/abpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
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
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

  links 
	{ 
		"GLFW",
    "Glad",
    "ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"AB_PLATFORM_WINDOWS",
			"AB_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
      "_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines "AB_DEBUG"
    runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AB_RELEASE"
    runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "AB_DIST"
    runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
  staticruntime "on"

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
		systemversion "latest"

		defines
		{
			"AB_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "AB_DEBUG"
    runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AB_RELEASE"
    runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "AB_DIST"
    runtime "Release"
		optimize "on"