#ifndef EIGHTGINE_CORE_MAIN_H
#define EIGHTGINE_CORE_MAIN_H

namespace Eightgine
{

int fMain(int iArgumentCount, char** pArgumentValues);

} // namespace Eightgine

int main(int argc, char** argv)
{
    return Eightgine::fMain(argc, argv);
}

#endif // EIGHTGINE_CORE_MAIN_H