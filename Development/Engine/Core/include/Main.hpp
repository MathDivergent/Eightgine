#ifndef EIGHTGINECORE_MAIN_HPP
#define EIGHTGINECORE_MAIN_HPP

EIGHTGINECORE_API int EightgineMain(int iArgumentCount, char** pArgumentValues);

int main(int argc, char** argv)
{
    return ::EightgineMain(argc, argv);
}

#endif // EIGHTGINECORE_MAIN_HPP
