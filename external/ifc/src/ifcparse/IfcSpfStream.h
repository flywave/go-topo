#ifndef IFCSPFSTREAM_H
#define IFCSPFSTREAM_H

#include <ifcparse/ifc_parse_api.h>

#include <string>

#ifdef USE_MMAP
#include <boost/iostreams/device/mapped_file.hpp>
#endif

namespace IfcParse {
/// The IfcSpfStream class represents a ISO 10303-21 IFC-SPF file in memory.
/// The file is interpreted as a sequence of tokens which are lazily
/// interpreted only when requested.
class IFC_PARSE_API IfcSpfStream {
private:
#ifdef USE_MMAP
  boost::iostreams::mapped_file_source mfs;
#endif
  FILE *stream_;
  const char *buffer_;
  unsigned int ptr_;
  unsigned int len_;

public:
  bool valid;
  bool eof;
  unsigned int size;
#ifdef USE_MMAP
  IfcSpfStream(const std::string &path, bool mmap = false);
#else
  IfcSpfStream(const std::string &path);
#endif
  IfcSpfStream(std::istream &stream, int length);
  IfcSpfStream(void *data, int length);
  ~IfcSpfStream();
  /// Returns the character at the cursor
  char Peek();
  /// Returns the character at specified offset
  char Read(unsigned int offset);
  /// Increment the file cursor and reads new page if necessary
  void Inc();
  void Close();
  /// Moves the file cursor to an arbitrary offset in the file
  void Seek(unsigned int offset);
  /// Returns the cursor position
  unsigned int Tell() const;

  bool is_eof_at(unsigned int) const;
  void increment_at(unsigned int &);
  char peek_at(unsigned int);
};
} // namespace IfcParse

#endif
