
-- Library
-------------------------------------------

project "Muon_Core"
	local ProjectRoot = os.getcwd()

	language "C++"
	targetname "Muon"
	targetdir (SolutionRoot.."/bin/lib")

	files {
       ProjectRoot.."/src/**.cpp",
       ProjectRoot.."/include/**.hpp",
    }

	defines { "MUON_EXPORTS" }

	filter "*DLL"
		if os.is("windows") then
			postbuildcommands { string.gsub("copy "..SolutionRoot.."/bin/lib/Muon*.dll "..SolutionRoot.."/bin/", "/", "\\") }
		end

	filter {}
