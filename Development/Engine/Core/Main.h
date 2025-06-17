#ifndef EIGHTGINECORE_MAIN_H
#define EIGHTGINECORE_MAIN_H

namespace Eightgine
{

int EIGHTGINECORE_API fMain(int iArgumentCount, char** pArgumentValues);

} // namespace Eightgine

int main(int argc, char** argv)
{
    return Eightgine::fMain(argc, argv);
}

#endif // EIGHTGINECORE_MAIN_H
