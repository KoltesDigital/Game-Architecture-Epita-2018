characterset "Unicode"

cppdialect "C++11"

debugargs {
	"-data",
	"../../../data",
}

defines {
	"dSINGLE",
}

flags {
	"FatalWarnings",
	"MultiProcessorCompile",
	"NoPCH",
}

configurations {
	"Debug",
	"Release",
}

platforms {
	"Win32",
	"Win64",
}

systemversion "10.0.16299.0"

warnings "Extra"

filter "configurations:Debug"
	defines {
		"DEBUG",
	}
	runtime "Debug"
	symbols "On"
	targetsuffix "-d"

filter "configurations:Release"
	defines {
		"NDEBUG",
	}
	optimize "On"
	runtime "Release"

filter "platforms:Win32"
	architecture "x32"
	debugdir "dep/windows/bin32"
	defines {
		"PLATFORM_WINDOWS",
		"WIN32", -- needed by ODE
	}
	libdirs {
		"dep/windows/lib32",
	}
	system "Windows"
	targetdir "bin32"

filter "platforms:Win64"
	architecture "x64"
	debugdir "dep/windows/bin64"
	defines {
		"PLATFORM_WINDOWS",
		"WIN32", -- needed by ODE
	}
	libdirs {
		"dep/windows/lib64",
	}
	system "Windows"
	targetdir "bin64"

workspace "StealthFactor"
	language "C++"
	location "build"

project "Engine"
	files {
		"code/engine/**",
	}
	includedirs {
		"code",
		"dep/include",
	}
	links {
		"winmm",
		"ws2_32",
	}
	location "build/Engine"
	kind "ConsoleApp"
	-- rtti "Off"

	filter "configurations:Debug"
		links {
			"ode_singled",
			"sfml-graphics-d",
			"sfml-network-d",
			"sfml-system-d",
			"sfml-window-d",
		}

	filter "configurations:Release"
		links {
			"ode_single",
			"sfml-graphics",
			"sfml-network",
			"sfml-system",
			"sfml-window",
		}
