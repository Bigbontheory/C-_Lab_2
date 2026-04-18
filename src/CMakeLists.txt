# 1. Создаем интерфейсную библиотеку (так как у нас шаблоны)
add_library(seq_lib INTERFACE)

# 2. Указываем, где лежат хедеры (текущая папка src)
target_include_directories(seq_lib INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 3. Создаем исполняемый файл из main.cpp
# Теперь main.cpp компилируется именно здесь
add_executable(main_app main.cpp)

# 4. Связываем main_app с нашей библиотекой шаблонов
# Это позволит main.cpp делать #include "arraysequence.hpp" и т.д.
target_link_libraries(main_app PRIVATE seq_lib)