#include "include-glm.h"
#include <QDebug>
#include <angelscript.h>
#include <angelscript-integration/angelscript-integration.h>

#include <glm/gtc/quaternion.hpp>

namespace AngelScriptIntegration {

inline void construct_quat(glm::quat *q, float w, float x, float y, float z)
{
  q->w = w;
  q->x = x;
  q->y = y;
  q->z = z;
}

void init_glm_quat(AngelScript::asIScriptEngine* as_engine)
{
  int r;
  r = as_engine->RegisterObjectType("quat",
                                    sizeof(glm::quat),
                                    AngelScript::asOBJ_VALUE |
                                    AngelScript::asOBJ_POD |
                                    AngelScript::asOBJ_APP_CLASS |
                                    AngelScript::asOBJ_APP_CLASS_CONSTRUCTOR |
                                    AngelScript::asOBJ_APP_CLASS_ASSIGNMENT |
                                    AngelScript::asOBJ_APP_CLASS_COPY_CONSTRUCTOR |
                                    AngelScript::asOBJ_APP_CLASS_ALLFLOATS);
  AngelScriptCheck(r);

  r = as_engine->RegisterObjectBehaviour("quat", AngelScript::asBEHAVE_CONSTRUCT, "void f(float w, float x, float y, float z)", AngelScript::asFUNCTION(construct_quat), AngelScript::asCALL_CDECL_OBJFIRST);AngelScriptCheck(r);
  AngelScriptCheck(r);
}

} // namespace AngelScriptIntegration
