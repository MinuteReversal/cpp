#include "car.h"
#include <iostream>

Car::Car() { color = (char *)"white"; }
Car::~Car() {}

void Car::drive() { std::cout << color << " car are driving." << std::endl; }