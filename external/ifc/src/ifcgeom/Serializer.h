#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <ifcparse/IfcFile.h>

class Serializer {
public:
  virtual ~Serializer() {}

  virtual bool ready() = 0;
  virtual void writeHeader() = 0;
  virtual void finalize() = 0;
  virtual void setFile(IfcParse::IfcFile *) = 0;
};

#endif