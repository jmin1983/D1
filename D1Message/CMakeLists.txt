# Sources
file(GLOB SRCS_G "*.cpp")
MACRO_SOURCES_AUTO(SRCS ${SRCS_G})

# Headers
file(GLOB HDRS_G "*.h")
MACRO_HEADERS_AUTO(SRCS ${HDRS_G})

add_library(D1Message ${SRCS})
if(MSVC)
	target_precompile_headers(D1Message
	PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/D1Message.h>
	)
endif()

if(MSVC)
	set_target_properties (D1Message PROPERTIES FOLDER "D1" )
endif()

set_target_properties(D1Message
	PROPERTIES
	OUTPUT_NAME D1Message
)

target_include_directories(D1Message
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../B1>
)

if(WIN32)
	target_compile_definitions(D1Message PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
