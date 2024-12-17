project(win-spout)

set(CMAKE_CXX_STANDARD 11)

if(MSVC)
	include_directories(deps/Spout2/SPOUTSDK/SpoutLibrary)
	include_directories(deps/Spout2/SPOUTSDK/SpoutDirectX/SpoutDX)
	link_directories(deps/Spout2/BUILD/Binaries/x64)
endif()

set(win-spout_HEADERS
	source/win-spout.h
)

set(win-spout_SOURCES
	source/win-spout.cpp
	source/win-spout-source.cpp
)

add_library(win-spout MODULE
	${win-spout_SOURCES}
	${win-spout_HEADERS})
add_library(OBS::spout ALIAS win-spout)

include_directories(
	"${CMAKE_SOURCE_DIR}/libobs"
)

set(SPOUTDX_LIB "${CMAKE_CURRENT_SOURCE_DIR}/deps/Spout2/BUILD/Binaries/x64/SpoutDX.lib")
target_link_libraries(win-spout PRIVATE
	OBS::libobs
	${SPOUTDX_LIB}
	OBS::w32-pthreads
)

set(MODULE_DESCRIPTION "Spout2 plugin")

function(install_spout_dependencies)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(_src_suffix "x64")
	else()
		set(_src_suffix "win32")
	endif()

	install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/deps/Spout2/BUILD/Binaries/${_src_suffix}/Spout.dll" DESTINATION "${OBS_PLUGIN_DESTINATION}")
	install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/deps/Spout2/BUILD/Binaries/${_src_suffix}/SpoutLibrary.dll" DESTINATION "${OBS_PLUGIN_DESTINATION}")
	install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/deps/Spout2/BUILD/Binaries/${_src_suffix}/SpoutDX.dll" DESTINATION "${OBS_PLUGIN_DESTINATION}")
endfunction()

set_target_properties(win-spout PROPERTIES FOLDER "plugins")
set_target_properties_obs(win-spout PROPERTIES FOLDER plugins/win-spout PREFIX "")

install_spout_dependencies()
