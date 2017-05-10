#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
    string str = "g++ -std=c++11 testing.cpp -o testing.exe";
    int i = system(str.c_str());
    str = "./testing.exe";
    int returned_sign = 0;
    time_t start = time(0);
    pid_t pid = fork();
    if (pid == 0) {
        int own_pid = getpid();
        system("echo " + to_string(own_pid) + " > /sys/fs/cgroup/memory/group0/tasks");
        system("echo " + to_string(own_pid) + " > /sys/fs/cgroup/cpu/group0/tasks");
        returned_sign = execl(str.c_str(), NULL);
        exit(returned_sign);
    } else {
        wait();
        double seconds_since_start = difftime(time(0), start);
        if (seconds_since_start - 2.0 > 0.00001) {
            cout << "TL ";
            exit(2);
        }
        str = "./checker.exe input.txt output.txt ans.txt";
        i = system(str.c_str());
        return i;
    }
}