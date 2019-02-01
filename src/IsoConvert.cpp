#include "IsoConvert.h"

IsoConvert::IsoConvert()
{
    //ctor
}

IsoConvert::~IsoConvert()
{
    //dtor
}

Point IsoConvert::isoToTwoD(double x, double y)
{
  Point newPoint = Point(0, 0);
  newPoint.x = (2 * y + x) / 2;
  newPoint.y = (2 * y - x) / 2;
  return(newPoint);
}

Point IsoConvert::twoDToIso(double x, double y)
{
  Point newPoint = Point(0, 0);
  newPoint.x = x - y;
  newPoint.y = (x + y) / 2;
  return(newPoint);
}
