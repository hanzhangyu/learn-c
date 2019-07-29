/**
 * @file 使用 daemon 写日志
 * @usage 
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

void daemonize() {
  // region 防止父进程为组长
  pid_t pid;
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid > 0) {
    exit(0);
  }
  // endregion

  // 设置新的会话
  setsid();

  // region change cmd
  if (chdir("/") < 0) {
    perror("chdir");
    exit(1);
  }
  // endregion

  // 防止被继承的umask影响
  umask(0);

  // region 关闭0/1/2
  close(0);
  open("/dev/null", O_RDWR); // 将null设置为0
  dup2(0, 1);
  dup2(0, 2);
  // endregion
}

int main(int argc, char *argv[]) {
  daemonize();

  int fd;
  time_t t;
  char buf[1024];

  if((fd = open("/tmp/daemon.log", O_CREAT | O_APPEND | O_RDWR, 0777)) < 0) {
    perror("open");
    exit(1);
  }
  for (int i = 0; i < 10; ++i) {
    time(&t); // 得到距离1970.1.1 00:00:00 的秒数
    ctime_r(&t, buf); // 把秒数转为当前时间
    printf("%d\n", fd);
    if(write(fd, buf, strlen(buf)) < 0) {
      perror("write");
      exit(1);
    }
    sleep(1);
  }
  close(fd);
  return 0;
}