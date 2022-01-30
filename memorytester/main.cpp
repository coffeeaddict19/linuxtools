#include <iostream>
#include <array>
#include <string.h>

void trytoallocate(char*& bytes, const unsigned long long byte_count, const char fillchar){
    std::cout << "fill character: " << fillchar << " count: " << byte_count << "\n";
    const char nullchar = '\0';
    try
    {
        bytes = new char[byte_count];
        memset(bytes, (int)fillchar, byte_count);
        bytes[byte_count-1] = nullchar;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << " Failed allocation. Count: " << byte_count << '\n';
        bytes = nullptr;
    }
}

int main(){
    std::cout << "Hit enter with nothing to exit. Or type in an integral number of bytes to try to allocate.\n";
    bool allocnewmem = true;
    char* bytes = nullptr;
    const std::array<char, 26> alphabet = {{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}};
    size_t alphabet_index = 0;
    while (allocnewmem)
    {
        std::string inputline = "";
        std::getline(std::cin, inputline);
        if(inputline.empty()){
            allocnewmem = false;
        }
        
        if(bytes != nullptr){
            delete []bytes;
            bytes = nullptr;
        }

        if(allocnewmem){
            const unsigned long long count = std::stoull(inputline);
            if(count == 0){
                return 0;
            }

            trytoallocate(bytes, count, alphabet.at(alphabet_index));

            if(alphabet_index+1 >= alphabet.size()){
                alphabet_index = 0;
            }else{
                alphabet_index = alphabet_index + 1;
            }
        }
    }

    return 0;
}