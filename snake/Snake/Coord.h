#pragma once
#ifndef Coord_h
#define Coord_h
class Coord
{
public:
	int hor;
	int ver;
	Coord()
	{
		hor = 0;
		ver = 0;
	}
	Coord(int hor, int ver)
	{
		this->hor = hor;
		this->ver = ver;
	}
};


#endif // !Coord_h

