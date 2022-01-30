add_executable(addressrange main.cpp)

target_compile_features(addressrange PRIVATE cxx_std_11)

target_compile_options(addressrange PRIVATE -Werror -Wall -Wextra)