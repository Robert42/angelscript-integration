#include "engine-library-math-vector-swizzle-operators.h"

namespace Base {
namespace Scripting {

void initVectorLibrary_swizzle_operators_bvec_rgba(AngelScript::asIScriptEngine* as_engine)
{
  int r;
  ALL_SWIZZLE_FOR_VEC_RGBA(bvec);
}


} // namespace Scripting
} // namespace Base
