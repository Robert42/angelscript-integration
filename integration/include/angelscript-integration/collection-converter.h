#ifndef ANGELSCRIPTINTEGRATION_COLLECTIONCONVERTER_H
#define ANGELSCRIPTINTEGRATION_COLLECTIONCONVERTER_H

#include <sdk/add_on/scriptarray/scriptarray.h>
#include <sdk/add_on/scriptdictionary/scriptdictionary.h>

#include <QSet>

namespace AngelScriptIntegration {

template<typename T>
QSet<T> scriptArrayToSet(AngelScript::CScriptArray* array)
{
  QSet<T> set;

  const size_t n = array->GetSize();

  for(size_t i=0; i<n; ++i)
    set.insert(*reinterpret_cast<T*>(array->At(i)));

  return set;
}

QSet<QString> scriptArrayToStringSet(AngelScript::CScriptArray* array)
{
  QSet<QString> set;

  const size_t n = array->GetSize();

  for(size_t i=0; i<n; ++i)
    set.insert(QString::fromStdString(*reinterpret_cast<std::string*>(array->At(i))));

  return set;
}

template<typename T>
QHash<QString, T> scriptDictionaryToHash(AngelScript::CScriptDictionary* dict, const QSet<int>& typeIds)
{
  QHash<QString, T> hash;

  for(AngelScript::CScriptDictionary::CIterator i=dict->begin(); i!=dict->end(); ++i)
  {
    QString key = QString::fromStdString(i.GetKey());
    if(typeIds.contains(i.GetTypeId()))
    {
      T v;
      if(!i.GetValue(&v, i.GetTypeId()))
        Q_UNREACHABLE();
      hash[key] = v;
    }
  }

  return hash;
}

} // namespace AngelScriptIntegration

#endif // ANGELSCRIPTINTEGRATION_COLLECTIONCONVERTER_H
