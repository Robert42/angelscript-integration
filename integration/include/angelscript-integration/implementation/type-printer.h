#ifndef ANGELSCRIPT_IMPLEMENTATION_TYPEPRINTER_H
#define ANGELSCRIPT_IMPLEMENTATION_TYPEPRINTER_H

#ifdef __GXX_ABI_VERSION
#include <cxxabi.h>
#endif

#include <QDebug>

namespace AngelScript {
namespace impl {

template<typename...>
struct TypePrinter;

template<>
struct TypePrinter<>
{
  static void print()
  {
  }
};

template<typename T, typename... T_rest>
struct TypePrinter<T, T_rest...>
{
  static void print()
  {
    const char* name = typeid(T).name();

#ifdef __GXX_ABI_VERSION
    char temp[1024];

    size_t length = 1024;
    int status;

    abi::__cxa_demangle(name, temp, &length, &status);

    name = temp;
#endif

    qDebug() << name;
    TypePrinter<T_rest...>::print();
  }
};

} // namespace impl
} // namespace AngelScript

#endif // ANGELSCRIPT_IMPLEMENTATION_TYPEPRINTER_H
