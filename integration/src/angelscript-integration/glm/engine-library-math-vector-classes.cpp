#include <base/scripting/engine.h>
#include <base/io/log.h>

namespace AngelScriptIntegration {

template<typename T_target, typename T_source>
T_target cast_vector1(const T_source* source)
{
  return T_target(source->x);
}

template<typename T_target, typename T_source>
T_target cast_vector2(const T_source* source)
{
  return T_target(source->x, source->y);
}

template<typename T_target, typename T_source>
T_target cast_vector3(const T_source* source)
{
  return T_target(source->x, source->y, source->z);
}

template<typename T_target, typename T_source>
T_target cast_vector4(const T_source* source)
{
  return T_target(source->x, source->y, source->z, source->w);
}

#define REGISTER_CAST_(source_vec, target_vec, vecLength, cast) \
  r = as_engine->RegisterObjectBehaviour(#source_vec#vecLength, AngelScript::cast, #target_vec#vecLength" f()", AngelScript::asFUNCTIONPR(cast_vector##vecLength, (const source_vec##vecLength*), target_vec##vecLength), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
 
#define REGISTER_CAST(source_vec, target_vec, cast) \
  REGISTER_CAST_(source_vec, target_vec, 2, cast) \
  REGISTER_CAST_(source_vec, target_vec, 3, cast) \
  REGISTER_CAST_(source_vec, target_vec, 4, cast)

template<typename T_vec>
inline typename T_vec::value_type getVecElement(T_vec* v, int i)
{
  if(i>=0 && i<v->length())
  {
    return (*v)[i];
  }else
  {
    IO::Log::logWarning("?vec?::opIndex: Index %0 is outside the range [0, %1]", i, v->length());
    return (*v)[clamp<int>(i, 0, v->length()-1)];
  }
}

#define REGISTER_BASIC_OPERATORS_(vec, type) \
  r = as_engine->RegisterObjectMethod(#vec, "int length() const", AngelScript::asMETHOD(vec, length), AngelScript::asCALL_THISCALL);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #type" opIndex(int) const", AngelScript::asFUNCTION(getVecElement<vec>), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
 
#define REGISTER_BASIC_OPERATORS(prefix, type) \
  REGISTER_BASIC_OPERATORS_(prefix##vec##2, type) \
  REGISTER_BASIC_OPERATORS_(prefix##vec##3, type) \
  REGISTER_BASIC_OPERATORS_(prefix##vec##4, type)

template<typename R, typename A, typename B>
R opAdd(const A* a, B b)
{
  return *a+b;
}

template<typename R, typename A, typename B>
R opSub(const A* a, B b)
{
  return *a-b;
}

template<typename R, typename A, typename B>
R opSub_r(const A* a, B b)
{
  return b-*a;
}

template<typename R, typename A, typename B>
R opMul(const A* a, B b)
{
  return *a*b;
}

template<typename A, typename B>
A opAddAssign(A* a, B b)
{
  return (*a)+=b;
}

template<typename A, typename B>
A opSubAssign(A* a, B b)
{
  return (*a)-=b;
}

template<typename A, typename B>
A opMulAssign(A* a, B b)
{
  return (*a)*=b;
}

template<typename A>
A opNeg(const A* a_)
{
  const A& a = *a_;

  return -a;
}

template<typename A>
A opPreInc(A* a_)
{
  A& a = *a_;

  return ++a;
}

template<typename A>
A opPreDec(A* a_)
{
  A& a = *a_;

  return --a;
}

template<typename A>
A opPostInc(A* a_)
{
  A& a = *a_;

  return a++;
}

template<typename A>
A opPostDec(A* a_)
{
  A& a = *a_;

  return a--;
}

template<typename A, typename B>
bool opEquals(const A* a, B b)
{
  return *a == A(b);
}

#define REGISTER_NUMERIC_OPERATORS_(vec, type) \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opAdd("#vec")", AngelScript::asFUNCTION((opAdd<vec, vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opAdd("#type")", AngelScript::asFUNCTION((opAdd<vec, vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opAdd_r("#type")", AngelScript::asFUNCTION((opAdd<vec, vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opSub("#vec")", AngelScript::asFUNCTION((opSub<vec, vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opSub("#type")", AngelScript::asFUNCTION((opSub<vec, vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opSub_r("#type")", AngelScript::asFUNCTION((opSub_r<vec, vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opMul("#vec")", AngelScript::asFUNCTION((opMul<vec, vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opMul("#type")", AngelScript::asFUNCTION((opMul<vec, vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opMul_r("#type")", AngelScript::asFUNCTION((opMul<vec, vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opAddAssign("#vec")", AngelScript::asFUNCTION((opAddAssign<vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opAddAssign("#type")", AngelScript::asFUNCTION((opAddAssign<vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opSubAssign("#vec")", AngelScript::asFUNCTION((opSubAssign<vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opSubAssign("#type")", AngelScript::asFUNCTION((opSubAssign<vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opMulAssign("#vec")", AngelScript::asFUNCTION((opMulAssign<vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opMulAssign("#type")", AngelScript::asFUNCTION((opMulAssign<vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opNeg()", AngelScript::asFUNCTION((opNeg<vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opPreInc()", AngelScript::asFUNCTION((opPreInc<vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opPreDec()", AngelScript::asFUNCTION((opPreDec<vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opPostInc()", AngelScript::asFUNCTION((opPostInc<vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opPostDec()", AngelScript::asFUNCTION((opPostDec<vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, "bool opEquals("#vec")", AngelScript::asFUNCTION((opEquals<vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, "bool opEquals("#type")", AngelScript::asFUNCTION((opEquals<vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
 

#define REGISTER_NUMERIC_OPERATORS(prefix, type) \
  REGISTER_BASIC_OPERATORS(prefix, type) \
  REGISTER_NUMERIC_OPERATORS_(prefix##vec##2, type) \
  REGISTER_NUMERIC_OPERATORS_(prefix##vec##3, type) \
  REGISTER_NUMERIC_OPERATORS_(prefix##vec##4, type)


template<typename R, typename A, typename B>
R opDiv_real(const A* a, B b)
{
  return *a/b;
}

template<typename R, typename A, typename B>
R opDiv_r_real(const A* a, B b)
{
  return b/ *a;
}

template<typename A, typename B>
A opDivAssign_real(A* a, B b)
{
  return (*a)/=b;
}

#define REGISTER_REAL_OPERATORS_(vec, type) \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opDiv("#vec")", AngelScript::asFUNCTION((opDiv_real<vec, vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opDiv("#type")", AngelScript::asFUNCTION((opDiv_real<vec, vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opDiv_r("#type")", AngelScript::asFUNCTION((opDiv_r_real<vec, vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opDivAssign("#vec")", AngelScript::asFUNCTION((opDivAssign_real<vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opDivAssign("#type")", AngelScript::asFUNCTION((opDivAssign_real<vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
 

#define REGISTER_REAL_OPERATORS(prefix, type) \
  REGISTER_NUMERIC_OPERATORS(prefix, type) \
  REGISTER_REAL_OPERATORS_(prefix##vec##2, type) \
  REGISTER_REAL_OPERATORS_(prefix##vec##3, type) \
  REGISTER_REAL_OPERATORS_(prefix##vec##4, type)


template<typename R, typename A, typename B>
R opMod_vec_vec(const A* a, B b)
{
  for(int i=0; i<b.length(); ++i)
  {
    if(b[i] == 0)
    {
      IO::Log::logWarning("AngelScript: opMod_vec_vec: Divition by zero detected");
      b[i] = 1;
    }
  }

  return *a%b;
}

template<typename R, typename A, typename B>
R opMod_vec_type(const A* a, B b)
{
  if(b == 0)
  {
    IO::Log::logWarning("AngelScript: opMod_vec_type: Divition by zero detected");
    b = 1;
  }

  return *a%b;
}

template<typename R, typename A, typename B>
R opMod_r_vec_type(const A* a_, B b)
{
  A a = *a_;

  for(int i=0; i<a.length(); ++i)
  {
    if(a[i] == 0)
    {
      IO::Log::logWarning("AngelScript: opMod_r_vec_type: Divition by zero detected");
      a[i] = 1;
    }
  }

  return b%a;
}


template<typename R, typename A, typename B>
R opDiv_int_vec_vec(const A* a_, B b)
{
  const A& a = *a_;

  for(int i=0; i<b.length(); ++i)
  {
    if(b[i] == 0)
    {
      IO::Log::logWarning("AngelScript: opDiv_int_vec_vec: Divition by zero detected");
      b[i] = std::numeric_limits<typename A::value_type>::max();
    }
  }

  return a/b;
}

template<typename R, typename A, typename B>
R opDiv_int_vec_type(const A* a_, B b)
{
  const A& a = *a_;

  if(b == 0)
  {
    IO::Log::logWarning("AngelScript: opDiv_int_vec_type: Divition by zero detected");
    b = std::numeric_limits<typename A::value_type>::max();
  }

  return a/b;
}

template<typename R, typename A, typename B>
R opDiv_r_int_vec_type(const A* a_, B b)
{
  A a = *a_;

  for(int i=0; i<a.length(); ++i)
  {
    if(a[i] == 0)
    {
      IO::Log::logWarning("AngelScript: opDiv_r_int_vec_type: Divition by zero detected");
      a[i] = std::numeric_limits<typename A::value_type>::max();
    }
  }

  return b/a;
}


template<typename R, typename A, typename B>
R opDivAssign_int_vec_vec(A* a_, B b)
{
  A& a = *a_;

  for(int i=0; i<b.length(); ++i)
  {
    if(b[i] == 0)
    {
      IO::Log::logWarning("AngelScript: opDivAssign_int_vec_vec: Divition by zero detected");
      b[i] = std::numeric_limits<typename A::value_type>::max();
    }
  }

  return a/=b;
}

template<typename R, typename A, typename B>
R opDivAssign_int_vec_type(A* a_, B b)
{
  A& a = *a_;

  if(b == 0)
  {
    IO::Log::logWarning("AngelScript: opDivAssign_int_vec_type: Divition by zero detected");
    b = std::numeric_limits<typename A::value_type>::max();
  }

  return a/=b;
}


template<typename R, typename A, typename B>
R opModAssign_vec_vec(A* a_, B b)
{
  A& a = *a_;

  for(int i=0; i<b.length(); ++i)
  {
    if(b[i] == 0)
    {
      IO::Log::logWarning("AngelScript: opMod_vec_vec: Divition by zero detected");
      b[i] = 1;
    }
  }

  return a%=b;
}

template<typename R, typename A, typename B>
R opModAssign_vec_type(A* a_, B b)
{
  A& a = *a_;

  if(b == 0)
  {
    IO::Log::logWarning("AngelScript: opMod_vec_type: Divition by zero detected");
    b = 1;
  }

  return a%=b;
}

template<typename A>
A opCom(const A* a_)
{
  const A& a = *a_;

  return ~a;
}

template<typename A, typename B>
A opShlAssign_scalar(A* a_, B b)
{
  A& a = *a_;

  for(int i=0; i<a.length(); ++i)
    a[i] <<= b;
  return a;
}

template<typename A, typename B>
A opShrAssign_scalar(A* a_, B b)
{
  A& a = *a_;

  for(int i=0; i<a.length(); ++i)
    a[i] >>= b;
  return a;
}

template<typename A, typename B>
A opShlAssign_vec(A* a_, B b)
{
  A& a = *a_;

  for(int i=0; i<a.length(); ++i)
    a[i] <<= b[i];
  return a;
}

template<typename A, typename B>
A opShrAssign_vec(A* a_, B b)
{
  A& a = *a_;

  for(int i=0; i<a.length(); ++i)
    a[i] >>= b[i];
  return a;
}

template<typename A, typename B>
A opShl_scalar(const A* a_, B b)
{
  A a = *a_;

  opShlAssign_scalar(&a, b);
  return a;
}

template<typename A, typename B>
A opShr_scalar(const A* a_, B b)
{
  A a = *a_;

  opShrAssign_scalar(&a, b);
  return a;
}

template<typename A, typename B>
A opShl_vec(const A* a_, B b)
{
  A a = *a_;

  opShlAssign_vec(&a, b);
  return a;
}

template<typename A, typename B>
A opShr_vec(const A* a_, B b)
{
  A a = *a_;

  opShrAssign_vec(&a, b);
  return a;
}

template<typename A, typename B>
A opAndAssign_scalar(A* a_, B b)
{
  A& a = *a_;

  for(int i=0; i<a.length(); ++i)
    a[i] &= b;
  return a;
}

template<typename A, typename B>
A opAndAssign_vec(A* a_, B b)
{
  A& a = *a_;

  for(int i=0; i<a.length(); ++i)
    a[i] &= b[i];
  return a;
}

template<typename A, typename B>
A opAnd_scalar(const A* a_, B b)
{
  A a = *a_;

  opAndAssign_scalar(&a, b);
  return a;
}

template<typename A, typename B>
A opAnd_vec(const A* a_, B b)
{
  A a = *a_;

  opAndAssign_vec(&a, b);
  return a;
}

template<typename A, typename B>
A opOrAssign_scalar(A* a_, B b)
{
  A& a = *a_;

  for(int i=0; i<a.length(); ++i)
    a[i] |= b;
  return a;
}

template<typename A, typename B>
A opOrAssign_vec(A* a_, B b)
{
  A& a = *a_;

  for(int i=0; i<a.length(); ++i)
    a[i] |= b[i];
  return a;
}

template<typename A, typename B>
A opOr_scalar(const A* a_, B b)
{
  A a = *a_;

  opOrAssign_scalar(&a, b);
  return a;
}

template<typename A, typename B>
A opOr_vec(const A* a_, B b)
{
  A a = *a_;

  opOrAssign_vec(&a, b);
  return a;
}

template<typename A, typename B>
A opXorAssign_scalar(A* a_, B b)
{
  A& a = *a_;

  for(int i=0; i<a.length(); ++i)
    a[i] ^= b;
  return a;
}

template<typename A, typename B>
A opXorAssign_vec(A* a_, B b)
{
  A& a = *a_;

  for(int i=0; i<a.length(); ++i)
    a[i] ^= b[i];
  return a;
}

template<typename A, typename B>
A opXor_scalar(const A* a_, B b)
{
  A a = *a_;

  opXorAssign_scalar(&a, b);
  return a;
}

template<typename A, typename B>
A opXor_vec(const A* a_, B b)
{
  A a = *a_;

  opXorAssign_vec(&a, b);
  return a;
}

#define REGISTER_INTEGER_OPERATORS_(vec, type) \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opMod("#vec")", AngelScript::asFUNCTION((opMod_vec_vec<vec, vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opMod("#type")", AngelScript::asFUNCTION((opMod_vec_type<vec, vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opMod_r("#type")", AngelScript::asFUNCTION((opMod_r_vec_type<vec, vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opDiv("#vec")", AngelScript::asFUNCTION((opDiv_int_vec_vec<vec, vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opDiv("#type")", AngelScript::asFUNCTION((opDiv_int_vec_type<vec, vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opDiv_r("#type")", AngelScript::asFUNCTION((opDiv_r_int_vec_type<vec, vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opDivAssign("#vec")", AngelScript::asFUNCTION((opDivAssign_int_vec_vec<vec, vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opDivAssign("#type")", AngelScript::asFUNCTION((opDivAssign_int_vec_type<vec, vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opModAssign("#vec")", AngelScript::asFUNCTION((opModAssign_vec_vec<vec, vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opModAssign("#type")", AngelScript::asFUNCTION((opModAssign_vec_type<vec, vec, type>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opCom()", AngelScript::asFUNCTION((opCom<vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opShl(int)", AngelScript::asFUNCTION((opShl_scalar<vec, int>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opShr(int)", AngelScript::asFUNCTION((opShr_scalar<vec, int>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opShl(uint)", AngelScript::asFUNCTION((opShl_scalar<vec, uint>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opShr(uint)", AngelScript::asFUNCTION((opShr_scalar<vec, uint>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opShl("#vec")", AngelScript::asFUNCTION((opShl_vec<vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opShr("#vec")", AngelScript::asFUNCTION((opShr_vec<vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opShlAssign(int)", AngelScript::asFUNCTION((opShlAssign_scalar<vec, int>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opShrAssign(int)", AngelScript::asFUNCTION((opShrAssign_scalar<vec, int>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opShlAssign(uint)", AngelScript::asFUNCTION((opShlAssign_scalar<vec, uint>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opShrAssign(uint)", AngelScript::asFUNCTION((opShrAssign_scalar<vec, uint>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opShlAssign("#vec")", AngelScript::asFUNCTION((opShlAssign_vec<vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opShrAssign("#vec")", AngelScript::asFUNCTION((opShrAssign_vec<vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opAnd(int)", AngelScript::asFUNCTION((opAnd_scalar<vec, int>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opAnd(uint)", AngelScript::asFUNCTION((opAnd_scalar<vec, uint>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opAnd_r(int)", AngelScript::asFUNCTION((opAnd_scalar<vec, int>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opAnd_r(uint)", AngelScript::asFUNCTION((opAnd_scalar<vec, uint>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opAnd("#vec")", AngelScript::asFUNCTION((opAnd_vec<vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opAndAssign(int)", AngelScript::asFUNCTION((opAndAssign_scalar<vec, int>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opAndAssign(uint)", AngelScript::asFUNCTION((opAndAssign_scalar<vec, uint>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opAndAssign("#vec")", AngelScript::asFUNCTION((opAndAssign_vec<vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opOr(int)", AngelScript::asFUNCTION((opOr_scalar<vec, int>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opOr(uint)", AngelScript::asFUNCTION((opOr_scalar<vec, uint>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opOr_r(int)", AngelScript::asFUNCTION((opAnd_scalar<vec, int>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opOr_r(uint)", AngelScript::asFUNCTION((opAnd_scalar<vec, uint>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opOr("#vec")", AngelScript::asFUNCTION((opOr_vec<vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opOrAssign(int)", AngelScript::asFUNCTION((opOrAssign_scalar<vec, int>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opOrAssign(uint)", AngelScript::asFUNCTION((opOrAssign_scalar<vec, uint>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opOrAssign("#vec")", AngelScript::asFUNCTION((opOrAssign_vec<vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opXor(int)", AngelScript::asFUNCTION((opXor_scalar<vec, int>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opXor(uint)", AngelScript::asFUNCTION((opXor_scalar<vec, uint>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opXor_r(int)", AngelScript::asFUNCTION((opAnd_scalar<vec, int>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opXor_r(uint)", AngelScript::asFUNCTION((opAnd_scalar<vec, uint>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opXor("#vec")", AngelScript::asFUNCTION((opXor_vec<vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opXorAssign(int)", AngelScript::asFUNCTION((opXorAssign_scalar<vec, int>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opXorAssign(uint)", AngelScript::asFUNCTION((opXorAssign_scalar<vec, uint>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectMethod(#vec, #vec" opXorAssign("#vec")", AngelScript::asFUNCTION((opXorAssign_vec<vec, vec>)), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
 

#define REGISTER_INTEGER_OPERATORS(prefix, type) \
  REGISTER_NUMERIC_OPERATORS(prefix, type) \
  REGISTER_INTEGER_OPERATORS_(prefix##vec##2, type) \
  REGISTER_INTEGER_OPERATORS_(prefix##vec##3, type) \
  REGISTER_INTEGER_OPERATORS_(prefix##vec##4, type)

#define REGISTER_VEC2_(vec, type) \
  class HELPERCLASS_REGISTER_VEC2_##vec \
  { \
  public: \
    static void construct_type_type(vec##2 *v, type x, type y) \
    { \
      v->x = x; \
      v->y = y; \
    } \
    \
    static void construct_type(vec##2 *v, type x) \
    { \
      v->x = x; \
      v->y = x; \
    } \
    static void construct_vec2(vec##2 *v, const vec##2 &other) \
    { \
      *v = other; \
    } \
  }; \
  r = as_engine->RegisterObjectBehaviour(#vec"2", AngelScript::asBEHAVE_CONSTRUCT, "void f("#type" x, "#type" y)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC2_##vec::construct_type_type), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectBehaviour(#vec"2", AngelScript::asBEHAVE_CONSTRUCT, "void f("#type" x)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC2_##vec::construct_type), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectBehaviour(#vec"2", AngelScript::asBEHAVE_CONSTRUCT, "void f("#vec"2 &in v)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC2_##vec::construct_vec2), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  \
  r = as_engine->RegisterObjectProperty(#vec"2", #type" x", asOFFSET(vec2, x));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"2", #type" y", asOFFSET(vec2, y));AngelScriptCheck(r); \
  \
  r = as_engine->RegisterObjectProperty(#vec"2", #type" r", asOFFSET(vec2, r));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"2", #type" g", asOFFSET(vec2, g));AngelScriptCheck(r); \
  \
  r = as_engine->RegisterObjectProperty(#vec"2", #type" s", asOFFSET(vec2, s));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"2", #type" t", asOFFSET(vec2, t));AngelScriptCheck(r); \
 


#define REGISTER_VEC3_(vec, type) \
  class HELPERCLASS_REGISTER_VEC3_##vec \
  { \
  public: \
    static void construct_type_type_type(vec##3 *v, type x, type y, type z) \
    { \
      v->x = x; \
      v->y = y; \
      v->z = z; \
    } \
    \
    static void construct_type(vec##3 *v, type x) \
    { \
      v->x = x; \
      v->y = x; \
      v->z = x; \
    } \
    static void construct_vec3(vec##3 *v, const vec##3 &other) \
    { \
      *v = other; \
    } \
    static void construct_vec2_float(vec##3 *v, const vec##2 &a, float b) \
    { \
      v->x = a.x; \
      v->y = a.y; \
      v->z = b; \
    } \
    static void construct_float_vec2(vec##3 *v, float a, const vec##2 &b) \
    { \
      v->x = a; \
      v->y = b.x; \
      v->z = b.y;\
    } \
    static void construct_vec4(vec##3 *v, const vec##4 &a) \
    { \
      v->x = a.x; \
      v->y = a.y; \
      v->z = a.z; \
    } \
  }; \
  r = as_engine->RegisterObjectBehaviour(#vec"3", AngelScript::asBEHAVE_CONSTRUCT, "void f("#type" x, "#type" y, "#type" z)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC3_##vec::construct_type_type_type), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectBehaviour(#vec"3", AngelScript::asBEHAVE_CONSTRUCT, "void f("#type" x)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC3_##vec::construct_type), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectBehaviour(#vec"3", AngelScript::asBEHAVE_CONSTRUCT, "void f("#vec"3 &in v)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC3_##vec::construct_vec3), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectBehaviour(#vec"3", AngelScript::asBEHAVE_CONSTRUCT, "void f("#vec"2 &in, float)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC3_##vec::construct_vec2_float), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectBehaviour(#vec"3", AngelScript::asBEHAVE_CONSTRUCT, "void f(float, "#vec"2 &in)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC3_##vec::construct_float_vec2), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectBehaviour(#vec"3", AngelScript::asBEHAVE_CONSTRUCT, "void f("#vec"4 &in)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC3_##vec::construct_vec4), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  \
  r = as_engine->RegisterObjectProperty(#vec"3", #type" x", asOFFSET(vec3, x));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"3", #type" y", asOFFSET(vec3, y));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"3", #type" z", asOFFSET(vec3, z));AngelScriptCheck(r); \
  \
  r = as_engine->RegisterObjectProperty(#vec"3", #type" r", asOFFSET(vec3, r));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"3", #type" g", asOFFSET(vec3, g));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"3", #type" b", asOFFSET(vec3, b));AngelScriptCheck(r); \
  \
  r = as_engine->RegisterObjectProperty(#vec"3", #type" s", asOFFSET(vec3, s));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"3", #type" t", asOFFSET(vec3, t));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"3", #type" p", asOFFSET(vec3, p));AngelScriptCheck(r); \
 

#define REGISTER_VEC4_(vec, type) \
  class HELPERCLASS_REGISTER_VEC4_##vec \
  { \
  public: \
    static void construct_type_type_type_type(vec##4 *v, type x, type y, type z, type w) \
    { \
      v->x = x; \
      v->y = y; \
      v->z = z; \
      v->w = w; \
    } \
    \
    static void construct_type(vec##4 *v, type x) \
    { \
      v->x = x; \
      v->y = x; \
      v->z = x; \
      v->w = x; \
    } \
    static void construct_vec4(vec##4 *v, const vec##4 &other) \
    { \
      *v = other; \
    } \
    static void construct_vec3_float(vec##4 *v, const vec##3 &a, float b) \
    { \
      v->x = a.x; \
      v->y = a.y; \
      v->z = a.z; \
      v->w = b; \
    } \
    static void construct_float_vec3(vec##4 *v, float a, const vec##3 &b) \
    { \
      v->x = a; \
      v->y = b.x; \
      v->z = b.y;\
      v->w = b.z;\
    } \
    static void construct_vec2_vec2(vec##4 *v, const vec##2 &a, const vec##2 &b) \
    { \
      v->x = a.x; \
      v->y = a.y; \
      v->z = b.x;\
      v->w = b.y;\
    } \
    static void construct_vec2_float_float(vec##4 *v, const vec##2 &a, float b, float c) \
    { \
      v->x = a.x; \
      v->y = a.y; \
      v->z = b;\
      v->w = c;\
    } \
    static void construct_float_vec2_float(vec##4 *v, float a, const vec##2 &b, float c) \
    { \
      v->x = a; \
      v->y = b.x; \
      v->z = b.y;\
      v->w = c;\
    } \
    static void construct_float_float_vec2(vec##4 *v, float a, float b, const vec##2 &c) \
    { \
      v->x = a; \
      v->y = b; \
      v->z = c.x;\
      v->w = c.y;\
    } \
  }; \
  r = as_engine->RegisterObjectBehaviour(#vec"4", AngelScript::asBEHAVE_CONSTRUCT, "void f("#type" x, "#type" y, "#type" z, "#type" w)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC4_##vec::construct_type_type_type_type), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectBehaviour(#vec"4", AngelScript::asBEHAVE_CONSTRUCT, "void f("#type" x)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC4_##vec::construct_type), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectBehaviour(#vec"4", AngelScript::asBEHAVE_CONSTRUCT, "void f("#vec"4 &in v)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC4_##vec::construct_vec4), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectBehaviour(#vec"4", AngelScript::asBEHAVE_CONSTRUCT, "void f("#vec"3 &in, float)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC4_##vec::construct_vec3_float), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectBehaviour(#vec"4", AngelScript::asBEHAVE_CONSTRUCT, "void f(float, "#vec"3 &in)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC4_##vec::construct_float_vec3), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectBehaviour(#vec"4", AngelScript::asBEHAVE_CONSTRUCT, "void f("#vec"2 &in, "#vec"2 &in)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC4_##vec::construct_vec2_vec2), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectBehaviour(#vec"4", AngelScript::asBEHAVE_CONSTRUCT, "void f("#vec"2 &in, float, float)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC4_##vec::construct_vec2_float_float), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectBehaviour(#vec"4", AngelScript::asBEHAVE_CONSTRUCT, "void f(float, "#vec"2 &in, float)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC4_##vec::construct_float_vec2_float), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  r = as_engine->RegisterObjectBehaviour(#vec"4", AngelScript::asBEHAVE_CONSTRUCT, "void f(float, float, "#vec"2 &in)", AngelScript::asFUNCTION(&HELPERCLASS_REGISTER_VEC4_##vec::construct_float_float_vec2), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r); \
  \
  r = as_engine->RegisterObjectProperty(#vec"4", #type" x", asOFFSET(vec4, x));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"4", #type" y", asOFFSET(vec4, y));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"4", #type" z", asOFFSET(vec4, z));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"4", #type" w", asOFFSET(vec4, w));AngelScriptCheck(r); \
  \
  r = as_engine->RegisterObjectProperty(#vec"4", #type" r", asOFFSET(vec4, r));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"4", #type" g", asOFFSET(vec4, g));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"4", #type" b", asOFFSET(vec4, b));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"4", #type" a", asOFFSET(vec4, a));AngelScriptCheck(r); \
  \
  r = as_engine->RegisterObjectProperty(#vec"4", #type" s", asOFFSET(vec4, s));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"4", #type" t", asOFFSET(vec4, t));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"4", #type" p", asOFFSET(vec4, p));AngelScriptCheck(r); \
  r = as_engine->RegisterObjectProperty(#vec"4", #type" q", asOFFSET(vec4, p));AngelScriptCheck(r); \
 


#define REGISTER_VEC(prefix, type) \
  REGISTER_VEC2_(prefix##vec, type) \
  REGISTER_VEC3_(prefix##vec, type) \
  REGISTER_VEC4_(prefix##vec, type)


void initVectorLibrary_classes(AngelScript::asIScriptEngine* as_engine)
{
  int r;

  // Register the vec2 class
  // asOBJ_VALUE because it's a value type
  // asOBJ_POD  because it doesn't contain pointer or any other dangerous stuff :)
  // asOBJ_APP_CLASS because its a class
  // asOBJ_APP_CLASS_CONSTRUCTOR because it has a default contructor
  // asOBJ_APP_CLASS_ASSIGNMENT because it's able to assign vectors to other vectors
  // asOBJ_APP_CLASS_COPY_CONSTRUCTOR because it has a copy constructor
  // asOBJ_APP_CLASS_ALLFLOATS because it consists only of floats
#define DECLARE_VECTOR_TYPE(name, FLAGS) \
  r = as_engine->RegisterObjectType(#name, \
                                    sizeof(name), \
                                    AngelScript::asOBJ_VALUE | \
                                    AngelScript::asOBJ_POD | \
                                    AngelScript::asOBJ_APP_CLASS | \
                                    AngelScript::asOBJ_APP_CLASS_CONSTRUCTOR | \
                                    AngelScript::asOBJ_APP_CLASS_ASSIGNMENT | \
                                    AngelScript::asOBJ_APP_CLASS_COPY_CONSTRUCTOR | \
                                    FLAGS); \
  AngelScriptCheck(r);

  DECLARE_VECTOR_TYPE(vec2, AngelScript::asOBJ_APP_CLASS_ALLFLOATS);
  DECLARE_VECTOR_TYPE(vec3, AngelScript::asOBJ_APP_CLASS_ALLFLOATS);
  DECLARE_VECTOR_TYPE(vec4, AngelScript::asOBJ_APP_CLASS_ALLFLOATS);
  DECLARE_VECTOR_TYPE(dvec2, 0);
  DECLARE_VECTOR_TYPE(dvec3, 0);
  DECLARE_VECTOR_TYPE(dvec4, 0);
  DECLARE_VECTOR_TYPE(bvec2, 0);
  DECLARE_VECTOR_TYPE(bvec3, 0);
  DECLARE_VECTOR_TYPE(bvec4, 0);
  DECLARE_VECTOR_TYPE(ivec2, AngelScript::asOBJ_APP_CLASS_ALLINTS);
  DECLARE_VECTOR_TYPE(ivec3, AngelScript::asOBJ_APP_CLASS_ALLINTS);
  DECLARE_VECTOR_TYPE(ivec4, AngelScript::asOBJ_APP_CLASS_ALLINTS);
  DECLARE_VECTOR_TYPE(uvec2, 0);
  DECLARE_VECTOR_TYPE(uvec3, 0);
  DECLARE_VECTOR_TYPE(uvec4, 0);

  REGISTER_VEC(,float);
  REGISTER_VEC(d,double);
  REGISTER_VEC(b,bool);
  REGISTER_VEC(i,int);
  REGISTER_VEC(u,uint);

  REGISTER_CAST(ivec, uvec, asBEHAVE_IMPLICIT_VALUE_CAST);
  REGISTER_CAST(ivec,  vec, asBEHAVE_IMPLICIT_VALUE_CAST);
  REGISTER_CAST(uvec,  vec, asBEHAVE_IMPLICIT_VALUE_CAST);
  REGISTER_CAST(ivec, dvec, asBEHAVE_IMPLICIT_VALUE_CAST);
  REGISTER_CAST(uvec, dvec, asBEHAVE_IMPLICIT_VALUE_CAST);
  REGISTER_CAST( vec, dvec, asBEHAVE_IMPLICIT_VALUE_CAST);

  REGISTER_REAL_OPERATORS(, float);
  REGISTER_REAL_OPERATORS(d, double);
  REGISTER_INTEGER_OPERATORS(i, int);
  REGISTER_INTEGER_OPERATORS(u, uint);
  REGISTER_BASIC_OPERATORS(b, bool);
}


} // namespace Angelscriptintegration

