#include <ctime>
#include <iostream>

#include "timetest.h"

long t_time;    //Время выполнения

void startTest() {
	t_time = clock();
}

double stopTest() {
	t_time = clock() - t_time;
	return (double)((double)t_time / CLOCKS_PER_SEC);
}