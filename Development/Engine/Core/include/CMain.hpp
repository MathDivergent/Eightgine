#ifndef EIGHTGINECORE_CMAIN_HPP
#define EIGHTGINECORE_CMAIN_HPP

struct EIGHTGINECORE_API CMain
{
    static CMain* Global();

    int Execute(int iArgumentCount, char** pArgumentValues);
};

#endif // EIGHTGINECORE_CMAIN_HPP
