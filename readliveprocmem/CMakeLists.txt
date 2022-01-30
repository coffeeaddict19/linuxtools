add_executable(readliveprocmem main.cpp)

target_compile_features(readliveprocmem PRIVATE cxx_std_17)

target_compile_options(readliveprocmem PRIVATE -Werror -Wall -Wextra)