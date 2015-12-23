#include "engine-library-math-vector-swizzle-operators.h"

namespace Base {
namespace Scripting {

void initVectorLibrary_swizzle_operators_dvec_xyzw(AngelScript::asIScriptEngine* as_engine)
{
  int r;
  ALL_SWIZZLE_FOR_VEC_XYZW(dvec);
}


} // namespace Scripting
} // namespace Base
