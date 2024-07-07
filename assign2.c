#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <fcntl.h>
#include <ctype.h>
#define BUFFER_SIZE 1024
#define MAX_LINE_LENGTH 256
typedef struct sort
{
    char name[100];
    double size;
} sort;
void printing(struct sort string[], int count)
{
    for (int i = 0; i < count; ++i)
    {
        printf("%s ", string[i].name);
    }
    printf("\n");
}

void sorting(struct sort string[], int count)
{
    char p[100];
    for (int i = 0; i < count; ++i)
    {
        for (int j = i + 1; j < count; ++j)
        {
            if (strcmp(string[i].name, string[j].name) > 0)
            {
                strcpy(p, string[i].name);
                strcpy(string[i].name, string[j].name);
                strcpy(string[j].name, p);
            }
        }
    }
}
void sorted(struct sort string[], int count)
{
    sort p;
    for (int i = 0; i < count; ++i)
    {
        for (int j = i + 1; j < count; ++j)
        {
            if (string[i].size < string[j].size)
            {
                p = string[i];
                string[i] = string[j];
                string[j] = p;
            }
        }
    }
}
void ls(struct sort arr[])
{
    struct dirent *d;
    DIR *dir = opendir(".");
    int i = 0, count = 0;
    while ((d = readdir(dir)) != NULL)
    {
        if (d->d_name[0] != '.')
        {
            strcpy(arr[i].name, d->d_name);
            i++;
            count++;
        }
    }
    closedir(dir);
    sorting(arr, count);
    printing(arr, count);
}
void lsl(struct sort arr[])
{
    struct dirent *d;
    DIR *dir = opendir(".");
    int i = 0, count = 0;
    while ((d = readdir(dir)) != NULL)
    {
        if (d->d_name[0] != '.')
        {
            strcpy(arr[i].name, d->d_name);
            i++;
            count++;
        }
    }
    sorting(arr, count);
    struct dirent *e;
    DIR *dr = opendir(".");
    int j = 0;
    while ((e = readdir(dr)) != NULL)
    {
        struct stat file_stat;
        struct group *gr;
        struct passwd *pw;
        char time_str[500];
        if (stat(arr[j].name, &file_stat) != -1)
        {
            printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
            printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
            printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
            printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
            printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
            printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
            printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
            printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
            printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
            printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
            printf("  %lu", file_stat.st_nlink);
            pw = getpwuid(file_stat.st_uid);
            printf(" %s", pw->pw_name);
            gr = getgrgid(file_stat.st_gid);
            printf("  %s", gr->gr_name);
            printf("  %5ld", file_stat.st_size);
            strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
            printf(" %s", time_str);
            printf(" %s", arr[j].name);
            printf("\n");
        }
        j++;
    }
    closedir(dir);
}
void lsal(struct sort arr[])
{
    struct dirent *d;
    DIR *dir = opendir(".");
    int i = 0, count = 0;
    while ((d = readdir(dir)) != NULL)
    {
        strcpy(arr[i].name, d->d_name);
        i++;
        count++;
    }
    sorting(arr, count);
    struct dirent *e;
    DIR *dr = opendir(".");
    int j = 0;
    while ((e = readdir(dr)) != NULL)
    {
        struct stat file_stat;
        struct group *gr;
        struct passwd *pw;
        char time_str[500];
        if (stat(arr[j].name, &file_stat) != -1)
        {
            printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
            printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
            printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
            printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
            printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
            printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
            printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
            printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
            printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
            printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
            printf("  %2lu", file_stat.st_nlink);
            pw = getpwuid(file_stat.st_uid);
            printf(" %s", pw->pw_name);
            gr = getgrgid(file_stat.st_gid);
            printf("  %s", gr->gr_name);
            printf("  %5ld", file_stat.st_size);
            strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
            printf(" %s", time_str);
            printf(" %s", arr[j].name);
            printf("\n");
        }
        j++;
    }
    closedir(dir);
}
void lsU(struct sort arr[])
{
    struct dirent *d;
    DIR *dir = opendir(".");
    while ((d = readdir(dir)) != NULL)
    {
        if (d->d_name[0] == '.')
        {
            continue;
        }
        printf("%s ", d->d_name);
    }
    closedir(dir);
    printf("\n");
}
void lsa(struct sort arr[])
{
    struct dirent *d;
    DIR *dir = opendir(".");
    int i = 0, count = 0;
    while ((d = readdir(dir)) != NULL)
    {
        strcpy(arr[i].name, d->d_name);
        i++;
        count++;
    }
    closedir(dir);
    sorting(arr, count);
    printing(arr, count);
}
void lsS(struct sort arr[])
{
    struct dirent *d;
    DIR *dir = opendir(".");
    int i = 0, count = 0;
    while ((d = readdir(dir)) != NULL)
    {
        struct stat file_stat;
        if (d->d_name[0] != '.')
        {
            strcpy(arr[i].name, d->d_name);
            if (stat(arr[i].name, &file_stat) != -1)
            {
                arr[i].size = file_stat.st_size;
            }
            i++;
            count++;
        }
    }
    closedir(dir);
    sorted(arr, count);
    printing(arr, count);
}
int copy(char *f1, char *f2)
{
    int i = 0;
    struct stat file_stat;
    char p;
    char buffer[1024];
    int files[2];
    ssize_t n;
    files[0] = open(f1, O_RDONLY);
    if (files[0] == -1)
    {
        printf("Error opening source file\n");
        i++;
    }
    if (stat(f2, &file_stat) != -1)
    {
        p = (S_ISDIR(file_stat.st_mode)) ? 'd' : '-';
    }
    if (p != 'd')
    {
        files[1] = open(f2, O_WRONLY | O_CREAT | O_RDONLY | S_IRUSR | S_IWUSR, 0644);
    }
    if (p == 'd')
    {
        strcat(f2, "/");
        strcat(f2, f1);
        files[1] = open(f2, O_WRONLY | O_CREAT | O_RDONLY | S_IRUSR | S_IWUSR, 0644);
    }
    if (files[1] == -1)
    {
        printf("Error opening destination file\n");
        close(files[0]);
        i++;
        return 0;
    }
    while ((n = read(files[0], buffer, BUFFER_SIZE)) > 0)
    {
        if (write(files[1], buffer, n) != n)
        {
            printf("Error writing to destination file\n");
            break;
        }
    }
    if (n == -1)
    {
        printf("Error reading from source file\n");
        return 0;
    }
    if (close(files[0]) == -1)
    {
        printf("Error closing source file\n");
        return 0;
    }
    if (close(files[1]) == -1)
    {
        printf("Error closing destination file\n");
        return 0;
    }
    if (i == 0)
        return 1;
    else
        return 0;
}
void cpv(char *f1, char *f2)
{
    printf("%s -> %s\n", f1, f2);
}
void cpn(char *f1, char *f2)
{
    struct stat file_stat;
    int flag = 0;
    char p;
    // if((d=readdir(dir))!=f2){copy(f1,f2);}
    // else return ;
    if (stat(f2, &file_stat) != -1)
    {
        p = (S_ISDIR(file_stat.st_mode)) ? 'd' : '-';
    }
    if (p == 'd')
    {
        struct dirent *d;
        DIR *dir = opendir(f2);
        while ((d = readdir(dir)) != NULL)
        {
            if (strcmp(f1, d->d_name) == 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            return;
        }
        else
            copy(f1, f2);
    }
    else
    {
        struct dirent *d;
        DIR *dir = opendir(".");
        while ((d = readdir(dir)) != NULL)
        {
            if (strcmp(f2, d->d_name) == 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            return;
        }
        else
            copy(f1, f2);
    }
}
void cpi(char *f1, char *f2)
{
    struct stat file_stat;
    char p;
    if (stat(f2, &file_stat) != -1)
    {
        p = (S_ISDIR(file_stat.st_mode)) ? 'd' : '-';
    }
    if (p == 'd')
    {
        int flag = 0;
        char *pole;
        struct dirent *d;
        DIR *dir = opendir(f2);
        while ((d = readdir(dir)) != NULL)
        {
            if (strcmp(f1, d->d_name) == 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            strcat(f2, "/");
            strcat(f2, f1);
            FILE *fil = fopen(f1, "r");
            if (fil != NULL)
            {
                printf("overwrite %s? (y/n [n])", f2);
                pole = readline("");
                if (!strcmp(pole, "y") || !strcmp(pole, "Y"))
                {
                    copy(f1, f2);
                }
                else
                    printf("not overwritten\n");
                return;
                fclose(fil);
            }
            else
                copy(f1, f2);
        }
        else
            copy(f1, f2);
        closedir(dir);
    }
    else
    {
        int flag = 0;
        char *pole;
        struct dirent *d;
        DIR *dir = opendir(".");
        while ((d = readdir(dir)) != NULL)
        {
            if (strcmp(f2, d->d_name) == 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            FILE *fil = fopen(f1, "r");
            if (fil != NULL)
            {
                printf("overwrite %s? (y/n [n])", f2);
                pole = readline("");
                if (!strcmp(pole, "y") || !strcmp(pole, "Y"))
                {
                    copy(f1, f2);
                }
                else
                    printf("not overwritten\n");
                return;
                fclose(fil);
            }
            else
                copy(f1, f2);
        }
        else
            copy(f1, f2);
        closedir(dir);
    }
}
void grep(char **f, int count, int point, int flag)
{
    for (int i = count; i < point; i++)
    {
        FILE *fp = fopen(f[i], "r");
        if (fp == NULL)
        {
            printf("Error: could not open file %s\n", f[i]);
        }
        else
        {
            char line[MAX_LINE_LENGTH];
            while (fgets(line, MAX_LINE_LENGTH, fp))
            {
                if (strstr(line, f[1]) != NULL)
                {
                    if (flag == 1)
                    {
                        printf("%s:%s", f[i], line);
                    }
                    else
                        printf("%s", line);
                }
            }
            fclose(fp);
        }
    }
}
void grepn(char **f, int count, int point, int flag)
{
    for (int i = count; i < point; i++)
    {
        int n = 0;
        FILE *fp = fopen(f[i], "r");
        if (fp == NULL)
        {
            printf("Error: could not open file %s\n", f[i]);
        }
        else
        {
            char line[MAX_LINE_LENGTH];
            while (fgets(line, MAX_LINE_LENGTH, fp))
            {
                n++;
                if (strstr(line, f[2]) != NULL)
                {
                    if (flag == 1)
                        printf("%s:%d:%s", f[i], n, line);
                    else
                        printf("%d:%s", n, line);
                }
            }
            fclose(fp);
        }
    }
}
void grepH(char **f, int count, int point, int flag)
{

    for (int i = count; i < point; i++)
    {
        int n = 0;
        FILE *fp = fopen(f[i], "r");
        if (fp == NULL)
        {
            printf("Error: could not open file %s\n", f[i]);
        }
        else
        {
            char line[MAX_LINE_LENGTH];
            while (fgets(line, MAX_LINE_LENGTH, fp))
            {

                n++;
                if (strstr(line, f[2]) != NULL)
                {

                    if (flag == 1)
                    {
                        printf("%s:%s", f[i], line);
                    }
                    else
                        printf("%s", line);
                }
            }
            fclose(fp);
        }
    }
}
void grepv(char **f, int count, int point, int flag)
{
    for (int i = count; i < point; i++)
    {
        int n = 0;
        FILE *fp = fopen(f[i], "r");
        if (fp == NULL)
        {
            printf("Error: could not open file %s\n", f[i]);
        }
        else
        {
            char line[MAX_LINE_LENGTH];
            while (fgets(line, MAX_LINE_LENGTH, fp))
            {
                n++;
                if (strstr(line, f[2]) == NULL)
                {
                    if (flag == 1)
                        printf("%s:%s", f[i], line);
                    else
                        printf("%s", line);
                }
            }
            fclose(fp);
        }
        printf("\n");
    }
}
void grepc(char **f, int count, int point, int flag)
{
    for (int i = count; i < point; i++)
    {
        int n = 0;
        FILE *fp = fopen(f[i], "r");
        if (fp == NULL)
        {
            printf("Error: could not open file %s\n", f[i]);
        }
        else
        {
            char line[MAX_LINE_LENGTH];
            while (fgets(line, MAX_LINE_LENGTH, fp))
            {
                if (strstr(line, f[2]) != NULL)
                {
                    n++;
                }
            }
            if (flag == 1)
                printf("%s:%d\n", f[i], n);
            else
                printf("%d\n", n);
            fclose(fp);
        }
    }
}

int main()
{
    char b[2000];
    char d[100];
    while (1)
    {
        int count = 0;
        char a[500];
        gethostname(a, 500);
        char c[500];
        getlogin_r(c, sizeof(c));
        getcwd(b, 2000);
        strcat(c, "@");
        strcat(c, a);
        strcat(c, ":∼");
        strcat(c, b);
        strcat(c, "$ ");
        char *input;
        input = readline(c);
        struct dirent *d;
        DIR *dir = opendir(".");
        while ((d = readdir(dir)) != NULL)
        {
            count++;
            if (d->d_name[0] != '.')
            {
                continue;
            }
        }
        if (strlen(input) != 0)
        {
            add_history(input);
        }
        sort arr[count];
        char *space[20];
        for (int k = 0; k < 20; k++)
        {
            space[k] = NULL;
        }
        int r = 0;
        char *token = strtok(input, " ");
        while (token != NULL)
        {
            space[r] = token;
            r++;
            token = strtok(NULL, " ");
        }
        if (space[0] != NULL)
        {
            if (!strcmp(space[0], "ls"))
            {
                if (r == 1)
                {
                    ls(arr);
                }
                else if (r == 2)
                {
                    if (strcmp(space[1], "-l") == 0)
                        lsl(arr);
                    else if (strcmp(space[1], "-al") == 0)
                        lsal(arr);
                    else if (strcmp(space[1], "-U") == 0)
                        lsU(arr);
                    else if (strcmp(space[1], "-a") == 0)
                        lsa(arr);
                    else if (strcmp(space[1], "-S") == 0)
                        lsS(arr);
                    else
                    {
                        printf("sh: command not found\n");
                    }
                }
                else
                {
                    printf("sh: command not found\n");
                }
            }
            else if (!strcmp(space[0], "cp"))
            {
                if (space[1][0] != '-')
                {
                    copy(space[1], space[2]);
                }
                else if (space[1][0] == '-')
                {
                    if (!strcmp(space[1], "-v"))
                    {
                        if (copy(space[2], space[3]))
                            cpv(space[2], space[3]);
                    }
                    if (!strcmp(space[1], "-n"))
                    {
                        cpn(space[2], space[3]);
                    }
                    if (!strcmp(space[1], "-i"))
                    {
                        cpi(space[2], space[3]);
                    }
                    if (!strcmp(space[1], "-nv"))
                    {
                        cpn(space[2], space[3]);
                        cpv(space[2], space[3]);
                    }
                }
            }
            else if (!strcmp(space[0], "mv"))
            {
                if (space[1][0] != '-')
                {
                    copy(space[1], space[2]);
                    remove(space[1]);
                }
                else if (space[1][0] == '-')
                {
                    if (!strcmp(space[1], "-v"))
                    {
                        if (copy(space[2], space[3]))
                        {
                            cpv(space[2], space[3]);
                            remove(space[2]);
                        }
                    }
                    if (!strcmp(space[1], "-n"))
                    {
                        cpn(space[2], space[3]);
                        remove(space[2]);
                    }
                    if (!strcmp(space[1], "-i"))
                    {
                        cpi(space[2], space[3]);
                        remove(space[2]);
                    }
                    if (!strcmp(space[1], "-nv"))
                    {
                        cpn(space[2], space[3]);
                        cpv(space[2], space[3]);
                        remove(space[2]);
                    }
                }
            }
            else if (!strcmp(space[0], "grep"))
            {
                int t = 0;
                if (space[1][0] != '-')
                {
                    if (space[3] != NULL)
                        t = 1;
                    grep(space, 2, r, t);
                }
                else if (space[1][0] == '-')
                {
                    if (!strcmp(space[1], "-n"))
                    {
                        if (space[4] != NULL)
                            t = 1;
                        grepn(space, 3, r, t);
                    }
                    if (!strcmp(space[1], "-H"))
                    {
                        grepH(space, 3, r, 1);
                    }
                    if (!strcmp(space[1], "-v"))
                    {
                        if (space[4] != NULL)
                            t = 1;
                        grepv(space, 3, r, t);
                    }
                    if (!strcmp(space[1], "-c"))
                    {
                        if (space[4] != NULL)
                            t = 1;
                        grepc(space, 3, r, t);
                    }
                }
            }
            else if (!strcmp(space[0], "ps"))
            {
                if (space[1] == NULL)
                {
                    struct dirent *entry;
                    DIR *dr;
                    FILE *fp;
                    dr = opendir("/proc");
                    int pid, ppid, pgrp, session, tty_nr, tpgid;
                    long long int utime;
                    long long int stime;
                    char path[1024], bath[1024], math[1024], line[2048], cmd[1024], state;
                    char ctty[100];
                    sprintf(math, "/proc/self/fd/0");
                    int f1 = open(math, O_RDONLY);
                    sprintf(ctty, "%s", ttyname(f1));
                    close(f1);
                    char p[256];
                    printf("%6s %s\t%8s %s\n", "PID", "TTY", "TIME", "CMD");
                    if (!dr)
                    {
                        perror("opendir");
                    }
                    else
                    {
                        while ((entry = readdir(dr)) != NULL)
                        {
                            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                            {
                                continue;
                            }
                            if (entry->d_type != DT_DIR)
                            {
                                continue;
                            }
                            if (!isdigit(entry->d_name[0]))
                            {
                                continue;
                            }
                            pid = atoi(entry->d_name);
                            snprintf(bath, sizeof(path), "/proc/%d/fd/0", pid);
                            int p = open(bath, O_RDONLY);
                            char atty[100];
                            sprintf(atty, "%s", ttyname(p));
                            if (!strcmp(atty, ctty))
                            {
                                if (pid == 0)
                                {
                                    continue;
                                }
                                snprintf(path, sizeof(path), "/proc/%d/stat", pid);
                                fp = fopen(path, "r");
                                if (!fp)
                                {
                                    continue;
                                }
                                fgets(line, sizeof(line), fp);
                                fclose(fp);
                                sscanf(line, "%d %s %*c %*d %*d %*d %*d %*d %*d %*u %*d %*d %*d %*d %lld %lld %*d %*d %*d %*d %*d %*d %*d %*d %*u %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",
                                       &pid, cmd, &utime, &stime);
                                printf("%6d %s\t", pid, ctty + 5);
                                time_t time = (stime + utime) / sysconf(_SC_CLK_TCK);
                                time_t hour, minute, second;
                                second = time % 60;
                                minute = (time / 60) % 60;
                                hour = (time / 3600) % 3600;
                                printf("%02ld:%02ld:%02ld %s\n", hour, minute, hour, cmd);
                            }
                        }
                    }
                }
                else if (space[1][0] == '-')
                {
                    if (!strcmp(space[1], "-e") || !strcmp(space[1], "-A"))
                    {
                        struct dirent *entry;
                        DIR *dir;
                        FILE *fp;
                        dir = opendir("/proc");
                        int pid, ppid, pgrp, session, tty_nr, tpgid;
                        long long int utime;
                        long long int stime;
                        char path[1024], bath[1024], math[1024], line[2048], cmd[1024], state;
                        char *ctty;
                        sprintf(math, "/proc/self/fd/0");
                        int f1 = open(math, O_RDONLY);
                        ctty = ttyname(f1);
                        close(f1);
                        char p[256];
                        printf("%6s %s\t%8s %s\n", "PID", "TTY", "TIME", "CMD");
                        if (!dir)
                        {
                            perror("opendir");
                        }
                        else
                        {
                            while ((entry = readdir(dir)) != NULL)
                            {
                                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                                {
                                    continue;
                                }
                                if (entry->d_type != DT_DIR)
                                {
                                    continue;
                                }
                                if (!isdigit(entry->d_name[0]))
                                {
                                    continue;
                                }
                                pid = atoi(entry->d_name);
                                snprintf(bath, sizeof(path), "/proc/%d/fd/0", pid);
                                int p = open(bath, O_RDONLY);
                                char atty[100];
                                sprintf(atty, "%s", ttyname(p));
                                if (!strcmp(atty, ctty))
                                {
                                    if (pid == 0)
                                    {
                                        continue;
                                    }
                                    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
                                    fp = fopen(path, "r");
                                    if (!fp)
                                    {
                                        continue;
                                    }
                                    fgets(line, sizeof(line), fp);
                                    fclose(fp);
                                    sscanf(line, "%d %s %*c %*d %*d %*d %*d %*d %*d %*u %*d %*d %*d %*d %lld %lld %*d %*d %*d %*d %*d %*d %*d %*d %*u %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",
                                           &pid, cmd, &utime, &stime);
                                    printf("%6d %s\t", pid, ctty + 5);
                                    utime = (int)(double)(utime + stime) / sysconf(_SC_CLK_TCK);
                                    printf("%02llu:%02llu:%02llu", (utime / 3600) % 3600, (utime / 60) % 60, utime % 60);
                                    printf(" %s\n", cmd);
                                }
                                else
                                {
                                    if (pid == 0)
                                    {
                                        continue;
                                    }
                                    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
                                    fp = fopen(path, "r");
                                    if (!fp)
                                    {
                                        continue;
                                    }
                                    fgets(line, sizeof(line), fp);
                                    fclose(fp);
                                    sscanf(line, "%d %s %*c %*d %*d %*d %*d %*d %*d %*u %*d %*d %*d %*d %lld %lld %*d %*d %*d %*d %*d %*d %*d %*d %*u %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",
                                           &pid, cmd, &utime, &stime);
                                    printf("%6d %s\t", pid, "?");
                                    utime = (int)(double)(utime + stime) / sysconf(_SC_CLK_TCK);
                                    printf("%02llu:%02llu:%02llu", (utime / 3600) % 3600, (utime / 60) % 60, utime % 60);
                                    printf(" %s\n", cmd);
                                }
                            }
                        }
                    }
                    if (!strcmp(space[1], "-t"))
                    {
                        struct dirent *entry;
                        DIR *dir;
                        FILE *fp;
                        dir = opendir("/proc");
                        int pid, ppid, pgrp, session, tty_nr, tpgid;
                        long long int utime;
                        long long int stime;
                        char path[1024], bath[1024], math[1024], line[2048], cmd[1024], state;
                        char ctty[100];
                        sprintf(math, "/proc/self/fd/0");
                        int f1 = open(math, O_RDONLY);
                        sprintf(ctty, "%s", ttyname(f1));
                        close(f1);
                        char p[256];
                        printf("%6s %s\t%s %11s %s\n", "PID", "TTY", "STAT", "TIME", "CMD");
                        if (!dir)
                        {
                            perror("opendir");
                        }
                        else
                        {
                            while ((entry = readdir(dir)) != NULL)
                            {
                                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                                {
                                    continue;
                                }
                                if (entry->d_type != DT_DIR)
                                {
                                    continue;
                                }
                                if (!isdigit(entry->d_name[0]))
                                {
                                    continue;
                                }
                                pid = atoi(entry->d_name);
                                snprintf(bath, sizeof(path), "/proc/%d/fd/0", pid);
                                int p = open(bath, O_RDONLY);
                                char atty[100];
                                sprintf(atty, "%s", ttyname(p));
                                if (!strcmp(atty, ctty))
                                {
                                    if (pid == 0)
                                    {
                                        continue;
                                    }
                                    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
                                    fp = fopen(path, "r");
                                    if (!fp)
                                    {
                                        continue;
                                    }
                                    fgets(line, sizeof(line), fp);
                                    fclose(fp);
                                    sscanf(line, "%d %s %c %*d %*d %*d %*d %*d %*d %*u %*d %*d %*d %*d %lld %lld %*d %*d %*d %*d %*d %*d %*d %*d %*u %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",
                                           &pid, cmd, &state, &utime, &stime);
                                    printf("%6d %s\t%c\t", pid, ctty + 5, state);
                                    time_t time = (stime + utime) / sysconf(_SC_CLK_TCK);
                                    time_t hour, minute, second;
                                    second = time % 60;
                                    minute = (time / 60) % 60;
                                    hour = (time / 3600) % 3600;
                                    printf("%02ld:%02ld:%02ld %s\n", hour, minute, hour, cmd);
                                }
                            }
                        }
                    }
                    if (!strcmp(space[1], "-d"))
                    {
                        struct dirent *entry;
                        DIR *dir;
                        FILE *fp;
                        dir = opendir("/proc");
                        int pid, ppid, pgrp, session, tty_nr, tpgid;
                        long long int utime;
                        long long int stime;
                        char path[1024], bath[1024], math[1024], line[2048], cmd[1024], state;
                        char *ctty;
                        sprintf(math, "/proc/self/fd/0");
                        int f1 = open(math, O_RDONLY);
                        ctty = ttyname(f1);
                        close(f1);
                        char p[256];
                        printf("%6s %s\t%8s %s\n", "PID", "TTY", "TIME", "CMD");
                        if (!dir)
                        {
                            perror("opendir");
                        }
                        else
                        {
                            while ((entry = readdir(dir)) != NULL)
                            {
                                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                                {
                                    continue;
                                }
                                if (entry->d_type != DT_DIR)
                                {
                                    continue;
                                }
                                if (!isdigit(entry->d_name[0]))
                                {
                                    continue;
                                }
                                pid = atoi(entry->d_name);
                                snprintf(bath, sizeof(path), "/proc/%d/fd/0", pid);
                                int p = open(bath, O_RDONLY);
                                char atty[100];
                                sprintf(atty, "%s", ttyname(p));
                                if (!strcmp(atty, ctty))
                                {
                                    if (pid == 0)
                                    {
                                        continue;
                                    }
                                    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
                                    fp = fopen(path, "r");
                                    if (!fp)
                                    {
                                        continue;
                                    }
                                    fgets(line, sizeof(line), fp);
                                    fclose(fp);
                                    int sid = getsid(pid);
                                    sscanf(line, "%d %s %*c %*d %*d %*d %*d %*d %*d %*u %*d %*d %*d %*d %lld %lld %*d %*d %*d %*d %*d %*d %*d %*d %*u %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",
                                           &pid, cmd, &utime, &stime);
                                    if (sid == pid)
                                    {
                                        continue;
                                    }
                                    printf("%6d %s\t", pid, ctty + 5);
                                    utime = (int)(double)(utime + stime) / sysconf(_SC_CLK_TCK);
                                    printf("%02llu:%02llu:%02llu", (utime / 3600) % 3600, (utime / 60) % 60, utime % 60);
                                    printf(" %s\n", cmd);
                                }
                                else
                                {
                                    if (pid == 0)
                                    {
                                        continue;
                                    }
                                    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
                                    fp = fopen(path, "r");
                                    if (!fp)
                                    {
                                        continue;
                                    }
                                    fgets(line, sizeof(line), fp);
                                    fclose(fp);
                                    int sid = getsid(pid);
                                    sscanf(line, "%d %s %*c %*d %*d %*d %*d %*d %*d %*u %*d %*d %*d %*d %lld %lld %*d %*d %*d %*d %*d %*d %*d %*d %*u %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",
                                           &pid, cmd, &utime, &stime);
                                    if (sid == pid)
                                    {
                                        continue;
                                    }
                                    printf("%6d %s\t", pid, "?");
                                    utime = (int)(double)(utime + stime) / sysconf(_SC_CLK_TCK);
                                    printf("%02llu:%02llu:%02llu", (utime / 3600) % 3600, (utime / 60) % 60, utime % 60);
                                    printf(" %s\n", cmd);
                                }
                            }
                        }
                    }
                    if (!strcmp(space[1], "-r"))
                    {
                        struct dirent *entry;
                        DIR *dir;
                        FILE *fp;
                        dir = opendir("/proc");
                        int pid, ppid, pgrp, session, tty_nr, tpgid;
                        long long int utime;
                        long long int stime;
                        char path[1024], bath[1024], math[1024], line[2048], cmd[1024], state;
                        char ctty[100];
                        sprintf(math, "/proc/self/fd/0");
                        int f1 = open(math, O_RDONLY);
                        sprintf(ctty, "%s", ttyname(f1));
                        close(f1);
                        char p[256];
                        printf("%6s %s\t%s %11s %s\n", "PID", "TTY", "STAT", "TIME", "CMD");
                        if (!dir)
                        {
                            perror("opendir");
                        }
                        else
                        {
                            while ((entry = readdir(dir)) != NULL)
                            {
                                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                                {
                                    continue;
                                }
                                if (entry->d_type != DT_DIR)
                                {
                                    continue;
                                }
                                if (!isdigit(entry->d_name[0]))
                                {
                                    continue;
                                }
                                pid = atoi(entry->d_name);
                                snprintf(bath, sizeof(path), "/proc/%d/fd/0", pid);
                                int p = open(bath, O_RDONLY);
                                char atty[100];
                                sprintf(atty, "%s", ttyname(p));
                                if (!strcmp(atty, ctty))
                                {
                                    if (pid == 0)
                                    {
                                        continue;
                                    }
                                    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
                                    fp = fopen(path, "r");
                                    if (!fp)
                                    {
                                        continue;
                                    }
                                    fgets(line, sizeof(line), fp);
                                    fclose(fp);
                                    sscanf(line, "%d %s %c %*d %*d %*d %*d %*d %*d %*u %*d %*d %*d %*d %lld %lld %*d %*d %*d %*d %*d %*d %*d %*d %*u %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",
                                           &pid, cmd, &state, &utime, &stime);
                                    if (state == 'R')
                                    {
                                        printf("%6d %s\t%c\t", pid, ctty + 5, state);
                                        time_t time = (stime + utime) / sysconf(_SC_CLK_TCK);
                                        time_t hour, minute, second;
                                        second = time % 60;
                                        minute = (time / 60) % 60;
                                        hour = (time / 3600) % 3600;
                                        printf("%02ld:%02ld:%02ld %s\n", hour, minute, hour, cmd);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (strcmp(space[0], "exit") == 0)
            {
                printf("Exiting my shell\n");
                break;
            }
            else
            {
                printf("Invalid input\n");
            }
        }
        free(input);
        closedir(dir);
    }
}