add_executable(LinkedListTest main.c)

target_sources(LinkedListTest
    PRIVATE
        main.c
)

target_link_libraries(LinkedListTest PRIVATE LinkedList)
target_link_libraries(LinkedListTest PRIVATE unity)
