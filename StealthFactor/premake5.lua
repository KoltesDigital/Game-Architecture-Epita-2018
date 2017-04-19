characterset "Unicode"

cppdialect "C++11"

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
	"Linux32",
	"Linux64",
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

filter "platforms:Linux*"
	system "Linux"

filter "platforms:Linux32"
	architecture "x86"

filter "platforms:Linux64"
	architecture "x64"

filter "platforms:Win*"
	system "Windows"

filter "platforms:Win32"
	architecture "x86"

filter "platforms:Win64"
	architecture "x64"

function runsWithDependencies()
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

	filter "platforms:Linux*"
		-- TODO links

	filter "platforms:Linux32"
		debugdir "dep/linux/bin32"
		libdirs {
			"dep/linux/lib32",
		}

	filter "platforms:Linux64"
		debugdir "dep/linux/bin64"
		libdirs {
			"dep/linux/lib64",
		}

	filter "platforms:Win*"
		links {
			"winmm",
			"ws2_32",
		}

	filter "platforms:Win32"
		debugdir "dep/windows/bin32"
		libdirs {
			"dep/windows/lib32",
		}

	filter "platforms:Win64"
		debugdir "dep/windows/bin64"
		libdirs {
			"dep/windows/lib64",
		}
end

workspace "StealthFactor"
	language "C++"
	location "build"
	startproject "Game"

project "Platform"
	files {
		"code/platform/**",
	}
	includedirs {
		"code",
		"dep/include",
	}
	kind "StaticLib"
	rtti "Off"

	filter "platforms:Linux*"
		files {
			"code/platform-linux/**",
		}

	filter "platforms:Win*"
		files {
			"code/platform-win/**",
		}

project "Engine"
	files {
		"code/engine/**",
	}
	includedirs {
		"code",
		"dep/include",
	}
	kind "StaticLib"
	-- rtti "Off"

project "Game"
	debugargs {
		"-data",
		"../../../data",
	}
	files {
		"code/game/**",
	}
	includedirs {
		"code",
		"dep/include",
	}
	links {
		"Engine",
		"Platform",
	}
	kind "ConsoleApp"
	-- rtti "Off"
	runsWithDependencies()

project "Sandbox"
	files {
		"code/sandbox/**",
	}
	includedirs {
		"code",
		"dep/include",
	}
	links {
		"Engine",
	}
	kind "ConsoleApp"
	-- rtti "Off"
	runsWithDependencies()
