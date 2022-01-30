add_executable(memorytester main.cpp)

target_compile_features(memorytester PRIVATE cxx_std_11)

target_compile_options(memorytester PRIVATE -Werror -Wall -Wextra)