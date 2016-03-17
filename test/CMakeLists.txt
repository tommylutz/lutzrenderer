ADD_EXECUTABLE(rendtest.t.tsk
image_mock.h
image_png.t.cpp
rend.t.cpp
model.t.cpp
cursor.t.cpp
)

TARGET_LINK_LIBRARIES(rendtest.t.tsk
                      png
                      librend gtest gmock gtest_main)


