# Sources
file(GLOB SRCS_G "*.cpp")
MACRO_SOURCES_AUTO(SRCS ${SRCS_G})

# Headers
file(GLOB HDRS_G "*.h")
MACRO_HEADERS_AUTO(SRCS ${HDRS_G})

add_library(D1Data ${SRCS})
if(MSVC)
	target_precompile_headers(D1Data
	PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/D1Data.h>
	)
endif()

if(MSVC)
	set_target_properties (D1Data PROPERTIES FOLDER "D1" )
endif()

set_target_properties(D1Data
	PROPERTIES
	OUTPUT_NAME D1Data
)

target_include_directories(D1Data
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../B1>
)

if(WIN32)
	target_compile_definitions(D1Data PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
