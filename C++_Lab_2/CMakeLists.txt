# CMakeList.txt: проект CMake для C++_Lab_2; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (C++_Lab_2 "C++_Lab_2.cpp" "C++_Lab_2.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET C++_Lab_2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
