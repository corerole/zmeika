cmake_minimum_required (VERSION 4.3.2)

if (MSVC)
  if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
  endif()
endif()

set(USE_HANDMADE_MODULES_STD ON)
if(NOT USE_HANDMADE_MODULES_STD)
	set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
	set(CMAKE_CXX_SCAN_FOR_MODULES ON)
	set(CMAKE_CXX_MODULE_STD ON)
endif()


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS NO)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project ("zmeika" LANGUAGES CXX)
add_executable (${PROJECT_NAME})
include("${CMAKE_CURRENT_LIST_DIR}/dep/dep.cmake")
target_sources(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/main.cpp")
add_compile_options(/FS)
target_link_libraries(${PROJECT_NAME} PRIVATE dwmapi Shcore)