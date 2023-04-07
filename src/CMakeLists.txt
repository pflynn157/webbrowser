set(SRC
    canvas.cpp
    dom_block.cpp
    main.cpp
    parser.cpp
    window.cpp
)

add_executable(wb ${SRC})

target_link_libraries(wb PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Xml
)

