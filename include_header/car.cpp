// cl ./main.cpp /I car.h car.cpp
#include "car.h"
#include <iostream>

Car::Car() { (this->color) = "red"; }
Car::~Car() {}

void Car::go() { std::cout << this->color << " car are going." << std::endl; }