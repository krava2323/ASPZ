#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_permissions(mode_t mode) {
    char perms[11] = "----------";

    if (S_ISDIR(mode)) perms[0] = 'd';  
    if (mode & S_IRUSR) perms[1] = 'r'; 
    if (mode & S_IWUSR) perms[2] = 'w'; 
    if (mode & S_IXUSR) perms[3] = 'x'; 
    if (mode & S_IRGRP) perms[4] = 'r'; 
    if (mode & S_IWGRP) perms[5] = 'w'; 
    if (mode & S_IXGRP) perms[6] = 'x'; 
    if (mode & S_IROTH) perms[7] = 'r';
    if (mode & S_IWOTH) perms[8] = 'w'; 
    if (mode & S_IXOTH) perms[9] = 'x'; 

    printf("%s ", perms);
}

void print_file_info(const char *file_name) {
    struct stat file_stat;

    if (stat(file_name, &file_stat) == -1) {
        perror("stat");
        return;
    }

    
    print_permissions(file_stat.st_mode);

    
    printf("%ld ", file_stat.st_nlink);

    
    struct passwd *pwd = getpwuid(file_stat.st_uid);
    printf("%s ", pwd ? pwd->pw_name : "UNKNOWN");

    
    struct group *grp = getgrgid(file_stat.st_gid);
    printf("%s ", grp ? grp->gr_name : "UNKNOWN");

    
    printf("%ld ", file_stat.st_size);

   
    char timebuf[256];
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&file_stat.st_mtime));
    printf("%s ", timebuf);

    
    printf("%s\n", file_name);
}

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        
        if (entry->d_name[0] == '.')
            continue;

        
        print_file_info(entry->d_name);
    }

    closedir(dir);
    return 0;
}
