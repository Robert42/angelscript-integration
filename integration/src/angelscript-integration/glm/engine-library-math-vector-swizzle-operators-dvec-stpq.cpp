#include "engine-library-math-vector-swizzle-operators.h"

namespace Base {
namespace Scripting {

void initVectorLibrary_swizzle_operators_dvec_stpq(AngelScript::asIScriptEngine* as_engine)
{
  int r;
  ALL_SWIZZLE_FOR_VEC_STPQ(dvec);
}


} // namespace Scripting
} // namespace Base
