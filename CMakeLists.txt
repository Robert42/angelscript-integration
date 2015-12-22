cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

add_subdirectory(external/sdk/angelscript/projects/cmake)

if(TARGET angelscript)
  set(ANGELSCRIPT_TARGET angelscript)
else()
  set(ANGELSCRIPT_TARGET Angelscript)
endif()

target_include_directories(${ANGELSCRIPT_TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/sdk/angelscript/include)
target_compile_definitions(${ANGELSCRIPT_TARGET} PUBLIC AS_USE_NAMESPACE)


add_subdirectory(integration)
