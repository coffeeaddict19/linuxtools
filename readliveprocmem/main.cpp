#include <fstream>
#include <iostream>
#include <sys/uio.h>
#include <string>
#include <vector>
#include <optional>

void write_tofile(const char* buf, size_t length, const char* filename){
  std::ofstream outfile(filename, std::ios::out | std::ios::binary);
  outfile.write(buf, length);
  outfile.close();
}

void printerror(){
  switch (errno) {
      case EINVAL:
        std::cerr << "ERROR: INVALID ARGUMENTS.\n";
        break;
      case EFAULT:
        std::cerr << "ERROR: UNABLE TO ACCESS TARGET MEMORY ADDRESS.\n";
        break;
      case ENOMEM:
        std::cerr << "ERROR: UNABLE TO ALLOCATE MEMORY.\n";
        break;
      case EPERM:
        std::cerr << "ERROR: INSUFFICIENT PRIVILEGES TO TARGET PROCESS.\n";
        break;
      case ESRCH:
        std::cerr << "ERROR: PROCESS DOES NOT EXIST.\n";
        break;
      default:
        std::cerr << "ERROR: Unknown: " << errno << '\n';
  }
}

bool readmemory_from_startingaddress(char* buf, pid_t pid, void* starting_address, size_t count){
  struct iovec local[1];
  struct iovec remote[1];
  local[0].iov_base = buf;
  local[0].iov_len = count;
  remote[0].iov_base = starting_address;
  remote[0].iov_len = count;
  auto nread = process_vm_readv(pid, local, 1, remote, 1, 0);
  if(count == (size_t)nread){
    std::cout << count << " bytes read from pid " << pid << '\n';
    return true;
  }else if(0 == nread){
    std::cout << "no bytes read but no error either\n";
    return false;
  }else{
    printerror();
    return false;
  }
}

int main(int argc, char* argv[]){
  if(argc != 4){
    std::cout << "Expected 3 arguments: pid start-end filename\n";
    return 0;
  }

  int pid = 0;

  try{
      pid = std::atoi(argv[1]);
  }catch(std::exception& ex){
      std::cerr<<"Failed parsing pid input " << ex.what() << '\n';
      return 0;
  }

  void* start = nullptr;
  void* end = nullptr;
  const auto parsecount = sscanf(argv[2], "%p-%p", &start, &end);
  if(parsecount != 2){
      std::cerr<<"Input " << argv[2] << " sscanf return: " << parsecount << " Expected two pointer addresses seperated by hyphen.\n";
      return 0;
  }

  const size_t buffer_length = (size_t)end-(size_t)start;

  std::vector<char>* buffer = nullptr;
  try
  {
      buffer = new std::vector<char>(buffer_length, 0);
  }
  catch(const std::exception& e)
  {
      std::cerr << "Failed to allocate buffer of size " << buffer_length << " error: " << e.what() << '\n';
      return 0;
  }
  
  const auto success = readmemory_from_startingaddress(
      (*buffer).data(), 
      pid, 
      start, 
      buffer_length
      );
  if(success){
      std::cout << "bytes read: " << buffer_length << '\n';
      write_tofile((*buffer).data(), (*buffer).size(), argv[3]);
      std::cout << (*buffer).size() << " bytes written to: " << argv[3] << '\n';
  }
  delete buffer;
  return 0;
}