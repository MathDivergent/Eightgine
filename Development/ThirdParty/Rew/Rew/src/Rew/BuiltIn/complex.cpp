#include <Rew/BuiltIn/complex.hpp>

template struct ::xxrew<std::complex<float>>;

#ifdef REW_FULLY_ENABLE
template struct ::xxrew<std::complex<double>>;
template struct ::xxrew<std::complex<long double>>;
#endif // REW_FULLY_ENABLE
