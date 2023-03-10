/*
** EPITECH PROJECT, 2022
** Epitech
** File description:
** test
*/

#include <chrono>
#include <iostream>
#include <unistd.h>

long fibonacci(unsigned n)
{
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{
    int c = 0;
    int z = 0;
    std::chrono::time_point<std::chrono::system_clock> start, end;
  
    start = std::chrono::system_clock::now();
    std::cout << "f(42) = " << fibonacci(42) << '\n';
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = (end - start) * 1000000;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
    usleep(elapsed_seconds.count());
}