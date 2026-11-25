if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE VK_USE_PLATFORM_WIN32_KHR)
endif()

set(GLFW_DIR "${CMAKE_CURRENT_LIST_DIR}")
target_sources(
	${PROJECT_NAME} PUBLIC
	FILE_SET CXX_MODULES 
	BASE_DIRS ${GLFW_DIR}
	FILES
		"${GLFW_DIR}/glfw.cppm"
		"${GLFW_DIR}/glfw_base.cppm"
		"${GLFW_DIR}/glfw_enums.cppm"
)

set(WINDOW_MANAGER "")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	set(WINDOW_MANAGER "__WINDOWS")
	target_sources(
		${PROJECT_NAME} PUBLIC
		FILE_SET CXX_MODULES 
		BASE_DIRS ${GLFW_DIR}
		FILES
			"${GLFW_DIR}/glfw_win32.cppm"
	)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	message(FATAL_ERROR "Unimplemented")
	#if()
		# set(WINDOW_MANAGER "__X11")
		# target_sources(
		#	${PROJECT_NAME} PUBLIC
		#	FILE_SET CXX_MODULES 
		#	BASE_DIRS ${GLFW_DIR}
		#	FILES
		#	"${GLFW_DIR}/glfw_x11.cppm"
		# )
	#else()
	#	set(WINDOW_MANAGER "__WAYLAND")
		# target_sources(
		#	${PROJECT_NAME} PUBLIC
		#	FILE_SET CXX_MODULES 
		#	BASE_DIRS ${GLFW_DIR}
		#	FILES
		#	"${GLFW_DIR}/glfw_wayland.cppm"
		# )
	#endif()
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
	message(FATAL_ERROR "Unimplemented")
	#set(WINDOW_MANAGER "__ANDROID")
		# target_sources(
		#	${PROJECT_NAME} PUBLIC
		#	FILE_SET CXX_MODULES 
		#	BASE_DIRS ${GLFW_DIR}
		#	FILES
		#	"${GLFW_DIR}/glfw_Android.cppm"
		# )
else()
	message(FATAL_ERROR "Unsupported OS")
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE "${WINDOW_MANAGER}")