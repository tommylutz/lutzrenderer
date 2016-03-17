SET(LIBREND_SRCS
    image_interface.h
    image_png.cpp
    image_png.h
    rend.cpp
    rend.h
    cursor.cpp
    cursor.h
    model.cpp
    model.h )

ADD_LIBRARY(librend STATIC
            ${LIBREND_SRCS} )

TARGET_INCLUDE_DIRECTORIES(librend PUBLIC
                           "${CMAKE_CURRENT_SOURCE_DIR}/"
                           "${CMAKE_CURRENT_SOURCE_DIR}/external_interfaces" )

ADD_SUBDIRECTORY(external_interfaces)
