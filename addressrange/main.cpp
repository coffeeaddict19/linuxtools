#include <iostream>

int main(int argc, char* argv[]){
    if(argc != 2){
        std::cout << "Expected one arg passed in by user to be address range ex 7ff7bc084000-7ff7c0000000\n";
        return 0;
    }

    void* start = nullptr;
    void* end = nullptr;
    const auto parsecount = sscanf(argv[1], "%p-%p", &start, &end);
    if(parsecount != 2){
        std::cerr<<"Input " << argv[1] << " sscanf return: " << parsecount << " Expected two pointer addresses seperated by hyphen.\n";
        return 0;
    }

    std::cout << (size_t)start << ' ' << (size_t)end-(size_t)start << '\n';
    
    return 0;
}