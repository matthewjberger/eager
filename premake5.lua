-- premake5.lua

-- Helper functions
function use_windows_slashes(unixPath)
    return (string.gsub(unixPath, "/", "\\") or "")
end

function quote(str)
    return '"' .. str .. '"'
end

local name = "ProjectName"

workspace "Ogre"
    configurations { "Debug", "Release" }
    location "build"
    project(name)
        local target = "bin" .. "/%{cfg.buildcfg}"
        targetdir(target)
        local srcDir = "src/"
        kind "WindowedApp"
        language "C++"
        links{
          "OgreOverlay",
          "OgreMain",
          "OIS",
          "boost_system"
        }
        includedirs({srcDir, srcDir .. "**" })
        files({ srcDir .. "**.h", srcDir .. "**.cpp" })

        filter "configurations:Debug"
            defines "DEBUG"
            flags "Symbols"

        filter "configurations:Release"
            defines "NDEBUG"
            optimize "On"

        configuration { "gmake" }
        includedirs {
          "/usr/local/include/OGRE",
          "/usr/local/include/OGRE/**",
          "/usr/include/OIS",
          "/usr/include/OIS/**"
        }
        linkoptions { "-L/usr/local/lib/", "-L/usr/local/lib/OGRE/", "-L/usr/lib/x86_64-linux-gnu" }
        -- Uncomment this line if you want to use c++11
        -- buildoptions { "-std=c++11" }

        -- Copy shaders to the output directory
        local config_path = "../" .. srcDir .. "config"
        local output_path = "../bin/%{cfg.buildcfg}"
        local copy_configs_pbc = "cp -r " .. config_path .. "/* " .. output_path
        postbuildcommands({ copy_configs_pbc })

