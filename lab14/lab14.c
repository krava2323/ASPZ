#include <stdio.h>
#include <sys/timerfd.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdint.h> 
int main() {
    int timer_fd = timerfd_create(CLOCK_REALTIME, 0);
    if (timer_fd == -1) {
        perror("timerfd_create");
        return 1;
    }

    struct itimerspec its;
    its.it_value.tv_sec = 1;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 1;
    its.it_interval.tv_nsec = 0;

    if (timerfd_settime(timer_fd, 0, &its, NULL) == -1) {
        perror("timerfd_settime");
        close(timer_fd);
        return 1;
    }

    printf("Timer started. Waiting for ticks...\n");

    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(timer_fd, &readfds);

       
        int ready = select(timer_fd + 1, &readfds, NULL, NULL, NULL);

        if (ready == -1) {
            perror("select");
            close(timer_fd);
            return 1;
        }

        if (FD_ISSET(timer_fd, &readfds)) {
            uint64_t expirations;
           
            ssize_t s = read(timer_fd, &expirations, sizeof(expirations));
            if (s != sizeof(expirations)) {
                perror("read timerfd");
                close(timer_fd);
                return 1;
            }
            printf("Tick! (Expirations: %llu)\n", (unsigned long long)expirations);
        }
    }

    
    close(timer_fd);
    return 0;
}
