/*
	Author: Wenjie Wang, Erfei Yang, Jiaming Chu
	Class: CptS 122, Fall 2022
	Date: Wednesday, December 7, 2022
	Task: Programming Assignment 9

	Description: A Graphical Game or Application
*/
#include "pa9.h"

// return true if two sf::Vector2f points are within dis
// used to detect if monster is within attack range
bool inRange(sf::Vector2f v1, sf::Vector2f v2, float dis) {
	bool checkLeft = v1.x >= v2.x - dis && v1.x <= v2.x;
	bool checkRight = v1.x <= v2.x + dis && v1.x >= v2.x;
	bool checkHeight = v1.y - v2.y < 20;

	return (checkLeft && checkHeight) || (checkRight && checkHeight);
}
