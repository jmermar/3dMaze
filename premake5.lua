workspace "3DMaze"
    configurations { "Release" }
    startproject "3DMaze"
    architecture "x64"
    location "build"
project "3DMaze"
    kind "ConsoleApp"
    language "C"
    location "%{wks.location}"
    targetdir "%{wks.location}"

    includedirs { "src" }
    files { "src/*.c" }
    links { "SDL2", "SDL2main" }

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
    filter "configurations:*"
    postbuildcommands {
        "{COPYDIR} ../res ."
    }
    