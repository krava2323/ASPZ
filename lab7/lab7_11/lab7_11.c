#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

typedef struct {
    int hour;        
    int minute;      
    char command[256]; 
} CronJob;

void execute_task(const char* command) {

    system(command);
    printf("Executed command: %s\n", command);
}

int check_time_match(int hour, int minute) {
    time_t t;
    struct tm* tm_info;


    time(&t);
    tm_info = localtime(&t);


    if (tm_info->tm_hour == hour && tm_info->tm_min == minute) {
        return 1;
    }
    return 0;
}

int main() {

    CronJob jobs[] = {
        {13, 53, "echo 'Task 1: Run at 14:30'"},
        {17, 07, "echo 'Task 2: Run at 16:45'"},
        {18, 0, "echo 'Task 3: Run at 18:00'"},
    };


    int job_count = sizeof(jobs) / sizeof(jobs[0]);


    while (1) {
        for (int i = 0; i < job_count; i++) {
            if (check_time_match(jobs[i].hour, jobs[i].minute)) {
                execute_task(jobs[i].command);
            }
        }


        sleep(60);  
    }

    return 0;
}
