#ifndef ISOCONVERT_H
#define ISOCONVERT_H
#include <Point.h>

class IsoConvert
{
    public:
        IsoConvert();
        virtual ~IsoConvert();
        static Point isoToTwoD(double x, double y);
        static Point twoDToIso(double x, double y);
    protected:

    private:
};

#endif // ISOCONVERT_H
