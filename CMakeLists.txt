cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("tusk1")

set(Boost_INCLUDE_DIR "C:\\Users\\Dorim\\boost_1_83_0")
set(Boost_LIBRARY_DIR "C:\\Users\\Dorim\\boost_1_83_0\\stage\\lib")
find_package(Boost COMPONENTS REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_executable (tusk1 "tusk1.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET tusk1 PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(tusk1 ${Boost_LIBRARIES})

if (MINGW)
target_link_libraries(tusk1 ws2_32)
endif()