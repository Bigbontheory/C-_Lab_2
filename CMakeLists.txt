cmake_minimum_required (VERSION 3.10)

# Настройка для Visual Studio (Hot Reload и отладка)
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("C++_Lab_2")

# Стандарт C++17 для работы шаблонов и move-семантики
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем папки с кодом и тестами
add_subdirectory(src)
add_subdirectory(tests)