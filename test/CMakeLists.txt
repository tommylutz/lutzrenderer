ADD_EXECUTABLE(rendtest.t.tsk
               rend.t.cpp
               image_mock.h )

TARGET_LINK_LIBRARIES(rendtest.t.tsk
                      librend gtest gmock gtest_main)

