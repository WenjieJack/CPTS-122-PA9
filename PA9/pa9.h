/*
	Author: Wenjie Wang, Erfei Yang, Jiaming Chu
	Class: CptS 122, Fall 2022
	Date: Wednesday, December 7, 2022
	Task: Programming Assignment 9

	Description: A Graphical Game or Application
*/
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>
#include <cstdlib>

using std::cout;
using std::endl;
using std::cin;
using std::string;

// animation macros
#define UNKNOWN_ANIM -1
#define IDLE_ANIM 0
#define WALK_ANIM 1
#define ATK_ANIM 2
#define HURT_ANIM 3

const unsigned short ServerPort = 5000;

// math helper function, clamp a number between lower bound and upper bound
template <class T>
T clamp(const T& n, const T& lower, const T& upper);

// math helper function, clamp a number between lower bound and upper bound
template <class T>
T clamp(const T& n, const T& lower, const T& upper) {
	return std::max(lower, std::min(n, upper));
}

// return true if two sf::Vector2f points are within dis
// used to detect if monster is within attack range
bool inRange(sf::Vector2f v1, sf::Vector2f v2, float dis);