#include "car.h"
#include <iostream>



Car::Car() { this->color = (wchar_t *)L"red"; }
Car::~Car() { this->color = NULL; }

void Car::go() { std::cout << this->color << "car are going." << std::endl; }