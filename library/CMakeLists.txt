file(GLOB_RECURSE SOURCE_LIST "${LinkedList_SOURCE_DIR}/library/*.c")
file(GLOB_RECURSE HEADER_LIST "${LinkedList_SOURCE_DIR}/include/*.h")

add_library(LinkedList STATIC ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(LinkedList PUBLIC 
    ${LinkedList_SOURCE_DIR}/include
)

set_property(TARGET LinkedList PROPERTY C_STANDARD 11)
set_target_properties(LinkedList PROPERTIES LINKER_LANGUAGE C POSITION_INDEPENDENT_CODE ON)
