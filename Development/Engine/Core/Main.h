#ifndef EIGHTGINECORE_MAIN_H
#define EIGHTGINECORE_MAIN_H

namespace eightgine
{

EIGHTGINECORE_API int fMain(int iArgumentCount, char** pArgumentValues);

} // namespace eightgine

int main(int argc, char** argv)
{
    return eightgine::fMain(argc, argv);
}

#endif // EIGHTGINECORE_MAIN_H
