#include <CMain.hpp>

int main(int iArgumentCount, char** pArgumentValues)
{
    return CMain::Global()->Execute(iArgumentCount, pArgumentValues);
}
