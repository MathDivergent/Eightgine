#include <PPlatform.hpp>

PPlatform* PPlatform::Global()
{
    static PPlatform self; return &self;
}
