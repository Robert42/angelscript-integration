#include "engine-library-math-vector-swizzle-operators.h"

namespace Base {
namespace Scripting {

void initVectorLibrary_swizzle_operators_ivec_rgba(AngelScript::asIScriptEngine* as_engine)
{
  int r;
  ALL_SWIZZLE_FOR_VEC_RGBA(ivec);
}


} // namespace Scripting
} // namespace Base
