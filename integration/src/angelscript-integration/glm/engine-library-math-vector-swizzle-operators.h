#include "include-glm.h"
#include <angelscript.h>

namespace AngelScriptIntegration {

#define INDEX_0001(setterIndices) (setterIndices&0x3)
#define INDEX_0010(setterIndices) ((setterIndices>>4)&0x3)
#define INDEX_0100(setterIndices) ((setterIndices>>8)&0x3)
#define INDEX_1000(setterIndices) ((setterIndices>>12)&0x3)

#define SET_0001(setterIndices, other) (*o)[INDEX_0001(setterIndices)] = s.other;
#define SET_0010(setterIndices, other) (*o)[INDEX_0010(setterIndices)] = s.other;
#define SET_0100(setterIndices, other) (*o)[INDEX_0100(setterIndices)] = s.other;
#define SET_1000(setterIndices, other) (*o)[INDEX_1000(setterIndices)] = s.other;

template<int setterIndices, class objectType, class swizzleType>
swizzleType swizzle_setter1(objectType* o, const swizzleType& s)
{
  SET_0001(setterIndices, x);
  return s;
}

template<int setterIndices, class objectType, class swizzleType>
swizzleType swizzle_setter2(objectType* o, const swizzleType& s)
{ \
  SET_0010(setterIndices, x);
  SET_0001(setterIndices, y);
  return s;
}

template<int setterIndices, class objectType, class swizzleType>
swizzleType swizzle_setter3(objectType* o, const swizzleType& s)
{
  SET_0100(setterIndices, x);
  SET_0010(setterIndices, y);
  SET_0001(setterIndices, z);
  return s;
}

template<int setterIndices, class objectType, class swizzleType>
swizzleType swizzle_setter4(objectType* o, const swizzleType& s)
{
  SET_1000(setterIndices, x);
  SET_0100(setterIndices, y);
  SET_0010(setterIndices, z);
  SET_0001(setterIndices, w);
  return s;
}


#define SINGLE_PERMUTATION(objectType, swizzleType, swizzleLength, xyz, setterIndices) \
  r = as_engine->RegisterObjectMethod(#objectType, #swizzleType#swizzleLength" get_"#xyz"() const", AngelScript::asMETHOD(objectType, xyz), AngelScript::asCALL_THISCALL);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#objectType, #swizzleType#swizzleLength" set_"#xyz"("#swizzleType#swizzleLength" &in)", AngelScript::asFUNCTIONPR(swizzle_setter##swizzleLength<setterIndices>, (objectType*, const swizzleType##swizzleLength&), swizzleType##swizzleLength), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r);

#define PERMUTE_XY_1(objectType, swizzleType, swizzleLength, leading, x, y, setterIndices) \
  SINGLE_PERMUTATION(objectType, swizzleType, swizzleLength, leading##x, (setterIndices|0x0)) \
  SINGLE_PERMUTATION(objectType, swizzleType, swizzleLength, leading##y, (setterIndices|0x1))

#define PERMUTE_XY_2(objectType, swizzleType, swizzleLength, leading, x, y, setterIndices) \
  PERMUTE_XY_1(objectType, swizzleType, swizzleLength, leading##x, x, y, (setterIndices|0x00)) \
  PERMUTE_XY_1(objectType, swizzleType, swizzleLength, leading##y, x, y, (setterIndices|0x10))

#define PERMUTE_XY_3(objectType, swizzleType, swizzleLength, leading, x, y, setterIndices) \
  PERMUTE_XY_2(objectType, swizzleType, swizzleLength, leading##x, x, y, (setterIndices|0x000)) \
  PERMUTE_XY_2(objectType, swizzleType, swizzleLength, leading##y, x, y, (setterIndices|0x100))

#define PERMUTE_XY_4(objectType, swizzleType, swizzleLength, leading, x, y, setterIndices) \
  PERMUTE_XY_3(objectType, swizzleType, swizzleLength, leading##x, x, y, (setterIndices|0x0000)) \
  PERMUTE_XY_3(objectType, swizzleType, swizzleLength, leading##y, x, y, (setterIndices|0x1000))

#define PERMUTE_XYZ_1(objectType, swizzleType, swizzleLength, leading, x, y, z, setterIndices) \
  SINGLE_PERMUTATION(objectType, swizzleType, swizzleLength, leading##x, (setterIndices|0x0)) \
  SINGLE_PERMUTATION(objectType, swizzleType, swizzleLength, leading##y, (setterIndices|0x1)) \
  SINGLE_PERMUTATION(objectType, swizzleType, swizzleLength, leading##z, (setterIndices|0x2))

#define PERMUTE_XYZ_2(objectType, swizzleType, swizzleLength, leading, x, y, z, setterIndices) \
  PERMUTE_XYZ_1(objectType, swizzleType, swizzleLength, leading##x, x, y, z, (setterIndices|0x00)) \
  PERMUTE_XYZ_1(objectType, swizzleType, swizzleLength, leading##y, x, y, z, (setterIndices|0x10)) \
  PERMUTE_XYZ_1(objectType, swizzleType, swizzleLength, leading##z, x, y, z, (setterIndices|0x20))

#define PERMUTE_XYZ_3(objectType, swizzleType, swizzleLength, leading, x, y, z, setterIndices) \
  PERMUTE_XYZ_2(objectType, swizzleType, swizzleLength, leading##x, x, y, z, (setterIndices|0x000)) \
  PERMUTE_XYZ_2(objectType, swizzleType, swizzleLength, leading##y, x, y, z, (setterIndices|0x100)) \
  PERMUTE_XYZ_2(objectType, swizzleType, swizzleLength, leading##z, x, y, z, (setterIndices|0x200))

#define PERMUTE_XYZ_4(objectType, swizzleType, swizzleLength, leading, x, y, z, setterIndices) \
  PERMUTE_XYZ_3(objectType, swizzleType, swizzleLength, leading##x, x, y, z, (setterIndices|0x0000)) \
  PERMUTE_XYZ_3(objectType, swizzleType, swizzleLength, leading##y, x, y, z, (setterIndices|0x1000)) \
  PERMUTE_XYZ_3(objectType, swizzleType, swizzleLength, leading##z, x, y, z, (setterIndices|0x2000))

#define PERMUTE_XYZW_1(objectType, swizzleType, swizzleLength, leading, x, y, z, w, setterIndices) \
  SINGLE_PERMUTATION(objectType, swizzleType, swizzleLength, leading##x, (setterIndices|0x0)) \
  SINGLE_PERMUTATION(objectType, swizzleType, swizzleLength, leading##y, (setterIndices|0x1)) \
  SINGLE_PERMUTATION(objectType, swizzleType, swizzleLength, leading##z, (setterIndices|0x2)) \
  SINGLE_PERMUTATION(objectType, swizzleType, swizzleLength, leading##w, (setterIndices|0x3))

#define PERMUTE_XYZW_2(objectType, swizzleType, swizzleLength, leading, x, y, z, w, setterIndices) \
  PERMUTE_XYZW_1(objectType, swizzleType, swizzleLength, leading##x, x, y, z, w, (setterIndices|0x00)) \
  PERMUTE_XYZW_1(objectType, swizzleType, swizzleLength, leading##y, x, y, z, w, (setterIndices|0x10)) \
  PERMUTE_XYZW_1(objectType, swizzleType, swizzleLength, leading##z, x, y, z, w, (setterIndices|0x20)) \
  PERMUTE_XYZW_1(objectType, swizzleType, swizzleLength, leading##w, x, y, z, w, (setterIndices|0x30))

#define PERMUTE_XYZW_3(objectType, swizzleType, swizzleLength, leading, x, y, z, w, setterIndices) \
  PERMUTE_XYZW_2(objectType, swizzleType, swizzleLength, leading##x, x, y, z, w, (setterIndices|0x000)) \
  PERMUTE_XYZW_2(objectType, swizzleType, swizzleLength, leading##y, x, y, z, w, (setterIndices|0x100)) \
  PERMUTE_XYZW_2(objectType, swizzleType, swizzleLength, leading##z, x, y, z, w, (setterIndices|0x200)) \
  PERMUTE_XYZW_2(objectType, swizzleType, swizzleLength, leading##w, x, y, z, w, (setterIndices|0x300))

#define PERMUTE_XYZW_4(objectType, swizzleType, swizzleLength, leading, x, y, z, w, setterIndices) \
  PERMUTE_XYZW_3(objectType, swizzleType, swizzleLength, leading##x, x, y, z, w, (setterIndices|0x0000)) \
  PERMUTE_XYZW_3(objectType, swizzleType, swizzleLength, leading##y, x, y, z, w, (setterIndices|0x1000)) \
  PERMUTE_XYZW_3(objectType, swizzleType, swizzleLength, leading##z, x, y, z, w, (setterIndices|0x2000)) \
  PERMUTE_XYZW_3(objectType, swizzleType, swizzleLength, leading##w, x, y, z, w, (setterIndices|0x3000))

#define ALL_XY_SWIZZLE_FOR_VEC2(vec, x, y) \
  PERMUTE_XY_4(vec##2, vec, 4, , x, y, 0) \
  PERMUTE_XY_3(vec##2, vec, 3, , x, y, 0) \
  PERMUTE_XY_2(vec##2, vec, 2, , x, y, 0)

#define ALL_SWIZZLE_FOR_VEC2_XY(vec) \
  ALL_XY_SWIZZLE_FOR_VEC2(vec, x, y)

#define ALL_SWIZZLE_FOR_VEC2_RG(vec) \
  ALL_XY_SWIZZLE_FOR_VEC2(vec, r, g)

#define ALL_SWIZZLE_FOR_VEC2_ST(vec) \
  ALL_XY_SWIZZLE_FOR_VEC2(vec, s, t)

#define ALL_XYZ_SWIZZLE_FOR_VEC3(vec, x, y, z) \
  PERMUTE_XYZ_4(vec##3, vec, 4, , x, y, z, 0) \
  PERMUTE_XYZ_3(vec##3, vec, 3, , x, y, z, 0) \
  PERMUTE_XYZ_2(vec##3, vec, 2, , x, y, z, 0)

#define ALL_SWIZZLE_FOR_VEC3_XYZ(vec) \
  ALL_XYZ_SWIZZLE_FOR_VEC3(vec, x, y, z)

#define ALL_SWIZZLE_FOR_VEC3_RGB(vec) \
  ALL_XYZ_SWIZZLE_FOR_VEC3(vec, r, g, b)

#define ALL_SWIZZLE_FOR_VEC3_STP(vec) \
  ALL_XYZ_SWIZZLE_FOR_VEC3(vec, s, t, p)

#define ALL_XYZW_SWIZZLE_FOR_VEC4(vec, x, y, z, w) \
  PERMUTE_XYZW_4(vec##4, vec, 4, , x, y, z, w, 0) \
  PERMUTE_XYZW_3(vec##4, vec, 3, , x, y, z, w, 0) \
  PERMUTE_XYZW_2(vec##4, vec, 2, , x, y, z, w, 0)

#define ALL_SWIZZLE_FOR_VEC4_XYZW(vec) \
  ALL_XYZW_SWIZZLE_FOR_VEC4(vec, x, y, z, w)

#define ALL_SWIZZLE_FOR_VEC4_RGBA(vec) \
  ALL_XYZW_SWIZZLE_FOR_VEC4(vec, r, g, b, a)

#define ALL_SWIZZLE_FOR_VEC4_STPQ(vec) \
  ALL_XYZW_SWIZZLE_FOR_VEC4(vec, s, t, p, q)

#define ALL_SWIZZLE_FOR_VEC_XYZW(vec) \
  ALL_SWIZZLE_FOR_VEC2_XY(vec) \
  ALL_SWIZZLE_FOR_VEC3_XYZ(vec) \
  ALL_SWIZZLE_FOR_VEC4_XYZW(vec)

#define ALL_SWIZZLE_FOR_VEC_RGBA(vec) \
  ALL_SWIZZLE_FOR_VEC2_RG(vec) \
  ALL_SWIZZLE_FOR_VEC3_RGB(vec) \
  ALL_SWIZZLE_FOR_VEC4_RGBA(vec)

#define ALL_SWIZZLE_FOR_VEC_STPQ(vec) \
  ALL_SWIZZLE_FOR_VEC2_ST(vec) \
  ALL_SWIZZLE_FOR_VEC3_STP(vec) \
  ALL_SWIZZLE_FOR_VEC4_STPQ(vec)

void AngelScriptCheck(int returnCode);


} // namespace Angelscriptintegration

