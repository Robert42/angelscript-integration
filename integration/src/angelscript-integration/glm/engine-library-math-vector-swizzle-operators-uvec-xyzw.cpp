#include "engine-library-math-vector-swizzle-operators.h"

namespace AngelScriptIntegration {

void initVectorLibrary_swizzle_operators_uvec_xyzw(AngelScript::asIScriptEngine* as_engine)
{
  int r;
  ALL_SWIZZLE_FOR_VEC_XYZW(uvec);
}


} // namespace Angelscriptintegration

