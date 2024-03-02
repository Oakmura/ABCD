workspace "ABCD"
	architecture "x86_64"
  startproject "Hazelnut"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

  flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "ABCD/vendor/GLFW/include"
IncludeDir["Glad"] = "ABCD/vendor/Glad/include"
IncludeDir["ImGui"] = "ABCD/vendor/imgui"
IncludeDir["glm"] = "ABCD/vendor/glm"
IncludeDir["stb_image"] = "ABCD/vendor/stb_image"
IncludeDir["entt"] = "ABCD/vendor/entt/include"
IncludeDir["yaml_cpp"] = "ABCD/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "ABCD/vendor/ImGuizmo"

group "Dependencies"
	include "ABCD/vendor/GLFW"
  include "ABCD/vendor/Glad"
  include "ABCD/vendor/imgui"
	include "ABCD/vendor/yaml-cpp"
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
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"
	}

  defines
  {
    "_CRT_SECURE_NO_WARNINGS",
  	"GLFW_INCLUDE_NONE",
  } 

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
    "%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}"
	}

  links 
	{ 
		"GLFW",
    "Glad",
    "ImGui",
		"yaml-cpp",
		"opengl32.lib"
	}
  
	filter "files:ABCD/vendor/ImGuizmo/**.cpp"
	  flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
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
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"ABCD"
	}

	filter "system:windows"
		systemversion "latest" 

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

project "Hazelnut"
	location "Hazelnut"
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
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"ABCD"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "AB_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AB_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AB_DIST"
		runtime "Release"
		optimize "on"