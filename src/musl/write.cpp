#include <os>
#include "common.hpp"
#include <posix/fd_map.hpp>

// The actual syscall
static long sys_write(int fd, char* str, size_t len) {

  if (fd == 1 or fd == 2)
  {
    OS::print(str, len);
    return len;
  }

  try {
    auto& fildes = FD_map::_get(fd);
    return fildes.write(str, len);
  }
  catch(const FD_not_found&) {
    return -EBADF;
  }
}

// The syscall wrapper, using strace if enabled
extern "C"
long syscall_SYS_write(int fd, char* str, size_t len) {
  //return strace(sys_write, "write", fd, str, len);
  return sys_write(fd, str, len);
}
