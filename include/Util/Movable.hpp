#pragma once

class Movable {
public:

	Movable(Movable&&) {};
	Movable& operator=(Movable&&) { return *this; }

};