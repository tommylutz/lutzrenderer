ADD_LIBRARY(librend STATIC
            rend.cpp 
            rend.h 
            image_interface.h)

TARGET_INCLUDE_DIRECTORIES(librend PUBLIC
                           "${CMAKE_CURRENT_SOURCE_DIR}/" )
