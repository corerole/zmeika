set(STD_DIR "${CMAKE_CURRENT_LIST_DIR}")
if(USE_HANDMADE_MODULES_STD)
	if($<C_COMPILER_ID:CLANG>)
		set(CMAKE_CXX_STDLIB_MODULES_JSON "${STD_DIR}/modules.json")
	endif()

	target_sources(
		${PROJECT_NAME} PUBLIC
		FILE_SET CXX_MODULES 
		BASE_DIRS ${STD_DIR}
		FILES
			"${STD_DIR}/std.cppm"
			"${STD_DIR}/std.compat.cppm"
	)
endif()