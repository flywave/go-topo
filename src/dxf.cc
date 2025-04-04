#if defined(_MSC_VER) && !defined(_USE_MATH_DEFINES)
// required by windows for M_PI definition
#define _USE_MATH_DEFINES
#endif
#include <cassert>
#include <cctype>
#include <clocale>
#include <cmath>
#if __cpp_lib_to_chars
#include <charconv>
#endif

#include <functional>
#include <iomanip>
#include <stdexcept>

#include "dxf.hh"

#include <iostream>

namespace {

class ScopedCLocale {
public:
  ScopedCLocale(int category)
      : m_category(category), m_savedLocale(std::setlocale(category, nullptr)) {
    std::setlocale(category, "C");
  }

  ~ScopedCLocale() { std::setlocale(m_category, m_savedLocale); }

private:
  int m_category = 0;
  const char *m_savedLocale = nullptr;
};

} // namespace

namespace flywave {
namespace dxf {
namespace dxf_internal {

template <typename T>
typename std::enable_if<std::is_same<T, int>::value, bool>::type
is_string_to_error_value_impl(T value) {
  return value == std::numeric_limits<int>::max();
}

template <typename T>
typename std::enable_if<std::is_same<T, unsigned>::value, bool>::type
is_string_to_error_value_impl(T value) {
  return value == std::numeric_limits<unsigned>::max();
}

template <typename T>
typename std::enable_if<std::is_same<T, double>::value, bool>::type
is_string_to_error_value_impl(T value) {
  const double dMax = std::numeric_limits<double>::max();
  return std::abs(value - dMax) * 1000000000000.0 <=
         std::min(std::abs(value), std::abs(dMax));
}

template <typename T> bool is_string_to_error_value(T value) {
  return is_string_to_error_value_impl<T>(value);
}

template <typename T>
typename std::enable_if<std::is_same<T, int>::value, T>::type
string_to_numeric_impl(const std::string &line,
                       string_to_error_mode errorMode) {
  try {
    return std::stoi(line);
  } catch (...) {
    if (errorMode == string_to_error_mode::ReturnErrorValue) {
      return std::numeric_limits<T>::max();
    } else {
      throw std::runtime_error("Failed to fetch int value from line:\n" + line);
    }
  }
}

template <typename T>
typename std::enable_if<std::is_same<T, unsigned>::value, T>::type
string_to_numeric_impl(const std::string &line,
                       string_to_error_mode errorMode) {
  try {
    return static_cast<unsigned>(std::stoul(line));
  } catch (...) {
    if (errorMode == string_to_error_mode::ReturnErrorValue) {
      return std::numeric_limits<T>::max();
    } else {
      throw std::runtime_error("Failed to fetch unsigned value from line:\n" +
                               line);
    }
  }
}

template <typename T>
typename std::enable_if<std::is_same<T, double>::value, T>::type
string_to_numeric_impl(const std::string &line,
                       string_to_error_mode errorMode) {
  try {
    return std::stod(line);
  } catch (...) {
    if (errorMode == string_to_error_mode::ReturnErrorValue) {
      return std::numeric_limits<T>::max();
    } else {
      throw std::runtime_error("Failed to fetch double value from line:\n" +
                               line);
    }
  }
}

template <typename T>
T string_to_numeric(const std::string &line, string_to_error_mode errorMode) {
  return string_to_numeric_impl<T>(line, errorMode);
}

int string_to_int(const std::string &line, string_to_error_mode errorMode) {
  return string_to_numeric<int>(line, errorMode);
}

unsigned string_to_unsigned(const std::string &line,
                            string_to_error_mode errorMode) {
  return string_to_numeric<unsigned>(line, errorMode);
}

double string_to_double(const std::string &line,
                        string_to_error_mode errorMode) {
  return string_to_numeric<double>(line, errorMode);
}

} // namespace dxf_internal

using namespace dxf_internal;

vector3d tovector3d(const double *a) {
  vector3d result;
  result.x = a[0];
  result.y = a[1];
  result.z = a[2];
  return result;
}

dxf_write::dxf_write(const char *filepath)
    : _ofs(filepath, std::ios::out), _handle(0xA00), _poly_override(false),
      _layer_name("none") {

  _fail = false;
  _version = 12;

  if (!_ofs)
    _fail = true;
  else
    _ofs.imbue(std::locale::classic());
}

dxf_write::~dxf_write() {}

void dxf_write::init() {
  write_header_section();
  make_block_record_table_head();
  make_block_section_head();
}

void dxf_write::end_run() {
  make_layer_table();
  make_block_record_table_body();

  write_classes_section();
  write_tables_section();
  write_blocks_section();
  write_entities_section();
  write_objects_section();

  _ofs << "  0" << std::endl;
  _ofs << "EOF";
}

void dxf_write::write_header_section() {
  std::stringstream ss;

  _ofs << "999" << std::endl;
  _ofs << ss.str() << std::endl;

  ss.str("");
  ss.clear();
  ss << "header" << _version << ".rub";
  std::string fileSpec = _data_dir + ss.str();
  _ofs << get_plate_file(fileSpec);
}

void dxf_write::write_classes_section() {
  if (_version < 14) {
    return;
  }

  std::stringstream ss;
  ss << "classes" << _version << ".rub";
  std::string fileSpec = _data_dir + ss.str();
  _ofs << get_plate_file(fileSpec);
}

void dxf_write::write_tables_section() {
  std::stringstream ss;
  ss << "tables1" << _version << ".rub";
  std::string fileSpec = _data_dir + ss.str();
  _ofs << get_plate_file(fileSpec);

  _ofs << _ss_layer.str();

  ss.str("");
  ss.clear();
  ss << "tables2" << _version << ".rub";
  fileSpec = _data_dir + ss.str();
  _ofs << get_plate_file(fileSpec);

  if (_version > 12) {
    _ofs << _ss_blk_record.str();
    _ofs << "  0" << std::endl;
    _ofs << "ENDTAB" << std::endl;
  }
  _ofs << "  0" << std::endl;
  _ofs << "ENDSEC" << std::endl;
}

void dxf_write::make_layer_table() {
  std::string tablehash = get_layer_handle();
  _ss_layer << "  0" << std::endl;
  _ss_layer << "TABLE" << std::endl;
  _ss_layer << "  2" << std::endl;
  _ss_layer << "LAYER" << std::endl;
  _ss_layer << "  5" << std::endl;
  _ss_layer << tablehash << std::endl;
  if (_version > 12) {
    _ss_layer << "330" << std::endl;
    _ss_layer << 0 << std::endl;
    _ss_layer << "100" << std::endl;
    _ss_layer << "AcDbSymbolTable" << std::endl;
  }
  _ss_layer << " 70" << std::endl;
  _ss_layer << _layer_list.size() + 1 << std::endl;

  _ss_layer << "  0" << std::endl;
  _ss_layer << "LAYER" << std::endl;
  _ss_layer << "  5" << std::endl;
  _ss_layer << get_layer_handle() << std::endl;
  if (_version > 12) {
    _ss_layer << "330" << std::endl;
    _ss_layer << tablehash << std::endl;
    _ss_layer << "100" << std::endl;
    _ss_layer << "AcDbSymbolTableRecord" << std::endl;
    _ss_layer << "100" << std::endl;
    _ss_layer << "AcDbLayerTableRecord" << std::endl;
  }
  _ss_layer << "  2" << std::endl;
  _ss_layer << "0" << std::endl;
  _ss_layer << " 70" << std::endl;
  _ss_layer << "   0" << std::endl;
  _ss_layer << " 62" << std::endl;
  _ss_layer << "   7" << std::endl;
  _ss_layer << "  6" << std::endl;
  _ss_layer << "CONTINUOUS" << std::endl;

  for (auto &l : _layer_list) {
    _ss_layer << "  0" << std::endl;
    _ss_layer << "LAYER" << std::endl;
    _ss_layer << "  5" << std::endl;
    _ss_layer << get_layer_handle() << std::endl;
    if (_version > 12) {
      _ss_layer << "330" << std::endl;
      _ss_layer << tablehash << std::endl;
      _ss_layer << "100" << std::endl;
      _ss_layer << "AcDbSymbolTableRecord" << std::endl;
      _ss_layer << "100" << std::endl;
      _ss_layer << "AcDbLayerTableRecord" << std::endl;
    }
    _ss_layer << "  2" << std::endl;
    _ss_layer << l << std::endl;
    _ss_layer << " 70" << std::endl;
    _ss_layer << "    0" << std::endl;
    _ss_layer << " 62" << std::endl;
    _ss_layer << "    7" << std::endl;
    _ss_layer << "  6" << std::endl;
    _ss_layer << "CONTINUOUS" << std::endl;
  }
  _ss_layer << "  0" << std::endl;
  _ss_layer << "ENDTAB" << std::endl;
}

void dxf_write::make_block_record_table_head() {
  if (_version < 14) {
    return;
  }
  std::string tablehash = get_blk_record_handle();
  _save_block_record_table_handle = tablehash;
  _ss_blk_record << "  0" << std::endl;
  _ss_blk_record << "TABLE" << std::endl;
  _ss_blk_record << "  2" << std::endl;
  _ss_blk_record << "BLOCK_RECORD" << std::endl;
  _ss_blk_record << "  5" << std::endl;
  _ss_blk_record << tablehash << std::endl;
  _ss_blk_record << "330" << std::endl;
  _ss_blk_record << "0" << std::endl;
  _ss_blk_record << "100" << std::endl;
  _ss_blk_record << "AcDbSymbolTable" << std::endl;
  _ss_blk_record << "  70" << std::endl;
  _ss_blk_record << (_block_list.size() + 5) << std::endl;

  _save_model_space_handle = get_blk_record_handle();
  _ss_blk_record << "  0" << std::endl;
  _ss_blk_record << "BLOCK_RECORD" << std::endl;
  _ss_blk_record << "  5" << std::endl;
  _ss_blk_record << _save_model_space_handle << std::endl;
  _ss_blk_record << "330" << std::endl;
  _ss_blk_record << tablehash << std::endl;
  _ss_blk_record << "100" << std::endl;
  _ss_blk_record << "AcDbSymbolTableRecord" << std::endl;
  _ss_blk_record << "100" << std::endl;
  _ss_blk_record << "AcDbBlockTableRecord" << std::endl;
  _ss_blk_record << "  2" << std::endl;
  _ss_blk_record << "*MODEL_SPACE" << std::endl;

  _save_paper_space_handle = get_blk_record_handle();
  _ss_blk_record << "  0" << std::endl;
  _ss_blk_record << "BLOCK_RECORD" << std::endl;
  _ss_blk_record << "  5" << std::endl;
  _ss_blk_record << _save_paper_space_handle << std::endl;
  _ss_blk_record << "330" << std::endl;
  _ss_blk_record << tablehash << std::endl;
  _ss_blk_record << "100" << std::endl;
  _ss_blk_record << "AcDbSymbolTableRecord" << std::endl;
  _ss_blk_record << "100" << std::endl;
  _ss_blk_record << "AcDbBlockTableRecord" << std::endl;
  _ss_blk_record << "  2" << std::endl;
  _ss_blk_record << "*PAPER_SPACE" << std::endl;
}

void dxf_write::make_block_record_table_body() {
  if (_version < 14) {
    return;
  }

  int iBlkRecord = 0;
  for (auto &b : _block_list) {
    _ss_blk_record << "  0" << std::endl;
    _ss_blk_record << "BLOCK_RECORD" << std::endl;
    _ss_blk_record << "  5" << std::endl;
    _ss_blk_record << _blk_record_list.at(iBlkRecord) << std::endl;
    _ss_blk_record << "330" << std::endl;
    _ss_blk_record << _save_block_record_table_handle << std::endl;
    _ss_blk_record << "100" << std::endl;
    _ss_blk_record << "AcDbSymbolTableRecord" << std::endl;
    _ss_blk_record << "100" << std::endl;
    _ss_blk_record << "AcDbBlockTableRecord" << std::endl;
    _ss_blk_record << "  2" << std::endl;
    _ss_blk_record << b << std::endl;
    iBlkRecord++;
  }
}

void dxf_write::make_block_section_head() {
  _ss_block << "  0" << std::endl;
  _ss_block << "SECTION" << std::endl;
  _ss_block << "  2" << std::endl;
  _ss_block << "BLOCKS" << std::endl;
  _ss_block << "  0" << std::endl;
  _ss_block << "BLOCK" << std::endl;
  _ss_block << "  5" << std::endl;
  _current_block = get_block_handle();
  _ss_block << _current_block << std::endl;
  if (_version > 12) {
    _ss_block << "330" << std::endl;
    _ss_block << _save_model_space_handle << std::endl;
    _ss_block << "100" << std::endl;
    _ss_block << "AcDbEntity" << std::endl;
  }
  _ss_block << "  8" << std::endl;
  _ss_block << "0" << std::endl;
  if (_version > 12) {
    _ss_block << "100" << std::endl;
    _ss_block << "AcDbBlockBegin" << std::endl;
  }
  _ss_block << "  2" << std::endl;
  _ss_block << "*MODEL_SPACE" << std::endl;
  _ss_block << " 70" << std::endl;
  _ss_block << "   0" << std::endl;
  _ss_block << " 10" << std::endl;
  _ss_block << 0.0 << std::endl;
  _ss_block << " 20" << std::endl;
  _ss_block << 0.0 << std::endl;
  _ss_block << " 30" << std::endl;
  _ss_block << 0.0 << std::endl;
  _ss_block << "  3" << std::endl;
  _ss_block << "*MODEL_SPACE" << std::endl;
  _ss_block << "  1" << std::endl;
  _ss_block << " " << std::endl;
  _ss_block << "  0" << std::endl;
  _ss_block << "ENDBLK" << std::endl;
  _ss_block << "  5" << std::endl;
  _ss_block << get_block_handle() << std::endl;
  if (_version > 12) {
    _ss_block << "330" << std::endl;
    _ss_block << _save_model_space_handle << std::endl;
    _ss_block << "100" << std::endl;
    _ss_block << "AcDbEntity" << std::endl;
  }
  _ss_block << "  8" << std::endl;
  _ss_block << "0" << std::endl;
  if (_version > 12) {
    _ss_block << "100" << std::endl;
    _ss_block << "AcDbBlockEnd" << std::endl;
  }

  _ss_block << "  0" << std::endl;
  _ss_block << "BLOCK" << std::endl;
  _ss_block << "  5" << std::endl;
  _current_block = get_block_handle();
  _ss_block << _current_block << std::endl;
  if (_version > 12) {
    _ss_block << "330" << std::endl;
    _ss_block << _save_paper_space_handle << std::endl;
    _ss_block << "100" << std::endl;
    _ss_block << "AcDbEntity" << std::endl;
    _ss_block << " 67" << std::endl;
    _ss_block << "1" << std::endl;
  }
  _ss_block << "  8" << std::endl;
  _ss_block << "0" << std::endl;
  if (_version > 12) {
    _ss_block << "100" << std::endl;
    _ss_block << "AcDbBlockBegin" << std::endl;
  }
  _ss_block << "  2" << std::endl;
  _ss_block << "*PAPER_SPACE" << std::endl;
  _ss_block << " 70" << std::endl;
  _ss_block << "   0" << std::endl;
  _ss_block << " 10" << std::endl;
  _ss_block << 0.0 << std::endl;
  _ss_block << " 20" << std::endl;
  _ss_block << 0.0 << std::endl;
  _ss_block << " 30" << std::endl;
  _ss_block << 0.0 << std::endl;
  _ss_block << "  3" << std::endl;
  _ss_block << "*PAPER_SPACE" << std::endl;
  _ss_block << "  1" << std::endl;
  _ss_block << " " << std::endl;
  _ss_block << "  0" << std::endl;
  _ss_block << "ENDBLK" << std::endl;
  _ss_block << "  5" << std::endl;
  _ss_block << get_block_handle() << std::endl;
  if (_version > 12) {
    _ss_block << "330" << std::endl;
    _ss_block << _save_paper_space_handle << std::endl;
    _ss_block << "100" << std::endl;
    _ss_block << "AcDbEntity" << std::endl;
    _ss_block << " 67" << std::endl; // paper_space flag
    _ss_block << "    1" << std::endl;
  }
  _ss_block << "  8" << std::endl;
  _ss_block << "0" << std::endl;
  if (_version > 12) {
    _ss_block << "100" << std::endl;
    _ss_block << "AcDbBlockEnd" << std::endl;
  }
}

bool filePathExists(const char *filename) {
  std::ifstream ifile(filename);
  return (bool)ifile;
}

std::string dxf_write::get_plate_file(const std::string &fileSpec) {
  std::stringstream outString;
  if (!filePathExists(fileSpec.c_str())) {
    // Base::Console().Message("dxf unable to open %s!\n",fileSpec.c_str());
  } else {
    std::string line;
    std::ifstream inFile(fileSpec);

    while (!inFile.eof()) {
      std::getline(inFile, line);
      if (!inFile.eof()) {
        outString << line << '\n';
      }
    }
  }
  return outString.str();
}

std::string dxf_write::get_handle() {
  _handle++;
  std::stringstream ss;
  ss << std::uppercase << std::hex << std::setfill('0') << std::setw(2);
  ss << _handle;
  return ss.str();
}

std::string dxf_write::get_entity_handle() {
  return get_handle();
  //    _entity_handle++;
  //    std::stringstream ss;
  //    ss << std::uppercase << std::hex << std::setfill('0') << std::setw(2);
  //    ss << _entity_handle;
  //    return ss.str();
}

std::string dxf_write::get_layer_handle() {
  return get_handle();
  //    _layer_handle++;
  //    std::stringstream ss;
  //    ss << std::uppercase << std::hex << std::setfill('0') << std::setw(2);
  //    ss << _layer_handle;
  //    return ss.str();
}

std::string dxf_write::get_block_handle() {
  return get_handle();
  //    _block_handle++;
  //    std::stringstream ss;
  //    ss << std::uppercase << std::hex << std::setfill('0') << std::setw(2);
  //    ss << _block_handle;
  //    return ss.str();
}

std::string dxf_write::get_blk_record_handle() {
  return get_handle();
  //    _blk_record_handle++;
  //    std::stringstream ss;
  //    ss << std::uppercase << std::hex << std::setfill('0') << std::setw(2);
  //    ss << _blk_record_handle;
  //    return ss.str();
}

void dxf_write::add_block_name(std::string b, std::string h) {
  _block_list.push_back(b);
  _blk_record_list.push_back(h);
}

void dxf_write::set_layer_name(std::string s) {
  _layer_name = s;
  _layer_list.push_back(s);
}

void dxf_write::write_line(const double *s, const double *e) {
  put_line(tovector3d(s), tovector3d(e), _ss_entity, get_entity_handle(),
           _save_model_space_handle);
}

void dxf_write::put_line(const vector3d &s, const vector3d &e,
                         std::ostringstream &outStream,
                         const std::string &handle,
                         const std::string &ownerHandle) {
  outStream << "  0" << std::endl;
  outStream << "LINE" << std::endl;
  outStream << "  5" << std::endl;
  outStream << handle << std::endl;
  if (_version > 12) {
    outStream << "330" << std::endl;
    outStream << ownerHandle << std::endl;
    outStream << "100" << std::endl;
    outStream << "AcDbEntity" << std::endl;
  }
  outStream << "  8" << std::endl;            // Group code for layer name
  outStream << get_layer_name() << std::endl; // Layer number
  if (_version > 12) {
    outStream << "100" << std::endl;
    outStream << "AcDbLine" << std::endl;
  }
  outStream << " 10" << std::endl; // Start point of line
  outStream << s.x << std::endl;   // X in WCS coordinates
  outStream << " 20" << std::endl;
  outStream << s.y << std::endl; // Y in WCS coordinates
  outStream << " 30" << std::endl;
  outStream << s.z << std::endl;   // Z in WCS coordinates
  outStream << " 11" << std::endl; // End point of line
  outStream << e.x << std::endl;   // X in WCS coordinates
  outStream << " 21" << std::endl;
  outStream << e.y << std::endl; // Y in WCS coordinates
  outStream << " 31" << std::endl;
  outStream << e.z << std::endl; // Z in WCS coordinates
}

void dxf_write::write_lw_polyline(const lw_poly_data_out &pd) {
  _ss_entity << "  0" << std::endl;
  _ss_entity << "LWPOLYLINE" << std::endl;
  _ss_entity << "  5" << std::endl;
  _ss_entity << get_entity_handle() << std::endl;
  if (_version > 12) {
    _ss_entity << "330" << std::endl;
    _ss_entity << _save_model_space_handle << std::endl;
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbEntity" << std::endl;
  }
  if (_version > 12) {
    _ss_entity << "100" << std::endl; // 100 groups are not part of R12
    _ss_entity << "AcDbPolyline" << std::endl;
  }
  _ss_entity << "  8" << std::endl;            // Group code for layer name
  _ss_entity << get_layer_name() << std::endl; // Layer name
  _ss_entity << " 90" << std::endl;
  _ss_entity << pd.nvert << std::endl; // number of vertices
  _ss_entity << " 70" << std::endl;
  _ss_entity << pd.flag << std::endl;
  _ss_entity << " 43" << std::endl;
  _ss_entity << "0" << std::endl; // Constant width opt

  for (auto &p : pd.verts) {
    _ss_entity << " 10" << std::endl; // Vertices
    _ss_entity << p.x << std::endl;
    _ss_entity << " 20" << std::endl;
    _ss_entity << p.y << std::endl;
  }
  for (auto &s : pd.start_width) {
    _ss_entity << " 40" << std::endl;
    _ss_entity << s << std::endl; // Start Width
  }
  for (auto &e : pd.end_width) {
    _ss_entity << " 41" << std::endl;
    _ss_entity << e << std::endl; // End Width
  }
  for (auto &b : pd.bulge) { // bulge
    _ss_entity << " 42" << std::endl;
    _ss_entity << b << std::endl;
  }
}

void dxf_write::write_polyline(const lw_poly_data_out &pd) {
  _ss_entity << "  0" << std::endl;
  _ss_entity << "POLYLINE" << std::endl;
  _ss_entity << "  5" << std::endl;
  _ss_entity << get_entity_handle() << std::endl;
  if (_version > 12) {
    _ss_entity << "330" << std::endl;
    _ss_entity << _save_model_space_handle << std::endl;
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbEntity" << std::endl;
  }
  _ss_entity << "  8" << std::endl;
  _ss_entity << get_layer_name() << std::endl; // Layer name
  if (_version > 12) {
    _ss_entity << "100" << std::endl; // 100 groups are not part of R12
    _ss_entity << "AcDbPolyline" << std::endl;
  }
  _ss_entity << " 66" << std::endl;
  _ss_entity << "     1" << std::endl; // vertices follow
  _ss_entity << " 10" << std::endl;
  _ss_entity << "0.0" << std::endl;
  _ss_entity << " 20" << std::endl;
  _ss_entity << "0.0" << std::endl;
  _ss_entity << " 30" << std::endl;
  _ss_entity << "0.0" << std::endl;
  _ss_entity << " 70" << std::endl;
  _ss_entity << "0" << std::endl;
  for (auto &p : pd.verts) {
    _ss_entity << "  0" << std::endl;
    _ss_entity << "VERTEX" << std::endl;
    _ss_entity << "  5" << std::endl;
    _ss_entity << get_entity_handle() << std::endl;
    _ss_entity << "  8" << std::endl;
    _ss_entity << get_layer_name() << std::endl;
    _ss_entity << " 10" << std::endl;
    _ss_entity << p.x << std::endl;
    _ss_entity << " 20" << std::endl;
    _ss_entity << p.y << std::endl;
    _ss_entity << " 30" << std::endl;
    _ss_entity << "0.0" << std::endl;
  }
  _ss_entity << "  0" << std::endl;
  _ss_entity << "SEQEND" << std::endl;
  _ss_entity << "  5" << std::endl;
  _ss_entity << get_entity_handle() << std::endl;
  _ss_entity << "  8" << std::endl;
  _ss_entity << get_layer_name() << std::endl;
}

void dxf_write::write_point(const double *s) {
  _ss_entity << "  0" << std::endl;
  _ss_entity << "POINT" << std::endl;
  _ss_entity << "  5" << std::endl;
  _ss_entity << get_entity_handle() << std::endl;
  if (_version > 12) {
    _ss_entity << "330" << std::endl;
    _ss_entity << _save_model_space_handle << std::endl;
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbEntity" << std::endl;
  }
  _ss_entity << "  8" << std::endl;            // Group code for layer name
  _ss_entity << get_layer_name() << std::endl; // Layer name
  if (_version > 12) {
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbPoint" << std::endl;
  }
  _ss_entity << " 10" << std::endl;
  _ss_entity << s[0] << std::endl; // X in WCS coordinates
  _ss_entity << " 20" << std::endl;
  _ss_entity << s[1] << std::endl; // Y in WCS coordinates
  _ss_entity << " 30" << std::endl;
  _ss_entity << s[2] << std::endl; // Z in WCS coordinates
}

void dxf_write::write_arc(const double *s, const double *e, const double *c,
                          bool dir) {
  double ax = s[0] - c[0];
  double ay = s[1] - c[1];
  double bx = e[0] - c[0];
  double by = e[1] - c[1];

  double start_angle = atan2(ay, ax) * 180 / M_PI;
  double end_angle = atan2(by, bx) * 180 / M_PI;
  double radius = sqrt(ax * ax + ay * ay);
  if (!dir) {
    double temp = start_angle;
    start_angle = end_angle;
    end_angle = temp;
  }
  _ss_entity << "  0" << std::endl;
  _ss_entity << "ARC" << std::endl;
  _ss_entity << "  5" << std::endl;
  _ss_entity << get_entity_handle() << std::endl;
  if (_version > 12) {
    _ss_entity << "330" << std::endl;
    _ss_entity << _save_model_space_handle << std::endl;
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbEntity" << std::endl;
  }
  _ss_entity << "  8" << std::endl;            // Group code for layer name
  _ss_entity << get_layer_name() << std::endl; // Layer number

  if (_version > 12) {
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbCircle" << std::endl;
  }
  _ss_entity << " 10" << std::endl; // Centre X
  _ss_entity << c[0] << std::endl;  // X in WCS coordinates
  _ss_entity << " 20" << std::endl;
  _ss_entity << c[1] << std::endl; // Y in WCS coordinates
  _ss_entity << " 30" << std::endl;
  _ss_entity << c[2] << std::endl;   // Z in WCS coordinates
  _ss_entity << " 40" << std::endl;  //
  _ss_entity << radius << std::endl; // Radius

  if (_version > 12) {
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbArc" << std::endl;
  }
  _ss_entity << " 50" << std::endl;
  _ss_entity << start_angle << std::endl; // Start angle
  _ss_entity << " 51" << std::endl;
  _ss_entity << end_angle << std::endl; // End angle
}

void dxf_write::write_circle(const double *c, double radius) {
  _ss_entity << "  0" << std::endl;
  _ss_entity << "CIRCLE" << std::endl;
  _ss_entity << "  5" << std::endl;
  _ss_entity << get_entity_handle() << std::endl;
  if (_version > 12) {
    _ss_entity << "330" << std::endl;
    _ss_entity << _save_model_space_handle << std::endl;
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbEntity" << std::endl;
  }
  _ss_entity << "  8" << std::endl;            // Group code for layer name
  _ss_entity << get_layer_name() << std::endl; // Layer number
  if (_version > 12) {
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbCircle" << std::endl;
  }
  _ss_entity << " 10" << std::endl; // Centre X
  _ss_entity << c[0] << std::endl;  // X in WCS coordinates
  _ss_entity << " 20" << std::endl;
  _ss_entity << c[1] << std::endl; // Y in WCS coordinates

  _ss_entity << " 40" << std::endl;  //
  _ss_entity << radius << std::endl; // Radius
}

void dxf_write::write_ellipse(const double *c, double major_radius,
                              double minor_radius, double rotation,
                              double start_angle, double end_angle,
                              bool endIsCW) {
  double m[3];
  m[2] = 0;
  m[0] = major_radius * sin(rotation);
  m[1] = major_radius * cos(rotation);

  double ratio = minor_radius / major_radius;

  if (!endIsCW) { // end is NOT CW from start
    double temp = start_angle;
    start_angle = end_angle;
    end_angle = temp;
  }
  _ss_entity << "  0" << std::endl;
  _ss_entity << "ELLIPSE" << std::endl;
  _ss_entity << "  5" << std::endl;
  _ss_entity << get_entity_handle() << std::endl;
  if (_version > 12) {
    _ss_entity << "330" << std::endl;
    _ss_entity << _save_model_space_handle << std::endl;
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbEntity" << std::endl;
  }
  _ss_entity << "  8" << std::endl;            // Group code for layer name
  _ss_entity << get_layer_name() << std::endl; // Layer number
  if (_version > 12) {
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbEllipse" << std::endl;
  }
  _ss_entity << " 10" << std::endl; // Centre X
  _ss_entity << c[0] << std::endl;  // X in WCS coordinates
  _ss_entity << " 20" << std::endl;
  _ss_entity << c[1] << std::endl; // Y in WCS coordinates
  _ss_entity << " 30" << std::endl;
  _ss_entity << c[2] << std::endl;  // Z in WCS coordinates
  _ss_entity << " 11" << std::endl; //
  _ss_entity << m[0] << std::endl;  // Major X
  _ss_entity << " 21" << std::endl;
  _ss_entity << m[1] << std::endl; // Major Y
  _ss_entity << " 31" << std::endl;
  _ss_entity << m[2] << std::endl;  // Major Z
  _ss_entity << " 40" << std::endl; //
  _ss_entity << ratio << std::endl; // Ratio

  _ss_entity << " 41" << std::endl;
  _ss_entity << start_angle << std::endl; // Start angle (radians [0..2pi])
  _ss_entity << " 42" << std::endl;
  _ss_entity << end_angle << std::endl; // End angle
}

void dxf_write::write_spline(const spline_data_out &sd) {
  _ss_entity << "  0" << std::endl;
  _ss_entity << "SPLINE" << std::endl;
  _ss_entity << "  5" << std::endl;
  _ss_entity << get_entity_handle() << std::endl;
  if (_version > 12) {
    _ss_entity << "330" << std::endl;
    _ss_entity << _save_model_space_handle << std::endl;
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbEntity" << std::endl;
  }
  _ss_entity << "  8" << std::endl;            // Group code for layer name
  _ss_entity << get_layer_name() << std::endl; // Layer name
  if (_version > 12) {
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbSpline" << std::endl;
  }
  _ss_entity << "210" << std::endl;
  _ss_entity << "0" << std::endl;
  _ss_entity << "220" << std::endl;
  _ss_entity << "0" << std::endl;
  _ss_entity << "230" << std::endl;
  _ss_entity << "1" << std::endl;

  _ss_entity << " 70" << std::endl;
  _ss_entity << sd.flag << std::endl; // flags
  _ss_entity << " 71" << std::endl;
  _ss_entity << sd.degree << std::endl;
  _ss_entity << " 72" << std::endl;
  _ss_entity << sd.knots << std::endl;
  _ss_entity << " 73" << std::endl;
  _ss_entity << sd.control_points << std::endl;
  _ss_entity << " 74" << std::endl;
  _ss_entity << 0 << std::endl;

  for (auto &k : sd.knot) {
    _ss_entity << " 40" << std::endl;
    _ss_entity << k << std::endl;
  }

  for (auto &w : sd.weight) {
    _ss_entity << " 41" << std::endl;
    _ss_entity << w << std::endl;
  }

  for (auto &c : sd.control) {
    _ss_entity << " 10" << std::endl;
    _ss_entity << c.x << std::endl; // X in WCS coordinates
    _ss_entity << " 20" << std::endl;
    _ss_entity << c.y << std::endl; // Y in WCS coordinates
    _ss_entity << " 30" << std::endl;
    _ss_entity << c.z << std::endl; // Z in WCS coordinates
  }
  for (auto &f : sd.fit) {
    _ss_entity << " 11" << std::endl;
    _ss_entity << f.x << std::endl; // X in WCS coordinates
    _ss_entity << " 21" << std::endl;
    _ss_entity << f.y << std::endl; // Y in WCS coordinates
    _ss_entity << " 31" << std::endl;
    _ss_entity << f.z << std::endl; // Z in WCS coordinates
  }
}

void dxf_write::write_vertex(double x, double y, double z) {
  _ss_entity << "  0" << std::endl;
  _ss_entity << "VERTEX" << std::endl;
  _ss_entity << "  5" << std::endl;
  _ss_entity << get_entity_handle() << std::endl;
  if (_version > 12) {
    _ss_entity << "330" << std::endl;
    _ss_entity << _save_model_space_handle << std::endl;
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbEntity" << std::endl;
  }
  _ss_entity << "  8" << std::endl;
  _ss_entity << get_layer_name() << std::endl;
  if (_version > 12) {
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbVertex" << std::endl;
  }
  _ss_entity << " 10" << std::endl;
  _ss_entity << x << std::endl;
  _ss_entity << " 20" << std::endl;
  _ss_entity << y << std::endl;
  _ss_entity << " 30" << std::endl;
  _ss_entity << z << std::endl;
  _ss_entity << " 70" << std::endl;
  _ss_entity << 0 << std::endl;
}

void dxf_write::write_text(const char *text, const double *location1,
                           const double *location2, const double height,
                           const int horizJust) {
  put_text(text, tovector3d(location1), tovector3d(location2), height,
           horizJust, _ss_entity, get_entity_handle(),
           _save_model_space_handle);
}

void dxf_write::put_text(const char *text, const vector3d &location1,
                         const vector3d &location2, const double height,
                         const int horizJust, std::ostringstream &outStream,
                         const std::string &handle,
                         const std::string &ownerHandle) {
  (void)location2;

  outStream << "  0" << std::endl;
  outStream << "TEXT" << std::endl;
  outStream << "  5" << std::endl;
  outStream << handle << std::endl;
  if (_version > 12) {
    outStream << "330" << std::endl;
    outStream << ownerHandle << std::endl;
    outStream << "100" << std::endl;
    outStream << "AcDbEntity" << std::endl;
  }
  outStream << "  8" << std::endl;
  outStream << get_layer_name() << std::endl;
  if (_version > 12) {
    outStream << "100" << std::endl;
    outStream << "AcDbText" << std::endl;
  }

  outStream << " 10" << std::endl; // first alignment point
  outStream << location1.x << std::endl;
  outStream << " 20" << std::endl;
  outStream << location1.y << std::endl;
  outStream << " 30" << std::endl;
  outStream << location1.z << std::endl;
  outStream << " 40" << std::endl;
  outStream << height << std::endl;
  outStream << "  1" << std::endl;
  outStream << text << std::endl;

  outStream << "  7" << std::endl;
  outStream << "STANDARD" << std::endl; // style

  outStream << " 72" << std::endl;
  outStream << horizJust << std::endl;

  outStream << " 11" << std::endl; // second alignment point
  outStream << location2.x << std::endl;
  outStream << " 21" << std::endl;
  outStream << location2.y << std::endl;
  outStream << " 31" << std::endl;
  outStream << location2.z << std::endl;

  if (_version > 12) {
    outStream << "100" << std::endl;
    outStream << "AcDbText" << std::endl;
  }
}

void dxf_write::put_arrow(const vector3d &arrowPos, const vector3d &barb1Pos,
                          const vector3d &barb2Pos,
                          std::ostringstream &outStream,
                          const std::string &handle,
                          const std::string &ownerHandle) {
  outStream << "  0" << std::endl;
  outStream << "SOLID" << std::endl;
  outStream << "  5" << std::endl;
  outStream << handle << std::endl;
  if (_version > 12) {
    outStream << "330" << std::endl;
    outStream << ownerHandle << std::endl;
    outStream << "100" << std::endl;
    outStream << "AcDbEntity" << std::endl;
  }
  outStream << "  8" << std::endl;
  outStream << "0" << std::endl;
  outStream << " 62" << std::endl;
  outStream << "     0" << std::endl;
  if (_version > 12) {
    outStream << "100" << std::endl;
    outStream << "AcDbTrace" << std::endl;
  }
  outStream << " 10" << std::endl;
  outStream << barb1Pos.x << std::endl;
  outStream << " 20" << std::endl;
  outStream << barb1Pos.y << std::endl;
  outStream << " 30" << std::endl;
  outStream << barb1Pos.z << std::endl;
  outStream << " 11" << std::endl;
  outStream << barb2Pos.x << std::endl;
  outStream << " 21" << std::endl;
  outStream << barb2Pos.y << std::endl;
  outStream << " 31" << std::endl;
  outStream << barb2Pos.z << std::endl;
  outStream << " 12" << std::endl;
  outStream << arrowPos.x << std::endl;
  outStream << " 22" << std::endl;
  outStream << arrowPos.y << std::endl;
  outStream << " 32" << std::endl;
  outStream << arrowPos.z << std::endl;
  outStream << " 13" << std::endl;
  outStream << arrowPos.x << std::endl;
  outStream << " 23" << std::endl;
  outStream << arrowPos.y << std::endl;
  outStream << " 33" << std::endl;
  outStream << arrowPos.z << std::endl;
}

#define ALIGNED 0
#define HORIZONTAL 1
#define VERTICAL 2
void dxf_write::write_linear_dim(const double *textMidPoint,
                                 const double *lineDefPoint,
                                 const double *extLine1, const double *extLine2,
                                 const char *dimText, int type) {
  _ss_entity << "  0" << std::endl;
  _ss_entity << "DIMENSION" << std::endl;
  _ss_entity << "  5" << std::endl;
  _ss_entity << get_entity_handle() << std::endl;
  if (_version > 12) {
    _ss_entity << "330" << std::endl;
    _ss_entity << _save_model_space_handle << std::endl;
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbEntity" << std::endl;
  }
  _ss_entity << "  8" << std::endl;
  _ss_entity << get_layer_name() << std::endl;
  if (_version > 12) {
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbDimension" << std::endl;
  }
  _ss_entity << "  2" << std::endl;
  _ss_entity << "*" << get_layer_name() << std::endl; // block_name
  _ss_entity << " 10" << std::endl; // dimension line definition point
  _ss_entity << lineDefPoint[0] << std::endl;
  _ss_entity << " 20" << std::endl;
  _ss_entity << lineDefPoint[1] << std::endl;
  _ss_entity << " 30" << std::endl;
  _ss_entity << lineDefPoint[2] << std::endl;
  _ss_entity << " 11" << std::endl; // text mid point
  _ss_entity << textMidPoint[0] << std::endl;
  _ss_entity << " 21" << std::endl;
  _ss_entity << textMidPoint[1] << std::endl;
  _ss_entity << " 31" << std::endl;
  _ss_entity << textMidPoint[2] << std::endl;
  if (type == ALIGNED) {
    _ss_entity << " 70" << std::endl;
    _ss_entity << 1 << std::endl; // dimType1 = Aligned
  }
  if ((type == HORIZONTAL) || (type == VERTICAL)) {
    _ss_entity << " 70" << std::endl;
    _ss_entity << 32
               << std::endl; // dimType0 = Aligned + 32 (bit for unique block)?
  }

  _ss_entity << "  1" << std::endl;
  _ss_entity << dimText << std::endl;
  _ss_entity << "  3" << std::endl;
  _ss_entity << "STANDARD" << std::endl; // style
  // linear dims
  if (_version > 12) {
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbAlignedDimension" << std::endl;
  }
  _ss_entity << " 13" << std::endl;
  _ss_entity << extLine1[0] << std::endl;
  _ss_entity << " 23" << std::endl;
  _ss_entity << extLine1[1] << std::endl;
  _ss_entity << " 33" << std::endl;
  _ss_entity << extLine1[2] << std::endl;
  _ss_entity << " 14" << std::endl;
  _ss_entity << extLine2[0] << std::endl;
  _ss_entity << " 24" << std::endl;
  _ss_entity << extLine2[1] << std::endl;
  _ss_entity << " 34" << std::endl;
  _ss_entity << extLine2[2] << std::endl;
  if (_version > 12) {
    if (type == VERTICAL) {
      _ss_entity << " 50" << std::endl;
      _ss_entity << "90" << std::endl;
    }
    if ((type == HORIZONTAL) || (type == VERTICAL)) {
      _ss_entity << "100" << std::endl;
      _ss_entity << "AcDbRotatedDimension" << std::endl;
    }
  }

  write_dim_block_preamble();
  write_linear_dim_block(textMidPoint, lineDefPoint, extLine1, extLine2,
                         dimText, type);
  write_block_trailer();
}

void dxf_write::write_angular_dim(const double *textMidPoint,
                                  const double *lineDefPoint,
                                  const double *startExt1,
                                  const double *endExt1,
                                  const double *startExt2,
                                  const double *endExt2, const char *dimText) {
  _ss_entity << "  0" << std::endl;
  _ss_entity << "DIMENSION" << std::endl;
  _ss_entity << "  5" << std::endl;
  _ss_entity << get_entity_handle() << std::endl;
  if (_version > 12) {
    _ss_entity << "330" << std::endl;
    _ss_entity << _save_model_space_handle << std::endl;
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbEntity" << std::endl;
  }
  _ss_entity << "  8" << std::endl;
  _ss_entity << get_layer_name() << std::endl;
  if (_version > 12) {
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbDimension" << std::endl;
  }
  _ss_entity << "  2" << std::endl;
  _ss_entity << "*" << get_layer_name() << std::endl; // block_name

  _ss_entity << " 10" << std::endl;
  _ss_entity << endExt2[0] << std::endl;
  _ss_entity << " 20" << std::endl;
  _ss_entity << endExt2[1] << std::endl;
  _ss_entity << " 30" << std::endl;
  _ss_entity << endExt2[2] << std::endl;

  _ss_entity << " 11" << std::endl;
  _ss_entity << textMidPoint[0] << std::endl;
  _ss_entity << " 21" << std::endl;
  _ss_entity << textMidPoint[1] << std::endl;
  _ss_entity << " 31" << std::endl;
  _ss_entity << textMidPoint[2] << std::endl;

  _ss_entity << " 70" << std::endl;
  _ss_entity << 2 << std::endl;

  _ss_entity << "  1" << std::endl;
  _ss_entity << dimText << std::endl;
  _ss_entity << "  3" << std::endl;
  _ss_entity << "STANDARD" << std::endl; // style
  // angular dims
  if (_version > 12) {
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDb2LineAngularDimension" << std::endl;
  }
  _ss_entity << " 13" << std::endl;
  _ss_entity << startExt1[0] << std::endl;
  _ss_entity << " 23" << std::endl;
  _ss_entity << startExt1[1] << std::endl;
  _ss_entity << " 33" << std::endl;
  _ss_entity << startExt1[2] << std::endl;

  _ss_entity << " 14" << std::endl;
  _ss_entity << endExt1[0] << std::endl;
  _ss_entity << " 24" << std::endl;
  _ss_entity << endExt1[1] << std::endl;
  _ss_entity << " 34" << std::endl;
  _ss_entity << endExt1[2] << std::endl;

  _ss_entity << " 15" << std::endl;
  _ss_entity << startExt2[0] << std::endl;
  _ss_entity << " 25" << std::endl;
  _ss_entity << startExt2[1] << std::endl;
  _ss_entity << " 35" << std::endl;
  _ss_entity << startExt2[2] << std::endl;

  _ss_entity << " 16" << std::endl;
  _ss_entity << lineDefPoint[0] << std::endl;
  _ss_entity << " 26" << std::endl;
  _ss_entity << lineDefPoint[1] << std::endl;
  _ss_entity << " 36" << std::endl;
  _ss_entity << lineDefPoint[2] << std::endl;
  write_dim_block_preamble();
  write_angular_dim_block(textMidPoint, lineDefPoint, startExt1, endExt1,
                          startExt2, endExt2, dimText);
  write_block_trailer();
}

void dxf_write::write_radial_dim(const double *centerPoint,
                                 const double *textMidPoint,
                                 const double *arcPoint, const char *dimText) {
  _ss_entity << "  0" << std::endl;
  _ss_entity << "DIMENSION" << std::endl;
  _ss_entity << "  5" << std::endl;
  _ss_entity << get_entity_handle() << std::endl;
  if (_version > 12) {
    _ss_entity << "330" << std::endl;
    _ss_entity << _save_model_space_handle << std::endl;
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbEntity" << std::endl;
  }
  _ss_entity << "  8" << std::endl;
  _ss_entity << get_layer_name() << std::endl;
  if (_version > 12) {
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbDimension" << std::endl;
  }
  _ss_entity << "  2" << std::endl;
  _ss_entity << "*" << get_layer_name() << std::endl; // block_name
  _ss_entity << " 10" << std::endl;                   // arc center point
  _ss_entity << centerPoint[0] << std::endl;
  _ss_entity << " 20" << std::endl;
  _ss_entity << centerPoint[1] << std::endl;
  _ss_entity << " 30" << std::endl;
  _ss_entity << centerPoint[2] << std::endl;
  _ss_entity << " 11" << std::endl; // text mid point
  _ss_entity << textMidPoint[0] << std::endl;
  _ss_entity << " 21" << std::endl;
  _ss_entity << textMidPoint[1] << std::endl;
  _ss_entity << " 31" << std::endl;
  _ss_entity << textMidPoint[2] << std::endl;
  _ss_entity << " 70" << std::endl;
  _ss_entity << 4 << std::endl; // dimType 4 = Radius

  _ss_entity << "  1" << std::endl;
  _ss_entity << dimText << std::endl;
  _ss_entity << "  3" << std::endl;
  _ss_entity << "STANDARD" << std::endl; // style
  // radial dims
  if (_version > 12) {
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbRadialDimension" << std::endl;
  }
  _ss_entity << " 15" << std::endl;
  _ss_entity << arcPoint[0] << std::endl;
  _ss_entity << " 25" << std::endl;
  _ss_entity << arcPoint[1] << std::endl;
  _ss_entity << " 35" << std::endl;
  _ss_entity << arcPoint[2] << std::endl;
  _ss_entity << " 40" << std::endl; // leader length????
  _ss_entity << 0 << std::endl;

  write_dim_block_preamble();
  write_radial_dim_block(centerPoint, textMidPoint, arcPoint, dimText);
  write_block_trailer();
}

void dxf_write::write_diametric_dim(const double *textMidPoint,
                                    const double *arcPoint1,
                                    const double *arcPoint2,
                                    const char *dimText) {
  _ss_entity << "  0" << std::endl;
  _ss_entity << "DIMENSION" << std::endl;
  _ss_entity << "  5" << std::endl;
  _ss_entity << get_entity_handle() << std::endl;
  if (_version > 12) {
    _ss_entity << "330" << std::endl;
    _ss_entity << _save_model_space_handle << std::endl;
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbEntity" << std::endl;
  }
  _ss_entity << "  8" << std::endl;
  _ss_entity << get_layer_name() << std::endl;
  if (_version > 12) {
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbDimension" << std::endl;
  }
  _ss_entity << "  2" << std::endl;
  _ss_entity << "*" << get_layer_name() << std::endl; // block_name
  _ss_entity << " 10" << std::endl;
  _ss_entity << arcPoint1[0] << std::endl;
  _ss_entity << " 20" << std::endl;
  _ss_entity << arcPoint1[1] << std::endl;
  _ss_entity << " 30" << std::endl;
  _ss_entity << arcPoint1[2] << std::endl;
  _ss_entity << " 11" << std::endl; // text mid point
  _ss_entity << textMidPoint[0] << std::endl;
  _ss_entity << " 21" << std::endl;
  _ss_entity << textMidPoint[1] << std::endl;
  _ss_entity << " 31" << std::endl;
  _ss_entity << textMidPoint[2] << std::endl;
  _ss_entity << " 70" << std::endl;
  _ss_entity << 3 << std::endl; // dimType 3 = Diameter

  _ss_entity << "  1" << std::endl;
  _ss_entity << dimText << std::endl;
  _ss_entity << "  3" << std::endl;
  _ss_entity << "STANDARD" << std::endl; // style
  // diametric dims
  if (_version > 12) {
    _ss_entity << "100" << std::endl;
    _ss_entity << "AcDbDiametricDimension" << std::endl;
  }
  _ss_entity << " 15" << std::endl;
  _ss_entity << arcPoint2[0] << std::endl;
  _ss_entity << " 25" << std::endl;
  _ss_entity << arcPoint2[1] << std::endl;
  _ss_entity << " 35" << std::endl;
  _ss_entity << arcPoint2[2] << std::endl;
  _ss_entity << " 40" << std::endl; // leader length????
  _ss_entity << 0 << std::endl;

  write_dim_block_preamble();
  write_diametric_dim_block(textMidPoint, arcPoint1, arcPoint2, dimText);
  write_block_trailer();
}

void dxf_write::write_dim_block_preamble() {
  if (_version > 12) {
    std::string block_name("*");
    block_name += get_layer_name();
    _save_blk_record_handle = get_blk_record_handle();
    add_block_name(block_name, _save_blk_record_handle);
  }

  _current_block = get_block_handle();
  _ss_block << "  0" << std::endl;
  _ss_block << "BLOCK" << std::endl;
  _ss_block << "  5" << std::endl;
  _ss_block << _current_block << std::endl;
  if (_version > 12) {
    _ss_block << "330" << std::endl;
    _ss_block << _save_blk_record_handle << std::endl;
    _ss_block << "100" << std::endl;
    _ss_block << "AcDbEntity" << std::endl;
  }
  _ss_block << "  8" << std::endl;
  _ss_block << get_layer_name() << std::endl;
  if (_version > 12) {
    _ss_block << "100" << std::endl;
    _ss_block << "AcDbBlockBegin" << std::endl;
  }
  _ss_block << "  2" << std::endl;
  _ss_block << "*" << get_layer_name() << std::endl; // block_name
  _ss_block << " 70" << std::endl;
  _ss_block << "   1" << std::endl;
  _ss_block << " 10" << std::endl;
  _ss_block << 0.0 << std::endl;
  _ss_block << " 20" << std::endl;
  _ss_block << 0.0 << std::endl;
  _ss_block << " 30" << std::endl;
  _ss_block << 0.0 << std::endl;
  _ss_block << "  3" << std::endl;
  _ss_block << "*" << get_layer_name() << std::endl; // block_name
  _ss_block << "  1" << std::endl;
  _ss_block << " " << std::endl;
}

void dxf_write::write_block_trailer() {
  _ss_block << "  0" << std::endl;
  _ss_block << "ENDBLK" << std::endl;
  _ss_block << "  5" << std::endl;
  _ss_block << get_block_handle() << std::endl;
  if (_version > 12) {
    _ss_block << "330" << std::endl;
    _ss_block << _save_blk_record_handle << std::endl;
    _ss_block << "100" << std::endl;
    _ss_block << "AcDbEntity" << std::endl;
  }
  _ss_block << "  8" << std::endl;
  _ss_block << get_layer_name() << std::endl;
  if (_version > 12) {
    _ss_block << "100" << std::endl;
    _ss_block << "AcDbBlockEnd" << std::endl;
  }
}

void dxf_write::write_linear_dim_block(const double *textMidPoint,
                                       const double *dimLine,
                                       const double *e1Start,
                                       const double *e2Start,
                                       const char *dimText, int type) {
  vector3d e1S(e1Start[0], e1Start[1], e1Start[2]);
  vector3d e2S(e2Start[0], e2Start[1], e2Start[2]);
  vector3d dl(dimLine[0], dimLine[1], dimLine[2]);
  vector3d perp = dl.distance_to_line_segment(e2S, e1S);
  vector3d e1E = e1S - perp;
  vector3d e2E = e2S - perp;
  vector3d para = e1E - e2E;
  vector3d X(1.0, 0.0, 0.0);
  double angle = para.get_angle(X);
  angle = angle * 180.0 / M_PI;
  if (type == ALIGNED) {
    // NOP
  } else if (type == HORIZONTAL) {
    double x = e1Start[0];
    double y = dimLine[1];
    e1E = vector3d(x, y, 0.0);
    x = e2Start[0];
    e2E = vector3d(x, y, 0.0);
    perp = vector3d(0, -1, 0); // down
    para = vector3d(1, 0, 0);  // right
    if (dimLine[1] > e1Start[1]) {
      perp = vector3d(0, 1, 0); // up
    }
    if (e1Start[0] > e2Start[0]) {
      para = vector3d(-1, 0, 0); // left
    }
    angle = 0;
  } else if (type == VERTICAL) {
    double x = dimLine[0];
    double y = e1Start[1];
    e1E = vector3d(x, y, 0.0);
    y = e2Start[1];
    e2E = vector3d(x, y, 0.0);
    perp = vector3d(1, 0, 0);
    para = vector3d(0, 1, 0);
    if (dimLine[0] < e1Start[0]) {
      perp = vector3d(-1, 0, 0);
    }
    if (e1Start[1] > e2Start[1]) {
      para = vector3d(0, -1, 0);
    }
    angle = 90;
  }

  double arrowLen = 5.0;                    // magic number
  double arrowWidth = arrowLen / 6.0 / 2.0; // magic number calc!

  put_line(e2S, e2E, _ss_block, get_block_handle(), _save_blk_record_handle);

  put_line(e1S, e1E, _ss_block, get_block_handle(), _save_blk_record_handle);

  put_line(e1E, e2E, _ss_block, get_block_handle(), _save_blk_record_handle);

  put_text(dimText, tovector3d(textMidPoint), tovector3d(dimLine), 3.5, 1,
           _ss_block, get_block_handle(), _save_blk_record_handle);

  perp.normalize();
  para.normalize();
  vector3d arrowStart = e1E;
  vector3d barb1 = arrowStart + perp * arrowWidth - para * arrowLen;
  vector3d barb2 = arrowStart - perp * arrowWidth - para * arrowLen;
  put_arrow(arrowStart, barb1, barb2, _ss_block, get_block_handle(),
            _save_blk_record_handle);

  arrowStart = e2E;
  barb1 = arrowStart + perp * arrowWidth + para * arrowLen;
  barb2 = arrowStart - perp * arrowWidth + para * arrowLen;
  put_arrow(arrowStart, barb1, barb2, _ss_block, get_block_handle(),
            _save_blk_record_handle);
}

void dxf_write::write_angular_dim_block(
    const double *textMidPoint, const double *lineDefPoint,
    const double *startExt1, const double *endExt1, const double *startExt2,
    const double *endExt2, const char *dimText) {
  vector3d e1S(startExt1[0], startExt1[1], startExt1[2]); // apex
  vector3d e2S(startExt2[0], startExt2[1], startExt2[2]);
  vector3d e1E(endExt1[0], endExt1[1], endExt1[2]);
  vector3d e2E(endExt2[0], endExt2[1], endExt2[2]);
  vector3d e1 = e1E - e1S;
  vector3d e2 = e2E - e2S;

  double startAngle = atan2(e2.y, e2.x);
  double endAngle = atan2(e1.y, e1.x);
  double span = fabs(endAngle - startAngle);
  double offset = span * 0.10;
  if (startAngle < 0) {
    startAngle += 2.0 * M_PI;
  }
  if (endAngle < 0) {
    endAngle += 2.0 * M_PI;
  }
  vector3d startOff(cos(startAngle + offset), sin(startAngle + offset), 0.0);
  vector3d endOff(cos(endAngle - offset), sin(endAngle - offset), 0.0);
  startAngle = startAngle * 180.0 / M_PI;
  endAngle = endAngle * 180.0 / M_PI;

  vector3d linePt(lineDefPoint[0], lineDefPoint[1], lineDefPoint[2]);
  double radius = (e2S - linePt).length();

  _ss_block << "  0" << std::endl;
  _ss_block << "ARC" << std::endl; // dimline arc
  _ss_block << "  5" << std::endl;
  _ss_block << get_block_handle() << std::endl;
  if (_version > 12) {
    _ss_block << "330" << std::endl;
    _ss_block << _save_blk_record_handle << std::endl;
    _ss_block << "100" << std::endl;
    _ss_block << "AcDbEntity" << std::endl;
  }
  _ss_block << "  8" << std::endl;
  _ss_block << "0" << std::endl;

  if (_version > 12) {
    _ss_block << "100" << std::endl;
    _ss_block << "AcDbCircle" << std::endl;
  }
  _ss_block << " 10" << std::endl;
  _ss_block << startExt2[0] << std::endl; // arc center
  _ss_block << " 20" << std::endl;
  _ss_block << startExt2[1] << std::endl;
  _ss_block << " 30" << std::endl;
  _ss_block << startExt2[2] << std::endl;
  _ss_block << " 40" << std::endl;
  _ss_block << radius << std::endl; // radius
  if (_version > 12) {
    _ss_block << "100" << std::endl;
    _ss_block << "AcDbArc" << std::endl;
  }
  _ss_block << " 50" << std::endl;
  _ss_block << startAngle << std::endl; // start angle
  _ss_block << " 51" << std::endl;
  _ss_block << endAngle << std::endl; // end angle

  put_text(dimText, tovector3d(textMidPoint), tovector3d(textMidPoint), 3.5, 1,
           _ss_block, get_block_handle(), _save_blk_record_handle);

  e1.normalize();
  e2.normalize();
  vector3d arrow1Start = e1S + e1 * radius;
  vector3d arrow2Start = e2S + e2 * radius;

  vector3d endTan = e1S + (startOff * radius);
  vector3d startTan = e2S + (endOff * radius);
  vector3d tanP1 = (arrow1Start - startTan).normalize();
  vector3d perp1(-tanP1.y, tanP1.x, tanP1.z);
  vector3d tanP2 = (arrow2Start - endTan).normalize();
  vector3d perp2(-tanP2.y, tanP2.x, tanP2.z);
  double arrowLen = 5.0;                    // magic number
  double arrowWidth = arrowLen / 6.0 / 2.0; // magic number calc!

  vector3d barb1 = arrow1Start + perp1 * arrowWidth - tanP1 * arrowLen;
  vector3d barb2 = arrow1Start - perp1 * arrowWidth - tanP1 * arrowLen;

  put_arrow(arrow1Start, barb1, barb2, _ss_block, get_block_handle(),
            _save_blk_record_handle);

  barb1 = arrow2Start + perp2 * arrowWidth - tanP2 * arrowLen;
  barb2 = arrow2Start - perp2 * arrowWidth - tanP2 * arrowLen;

  put_arrow(arrow2Start, barb1, barb2, _ss_block, get_block_handle(),
            _save_blk_record_handle);
}

void dxf_write::write_radial_dim_block(const double *centerPoint,
                                       const double *textMidPoint,
                                       const double *arcPoint,
                                       const char *dimText) {
  put_line(tovector3d(centerPoint), tovector3d(arcPoint), _ss_block,
           get_block_handle(), _save_blk_record_handle);

  put_text(dimText, tovector3d(textMidPoint), tovector3d(textMidPoint), 3.5, 1,
           _ss_block, get_block_handle(), _save_blk_record_handle);

  vector3d c(centerPoint[0], centerPoint[1], centerPoint[2]);
  vector3d a(arcPoint[0], arcPoint[1], arcPoint[2]);
  vector3d para = a - c;
  double arrowLen = 5.0;                    // magic number
  double arrowWidth = arrowLen / 6.0 / 2.0; // magic number calc!
  para.normalize();
  vector3d perp(-para.y, para.x, para.z);
  vector3d arrowStart = a;
  vector3d barb1 = arrowStart + perp * arrowWidth - para * arrowLen;
  vector3d barb2 = arrowStart - perp * arrowWidth - para * arrowLen;

  put_arrow(arrowStart, barb1, barb2, _ss_block, get_block_handle(),
            _save_blk_record_handle);
}

void dxf_write::write_diametric_dim_block(const double *textMidPoint,
                                          const double *arcPoint1,
                                          const double *arcPoint2,
                                          const char *dimText) {
  put_line(tovector3d(arcPoint1), tovector3d(arcPoint2), _ss_block,
           get_block_handle(), _save_blk_record_handle);

  put_text(dimText, tovector3d(textMidPoint), tovector3d(textMidPoint), 3.5, 1,
           _ss_block, get_block_handle(), _save_blk_record_handle);

  vector3d a1(arcPoint1[0], arcPoint1[1], arcPoint1[2]);
  vector3d a2(arcPoint2[0], arcPoint2[1], arcPoint2[2]);
  vector3d para = a2 - a1;
  double arrowLen = 5.0;                    // magic number
  double arrowWidth = arrowLen / 6.0 / 2.0; // magic number calc!
  para.normalize();
  vector3d perp(-para.y, para.x, para.z);
  vector3d arrowStart = a1;
  vector3d barb1 = arrowStart + perp * arrowWidth + para * arrowLen;
  vector3d barb2 = arrowStart - perp * arrowWidth + para * arrowLen;

  put_arrow(arrowStart, barb1, barb2, _ss_block, get_block_handle(),
            _save_blk_record_handle);

  arrowStart = a2;
  barb1 = arrowStart + perp * arrowWidth - para * arrowLen;
  barb2 = arrowStart - perp * arrowWidth - para * arrowLen;
  put_arrow(arrowStart, barb1, barb2, _ss_block, get_block_handle(),
            _save_blk_record_handle);
}

void dxf_write::write_blocks_section() {
  if (_version < 14) {
    std::stringstream ss;
    ss << "blocks1" << _version << ".rub";
    std::string fileSpec = _data_dir + ss.str();
    _ofs << get_plate_file(fileSpec);
  }

  // write blocks content
  _ofs << _ss_block.str();

  _ofs << "  0" << std::endl;
  _ofs << "ENDSEC" << std::endl;
}

void dxf_write::write_entities_section() {
  std::stringstream ss;
  ss << "entities" << _version << ".rub";
  std::string fileSpec = _data_dir + ss.str();
  _ofs << get_plate_file(fileSpec);

  // write entities content
  _ofs << _ss_entity.str();

  _ofs << "  0" << std::endl;
  _ofs << "ENDSEC" << std::endl;
}

void dxf_write::write_objects_section() {
  if (_version < 14) {
    return;
  }
  std::stringstream ss;
  ss << "objects" << _version << ".rub";
  std::string fileSpec = _data_dir + ss.str();
  _ofs << get_plate_file(fileSpec);
}

dxf_read::dxf_read(const char *filepath) : _ifs(filepath) {
  if (!_ifs)
    _fail = true;
  else
    _ifs.imbue(std::locale::classic());
}

dxf_read::~dxf_read() {}

double dxf_read::mm(double value) const {
  if (_measurement_inch && (_units == eMillimeters)) {
    value *= 25.4;
  }

  switch (_units) {
  case eUnspecified:
    return (value * 1.0);
  case eInches:
    return (value * 25.4);
  case eFeet:
    return (value * 25.4 * 12);
  case eMiles:
    return (value * 1609344.0);
  case eMillimeters:
    return (value * 1.0);
  case eCentimeters:
    return (value * 10.0);
  case eMeters:
    return (value * 1000.0);
  case eKilometers:
    return (value * 1000000.0);
  case eMicroinches:
    return (value * 25.4 / 1000.0);
  case eMils:
    return (value * 25.4 / 1000.0);
  case eYards:
    return (value * 3 * 12 * 25.4);
  case eAngstroms:
    return (value * 0.0000001);
  case eNanometers:
    return (value * 0.000001);
  case eMicrons:
    return (value * 0.001);
  case eDecimeters:
    return (value * 100.0);
  case eDekameters:
    return (value * 10000.0);
  case eHectometers:
    return (value * 100000.0);
  case eGigameters:
    return (value * 1000000000000.0);
  case eAstronomicalUnits:
    return (value * 149597870690000.0);
  case eLightYears:
    return (value * 9454254955500000000.0);
  case eParsecs:
    return (value * 30856774879000000000.0);
  default:
    return (value * 1.0);
  }
}

const dxf_style *dxf_read::find_style(const std::string &name) const {
  if (name.empty())
    return nullptr;

  auto itFound = _map_style.find(name);
  return itFound != _map_style.cend() ? &itFound->second : nullptr;
}

bool dxf_read::read_line() {
  dxf_coords s = {};
  dxf_coords e = {};
  bool hidden = false;

  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (n == 0) {
      resolve_color_index();
      on_read_line(s, e, hidden);
      return true;
    } else if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_line()");
      return false;
    }

    get_line();
    switch (n) {
    case 6:
      if (!_str.empty() && (_str[0] == 'h' || _str[0] == 'H')) {
        hidden = true;
      }
      break;
    case 10:
    case 20:
    case 30:
      handle_coord_code(n, &s);
      break;
    case 11:
    case 21:
    case 31:
      handle_coord_code<11, 21, 31>(n, &e);
      break;
    case 100:
    case 39:
    case 210:
    case 220:
    case 230:
      break;
    default:
      handle_common_group_code(n);
      break;
    }
  }

  try {
    resolve_color_index();
    on_read_line(s, e, false);
  } catch (...) {
    if (!ignore_errors()) {
      throw;
    }
  }

  return false;
}

bool dxf_read::read_point() {
  dxf_coords s = {};

  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (n == 0) {
      resolve_color_index();
      on_read_point(s);
      return true;
    } else if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_point()");
      return false;
    }

    get_line();
    switch (n) {
    case 10:
    case 20:
    case 30:
      handle_coord_code(n, &s);
      break;

    case 100:
    case 39:
    case 210:
    case 220:
    case 230:
      break;
    default:
      handle_common_group_code(n);
      break;
    }
  }

  try {
    resolve_color_index();
    on_read_point(s);
  } catch (...) {
    if (!ignore_errors()) {
      throw;
    }
  }

  return false;
}

bool dxf_read::read_arc() {
  double start_angle = 0.0;
  double end_angle = 0.0;
  double radius = 0.0;
  dxf_coords c = {};
  double z_extrusion_dir = 1.0;
  bool hidden = false;

  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (n == 0) {
      resolve_color_index();
      on_read_arc(start_angle, end_angle, radius, c, z_extrusion_dir, hidden);
      hidden = false;
      return true;
    } else if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_arc()");
      return false;
    }

    get_line();
    switch (n) {
    case 6:
      if (!_str.empty() && (_str[0] == 'h' || _str[0] == 'H')) {
        hidden = true;
      }
      break;

    case 10:
    case 20:
    case 30:
      handle_coord_code(n, &c);
      break;
    case 40:
      radius = mm(string_to_double(_str));
      break;
    case 50:
      start_angle = mm(string_to_double(_str));
      break;
    case 51:
      end_angle = mm(string_to_double(_str));
      break;

    case 100:
    case 39:
    case 210:
    case 220:
      break;
    case 230:
      z_extrusion_dir = mm(string_to_double(_str));
      break;

    default:
      handle_common_group_code(n);
      break;
    }
  }

  resolve_color_index();
  on_read_arc(start_angle, end_angle, radius, c, z_extrusion_dir, false);
  return false;
}

bool dxf_read::read_spline() {
  dxf_spline spline;
  int knotCount = 0;
  int controlpoint_count = 0;
  int fitpoint_count = 0;

  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (n == 0) {
      resolve_color_index();
      on_read_spline(spline);
      return true;
    } else if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_spline()");
      return false;
    }

    get_line();
    switch (n) {
    case 210:
    case 220:
    case 230:
      handle_coord_code<210, 220, 230>(n, &spline.normal_vector);
      break;
    case 70:
      spline.flags = string_to_unsigned(_str);
      break;
    case 71:
      spline.degree = string_to_int(_str);
      break;
    case 72:
      knotCount = string_to_int(_str);
      spline.knots.reserve(knotCount);
      break;
    case 73:
      controlpoint_count = string_to_int(_str);
      spline.control_points.reserve(controlpoint_count);
      break;
    case 74:
      fitpoint_count = string_to_int(_str);
      spline.fit_points.reserve(fitpoint_count);
      break;
    case 12:
    case 22:
    case 32:
      handle_vector_coord_code<12, 22, 32>(n, &spline.start_tangents);
      break;
    case 13:
    case 23:
    case 33:
      handle_vector_coord_code<13, 23, 33>(n, &spline.end_tangents);
      break;
    case 40:
      spline.knots.push_back(mm(string_to_double(_str)));
      break;
    case 41:
      spline.weights.push_back(mm(string_to_double(_str)));
      break;
    case 10:
    case 20:
    case 30:
      handle_vector_coord_code<10, 20, 30>(n, &spline.control_points);
      break;
    case 11:
    case 21:
    case 31:
      handle_vector_coord_code<11, 21, 31>(n, &spline.fit_points);
      break;
    case 42:
      spline.knot_tolerance = string_to_double(_str);
      break;
    case 43:
      spline.control_point_tolerance = string_to_double(_str);
      break;
    case 44:
      spline.fit_tolerance = string_to_double(_str);
      break;
    default:
      handle_common_group_code(n);
      break;
    }
  }

  resolve_color_index();
  on_read_spline(spline);
  return false;
}

bool dxf_read::read_circle() {
  double radius = 0.0;
  dxf_coords c = {}; // centre
  bool hidden = false;

  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (n == 0) {
      resolve_color_index();
      on_read_circle(c, radius, hidden);
      return true;
    } else if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_circle()");
      return false;
    }

    get_line();
    switch (n) {
    case 6: // line style name follows
      if (!_str.empty() && (_str[0] == 'h' || _str[0] == 'H')) {
        hidden = true;
      }
      break;
    case 10:
    case 20:
    case 30:
      // centre coords
      handle_coord_code(n, &c);
      break;
    case 40:
      // radius
      radius = mm(string_to_double(_str));
      break;

    case 100:
    case 39:
    case 210:
    case 220:
    case 230:
      // skip the next line
      break;
    default:
      handle_common_group_code(n);
      break;
    }
  }

  resolve_color_index();
  on_read_circle(c, radius, false);
  return false;
}

bool dxf_read::read_mtext() {
  dxf_mtext text;
  bool withinAcadColumnInfo = false;
  bool withinAcadColumns = false;
  bool withinAcadDefinedHeight = false;

  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (n == 0) {
      resolve_color_index();
      // Replace \P by \n
      size_t pos = text.str.find("\\P", 0);
      while (pos != std::string::npos) {
        text.str.replace(pos, 2, "\n");
        pos = text.str.find("\\P", pos + 1);
      }

      text.str = this->to_utf8(text.str);
      on_read_mtext(text);
      return true;
    }

    get_line();

    auto fnMatchExtensionBegin = [=](const std::string &extName, bool &tag) {
      if (!tag && _str == extName) {
        tag = true;
        return true;
      }
      return false;
    };

    auto fnMatchExtensionEnd = [=](const std::string &extName, bool &tag) {
      if (tag && _str == extName) {
        tag = false;
        return true;
      }
      return false;
    };

    if (fnMatchExtensionBegin("ACAD_MTEXT_COLUMN_INFO_BEGIN",
                              withinAcadColumnInfo)) {
      text.acad_has_column_info = true;
      continue; // Skip
    }

    if (fnMatchExtensionEnd("ACAD_MTEXT_COLUMN_INFO_END", withinAcadColumnInfo))
      continue; // Skip

    if (fnMatchExtensionBegin("ACAD_MTEXT_COLUMNS_BEGIN", withinAcadColumns))
      continue; // Skip

    if (fnMatchExtensionEnd("ACAD_MTEXT_COLUMNS_END", withinAcadColumns))
      continue; // Skip

    if (fnMatchExtensionBegin("ACAD_MTEXT_DEFINED_HEIGHT_BEGIN",
                              withinAcadDefinedHeight)) {
      text.acad_has_defined_height = true;
      continue; // Skip
    }

    if (fnMatchExtensionEnd("ACAD_MTEXT_DEFINED_HEIGHT_END",
                            withinAcadDefinedHeight))
      continue; // Skip

    if (withinAcadColumnInfo) {
      // 1040/1070 extended data code was found at beginning of current
      // iteration
      const int xn =
          string_to_int(_str, string_to_error_mode::ReturnErrorValue);
      get_line(); // Skip 1040/1070 line
      get_line(); // Get value line of extended data code
      switch (xn) {
      case 75: { // 1070
        const int t = string_to_int(_str);
        if (0 <= t && t <= 2)
          text.acad_column_info_type = static_cast<dxf_mtext::column_type>(t);
      } break;
      case 76: // 1070
        text.acad_column_info_count = string_to_int(_str);
        break;
      case 78: // 1070
        text.acad_column_info_flow_reversed = string_to_int(_str) != 0;
        break;
      case 79: // 1070
        text.acad_column_info_auto_height = string_to_int(_str) != 0;
        break;
      case 48: // 1040
        text.acad_column_info_width = mm(string_to_double(_str));
        break;
      case 49: // 1040
        text.acad_column_info_gutter_width = mm(string_to_double(_str));
        break;
      } // endswitch

      continue; // Skip
    }

    if (withinAcadDefinedHeight) {
      // 1040/1070 extended data code was found at beginning of current
      // iteration
      const int xn =
          string_to_int(_str, string_to_error_mode::ReturnErrorValue);
      get_line(); // Skip 1040/1070 line
      get_line(); // Get value line of extended data code
      if (xn == 46)
        text.acad_defined_height = mm(string_to_double(_str));

      continue; // Skip
    }

    switch (n) {
    case 10:
    case 20:
    case 30:
      // centre coords
      handle_coord_code(n, &text.insertion_point);
      break;
    case 40:
      // text height
      text.height = mm(string_to_double(_str));
      break;
    case 50:
      // text rotation
      text.rotation_angle = string_to_double(_str);
      break;
    case 3:
      text.str.append(_str);
      break;
    case 1:
      // final text
      text.str.append(_str);
      break;

    case 71: {
      // attachment point
      const int ap = string_to_int(_str);
      if (ap >= 1 && ap <= 9)
        text.attachment_point =
            static_cast<dxf_mtext::attachment_point_type>(ap);
    } break;

    case 11:
    case 21:
    case 31:
      // X-axis direction vector
      handle_coord_code<11, 21, 31>(n, &text.x_axis_direction);
      break;

    case 210:
    case 220:
    case 230:
      // extrusion direction
      handle_coord_code<210, 220, 230>(n, &text.extrusion_direction);
      break;

    default:
      handle_common_group_code(n);
      break;
    }
  }

  return false;
}

bool dxf_read::read_text() {
  dxf_text text;

  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (n == 0) {
      resolve_color_index();
      on_read_text(text);
      return true;
    }

    get_line();
    switch (n) {
    case 10:
    case 20:
    case 30:
      handle_coord_code(n, &text.first_alignment_point);
      break;
    case 40:
      text.height = mm(string_to_double(_str));
      break;
    case 1:
      text.str = this->to_utf8(_str);
      break;
    case 50:
      text.rotation_angle = string_to_double(_str);
      break;
    case 41:
      text.relative_x_scale_factor_width = string_to_double(_str);
      break;
    case 51:
      text.oblique_angle = string_to_double(_str);
      break;
    case 7:
      text.style_name = _str;
      break;
    case 72: {
      const int hjust = string_to_int(_str);
      if (hjust >= 0 && hjust <= 5)
        text.horizontal_justification =
            static_cast<dxf_text::horizontal_justification_type>(hjust);
    } break;
    case 11:
    case 21:
    case 31:
      handle_coord_code<11, 21, 31>(n, &text.second_alignment_point);
      break;
    case 210:
    case 220:
    case 230:
      handle_coord_code<210, 220, 230>(n, &text.extrusion_direction);
      break;
    case 73: {
      const int vjust = string_to_int(_str);
      if (vjust >= 0 && vjust <= 3)
        text.vertical_justification =
            static_cast<dxf_text::vertical_justification_type>(vjust);
    } break;
    default:
      handle_common_group_code(n);
      break;
    }
  }

  return false;
}

bool dxf_read::read_ellipse() {
  dxf_coords c = {}; // centre
  dxf_coords m = {}; // major axis point
  double ratio = 0;  // ratio of major to minor axis
  double start = 0;  // start of arc
  double end = 0;    // end of arc

  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (n == 0) {
      // next item found, so finish with Ellipse
      resolve_color_index();
      on_read_ellipse(c, m, ratio, start, end);
      return true;
    } else if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_ellipse()");
      return false;
    }

    get_line();
    switch (n) {
    case 10:
    case 20:
    case 30:
      // centre coords
      handle_coord_code(n, &c);
      break;
    case 11:
    case 21:
    case 31:
      // major coords
      handle_coord_code<11, 21, 31>(n, &m);
      break;
    case 40:
      // ratio
      ratio = string_to_double(_str);
      break;
    case 41:
      // start
      start = string_to_double(_str);
      break;
    case 42:
      // end
      end = string_to_double(_str);
      break;
    case 100:
    case 210:
    case 220:
    case 230:
      // skip the next line
      break;
    default:
      handle_common_group_code(n);
      break;
    }
  }

  resolve_color_index();
  on_read_ellipse(c, m, ratio, start, end);
  return false;
}

// TODO Remove this(refactoring of dxf_read::read_lw_polyline()
static bool poly_prev_found = false;
static double poly_prev_x;
static double poly_prev_y;
static double poly_prev_z;
static bool poly_prev_bulge_found = false;
static double poly_prev_bulge;
static bool poly_first_found = false;
static double poly_first_x;
static double poly_first_y;
static double poly_first_z;

// TODO Remove this(refactoring of dxf_read::read_lw_polyline()
static void add_polyline_point(dxf_read *dxf_read, double x, double y, double z,
                               bool bulge_found, double bulge) {

  try {
    if (poly_prev_found) {
      bool arc_done = false;
      if (poly_prev_bulge_found) {
        double cot = 0.5 * ((1.0 / poly_prev_bulge) - poly_prev_bulge);
        double cx = ((poly_prev_x + x) - ((y - poly_prev_y) * cot)) / 2.0;
        double cy = ((poly_prev_y + y) + ((x - poly_prev_x) * cot)) / 2.0;
        const dxf_coords ps = {poly_prev_x, poly_prev_y, poly_prev_z};
        const dxf_coords pe = {x, y, z};
        const dxf_coords pc = {cx, cy, (poly_prev_z + z) / 2.0};
        dxf_read->on_read_arc(ps, pe, pc, poly_prev_bulge >= 0, false);
        arc_done = true;
      }

      if (!arc_done) {
        const dxf_coords s = {poly_prev_x, poly_prev_y, poly_prev_z};
        const dxf_coords e = {x, y, z};
        dxf_read->on_read_line(s, e, false);
      }
    }

    poly_prev_found = true;
    poly_prev_x = x;
    poly_prev_y = y;
    poly_prev_z = z;
    if (!poly_first_found) {
      poly_first_x = x;
      poly_first_y = y;
      poly_first_z = z;
      poly_first_found = true;
    }
    poly_prev_bulge_found = bulge_found;
    poly_prev_bulge = bulge;
  } catch (...) {
    if (!dxf_read->ignore_errors()) {
      throw; // Re-throw it.
    }
  }
}

// TODO Remove this(refactoring of dxf_read::read_lw_polyline()
static void polyline_start() {
  poly_prev_found = false;
  poly_first_found = false;
}

// TODO Reimplement this function(refactoring of dxf_read::read_lw_polyline()
bool dxf_read::read_lw_polyline() {
  polyline_start();

  bool x_found = false;
  bool y_found = false;
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
  bool bulge_found = false;
  double bulge = 0.0;
  bool closed = false;
  int flags;
  bool next_item_found = false;

  while (!_ifs.eof() && !next_item_found) {
    get_line();
    const int n = string_to_int(_str);
    if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_lw_polyline()");
      return false;
    }

    std::istringstream ss;
    ss.imbue(std::locale::classic());
    switch (n) {
    case 0:
      // next item found
      resolve_color_index();
      if (x_found && y_found) {
        // add point
        add_polyline_point(this, x, y, z, bulge_found, bulge);
        bulge_found = false;
        x_found = false;
        y_found = false;
      }
      next_item_found = true;
      break;
    case 10:
      // x
      get_line();
      if (x_found && y_found) {
        // add point
        add_polyline_point(this, x, y, z, bulge_found, bulge);
        bulge_found = false;
        x_found = false;
        y_found = false;
      }
      ss.str(_str);
      ss >> x;
      x = mm(x);
      if (ss.fail()) {
        return false;
      }
      x_found = true;
      break;
    case 20:
      // y
      get_line();
      ss.str(_str);
      ss >> y;
      y = mm(y);
      if (ss.fail()) {
        return false;
      }
      y_found = true;
      break;
    case 38:
      // elevation
      get_line();
      ss.str(_str);
      ss >> z;
      z = mm(z);
      if (ss.fail()) {
        return false;
      }
      break;
    case 42:
      // bulge
      get_line();
      ss.str(_str);
      ss >> bulge;
      if (ss.fail()) {
        return false;
      }
      bulge_found = true;
      break;
    case 70:
      // flags
      get_line();
      flags = string_to_int(_str);
      closed = ((flags & 1) != 0);
      break;
    default:
      get_line();
      handle_common_group_code(n);
      break;
    }
  }

  if (next_item_found) {
    if (closed && poly_first_found) {
      // repeat the first point
      resolve_color_index();
      add_polyline_point(this, poly_first_x, poly_first_y, poly_first_z, false,
                         0.0);
    }
    return true;
  }

  return false;
}

bool dxf_read::read_vertex(dxf_vertex *vertex) {
  bool x_found = false;
  bool y_found = false;
  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (n == 0) {
      resolve_color_index();
      put_line(_str); // read one line too many.  put it back.
      return x_found && y_found;
    } else if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_vertex()");
      return false;
    }

    get_line();
    switch (n) {
    case 10:
    case 20:
    case 30:
      // coords
      x_found = x_found || n == 10;
      y_found = y_found || n == 20;
      handle_coord_code(n, &vertex->point);
      break;
    case 40:
      vertex->starting_width = string_to_double(_str);
      break;
    case 41:
      vertex->ending_width = string_to_double(_str);
      break;
    case 42: {
      const int bulge = string_to_int(_str);
      if (bulge == 0)
        vertex->bulge = dxf_vertex::bulge::StraightSegment;
      else
        vertex->bulge = dxf_vertex::bulge::SemiCircle;
    } break;
    case 70:
      vertex->flags = string_to_unsigned(_str);
      break;
    case 71:
      vertex->polyface_mesh_vertex1 = string_to_int(_str);
      break;
    case 72:
      vertex->polyface_mesh_vertex2 = string_to_int(_str);
      break;
    case 73:
      vertex->polyface_mesh_vertex3 = string_to_int(_str);
      break;
    case 74:
      vertex->polyface_mesh_vertex4 = string_to_int(_str);
      break;
    default:
      handle_common_group_code(n);
      break;
    }
  }

  return false;
}

bool dxf_read::read_3d_face() {
  dxf_3d_face face;
  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (n == 0) {
      resolve_color_index();
      on_read_3d_face(face);
      return true;
    } else if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_3d_face()");
      return false;
    }

    get_line();
    switch (n) {
    case 10:
    case 20:
    case 30:
      handle_coord_code<10, 20, 30>(n, &face.corner1);
      break;
    case 11:
    case 21:
    case 31:
      handle_coord_code<11, 21, 31>(n, &face.corner2);
      break;
    case 12:
    case 22:
    case 32:
      handle_coord_code<12, 22, 32>(n, &face.corner3);
      break;
    case 13:
    case 23:
    case 33:
      handle_coord_code<13, 23, 33>(n, &face.corner4);
      face.has_corner4 = true;
      break;
    case 70:
      face.flags = string_to_unsigned(_str);
      break;
    default:
      handle_common_group_code(n);
      break;
    }
  }

  return false;
}

bool dxf_read::read_solid() {
  dxf_solid solid;

  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (n == 0) {
      resolve_color_index();
      on_read_solid(solid);
      return true;
    } else if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_solid()");
      return false;
    }

    get_line();
    switch (n) {
    case 10:
    case 20:
    case 30:
      handle_coord_code<10, 20, 30>(n, &solid.corner1);
      break;
    case 11:
    case 21:
    case 31:
      handle_coord_code<11, 21, 31>(n, &solid.corner2);
      break;
    case 12:
    case 22:
    case 32:
      handle_coord_code<12, 22, 32>(n, &solid.corner3);
      break;
    case 13:
    case 23:
    case 33:
      handle_coord_code<13, 23, 33>(n, &solid.corner4);
      solid.has_corner4 = true;
      break;
    case 39:
      solid.thickness = string_to_double(_str);
      break;
    case 210:
    case 220:
    case 230:
      handle_coord_code<210, 220, 230>(n, &solid.extrusion_direction);
      break;
    default:
      handle_common_group_code(n);
      break;
    }
  }

  return false;
}

bool dxf_read::read_section() {
  _section_name.clear();
  get_line();
  get_line();
  if (_str != "ENTITIES")
    _section_name = _str;

  _block_name.clear();
  return true;
}

bool dxf_read::read_table() {
  get_line();
  get_line();
  return true;
}

bool dxf_read::read_end_sec() {
  _section_name.clear();
  _block_name.clear();
  return true;
}

bool dxf_read::read_polyline() {
  dxf_polyline polyline;
  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_polyline()");
      return false;
    }

    get_line();
    switch (n) {
    case 0:
      // next item found
      resolve_color_index();
      if (_str == "VERTEX") {
        dxf_vertex vertex;
        if (read_vertex(&vertex))
          polyline.vertices.push_back(std::move(vertex));
      }

      if (_str == "SEQEND") {
        on_read_polyline(polyline);
        return true;
      }

      break;
    case 39:
      polyline.thickness = string_to_double(_str);
      break;
    case 70:
      polyline.flags = string_to_unsigned(_str);
      break;
    case 40:
      polyline.default_start_width = string_to_double(_str);
      break;
    case 41:
      polyline.default_end_width = string_to_double(_str);
      break;
    case 71:
      polyline.polygon_mesh_m_vertex_count = string_to_int(_str);
      break;
    case 72:
      polyline.polygon_mesh_n_vertex_count = string_to_int(_str);
      break;
    case 73:
      polyline.smooth_surface_m_density = string_to_double(_str);
      break;
    case 74:
      polyline.smooth_surface_n_density = string_to_double(_str);
      break;
    case 75:
      polyline.type = static_cast<dxf_polyline::Type>(string_to_unsigned(_str));
      break;
    case 210:
    case 220:
    case 230:
      handle_coord_code<210, 220, 230>(n, &polyline.extrusion_direction);
      break;
    default:
      handle_common_group_code(n);
      break;
    }
  }

  return false;
}

void dxf_read::on_read_arc(double start_angle, double end_angle, double radius,
                           const dxf_coords &c, double z_extrusion_dir,
                           bool hidden) {
  dxf_coords s = {};
  dxf_coords e = {};
  dxf_coords temp = {};
  if (z_extrusion_dir == 1.0) {
    temp.x = c.x;
    temp.y = c.y;
    temp.z = c.z;
    s.x = c.x + radius * cos(start_angle * M_PI / 180);
    s.y = c.y + radius * sin(start_angle * M_PI / 180);
    s.z = c.z;
    e.x = c.x + radius * cos(end_angle * M_PI / 180);
    e.y = c.y + radius * sin(end_angle * M_PI / 180);
    e.z = c.z;
  } else {
    temp.x = -c.x;
    temp.y = c.y;
    temp.z = c.z;

    e.x = -(c.x + radius * cos(start_angle * M_PI / 180));
    e.y = (c.y + radius * sin(start_angle * M_PI / 180));
    e.z = c.z;
    s.x = -(c.x + radius * cos(end_angle * M_PI / 180));
    s.y = (c.y + radius * sin(end_angle * M_PI / 180));
    s.z = c.z;
  }

  on_read_arc(s, e, temp, true, hidden);
}

void dxf_read::on_read_circle(const dxf_coords &c, double radius, bool hidden) {
  constexpr double start_angle = 0;
  const dxf_coords s = {c.x + radius * cos(start_angle * M_PI / 180),
                        c.y + radius * sin(start_angle * M_PI / 180), c.z};

  const bool dir = false;
  on_read_circle(s, c, dir, hidden);
}

void dxf_read::on_read_ellipse(const dxf_coords &c, const dxf_coords &m,
                               double ratio, double start_angle,
                               double end_angle) {
  const double major_radius = sqrt(m.x * m.x + m.y * m.y + m.z * m.z);
  const double minor_radius = major_radius * ratio;

  const double rotation = atan2(m.y / major_radius, m.x / major_radius);
  on_read_ellipse(c, major_radius, minor_radius, rotation, start_angle,
                  end_angle, true);
}

bool dxf_read::read_insert() {
  dxf_insert insert;

  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (n == 0) {
      resolve_color_index();
      on_read_insert(insert);
      return true;
    } else if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_insert()");
      return false;
    }

    get_line();
    switch (n) {
    case 2:
      insert.block_name = _str;
      break;
    case 10:
    case 20:
    case 30:
      handle_coord_code(n, &insert.insert_point);
      break;
    case 41:
      insert.scale_factor.x = string_to_double(_str);
      break;
    case 42:
      insert.scale_factor.y = string_to_double(_str);
      break;
    case 43:
      insert.scale_factor.z = string_to_double(_str);
      break;
    case 50:
      insert.rotation_angle = string_to_double(_str);
      break;
    case 70:
      insert.column_count = string_to_int(_str);
      break;
    case 71:
      insert.row_count = string_to_int(_str);
      break;
    case 44:
      insert.column_spacing = mm(string_to_double(_str));
      break;
    case 45:
      insert.row_spacing = mm(string_to_double(_str));
      break;
    case 210:
    case 220:
    case 230:
      handle_coord_code<210, 220, 230>(n, &insert.extrusion_direction);
      break;
    default:
      handle_common_group_code(n);
      break;
    }
  }

  return false;
}

bool dxf_read::read_dimension() {
  dxf_coords s = {}; // startpoint
  dxf_coords e = {}; // endpoint
  dxf_coords p = {}; // dimpoint
  double rot = -1.0; // rotation

  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (n == 0) {
      resolve_color_index();
      on_read_dimension(s, e, p, rot * M_PI / 180);
      return true;
    } else if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_dimension()");
      return false;
    }

    get_line();
    switch (n) {
    case 13:
    case 23:
    case 33:
      handle_coord_code<13, 23, 33>(n, &s);
      break;
    case 14:
    case 24:
    case 34:
      handle_coord_code<14, 24, 34>(n, &e);
      break;
    case 10:
    case 20:
    case 30:
      handle_coord_code<10, 20, 30>(n, &p);
      break;
    case 50:
      rot = string_to_double(_str);
      break;
    case 100:
    case 39:
    case 210:
    case 220:
    case 230:
      break;
    default:
      handle_common_group_code(n);
      break;
    }
  }

  return false;
}

bool dxf_read::read_block_info() {
  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_block_info()");
      return false;
    }

    get_line();
    switch (n) {
    case 2:
      _block_name = _str;
      return true;
    case 3:
      _block_name = _str;
      return true;
    default:
      break;
    }
  }

  return false;
}

void dxf_read::get_line() {
  if (!_unused_line.empty()) {
    _str = _unused_line;
    _unused_line.clear();
    return;
  }

  std::getline(_ifs, _str);
  _gcount = _str.size();
  ++_line_nb;

  auto itNonSpace = _str.begin();
  while (itNonSpace != _str.end()) {
    if (!std::isspace(*itNonSpace))
      break;

    ++itNonSpace;
  }

  _str.erase(_str.begin(), itNonSpace);
}

void dxf_read::put_line(const std::string &value) { _unused_line = value; }

bool dxf_read::read_ins_units() {
  get_line();
  get_line();
  const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
  if (!is_string_to_error_value(n)) {
    _units = static_cast<dxf_units_type>(n);
    return true;
  } else {
    this->report_error_read_integer("DXF::ReadUnits()");
    return false;
  }
}

bool dxf_read::read_measurement() {
  get_line();
  get_line();
  const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
  if (n == 0)
    _measurement_inch = true;

  return true;
}

bool dxf_read::read_layer() {
  std::string layername;
  color_index_t colorIndex = -1;

  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (n == 0) {
      if (layername.empty()) {
        this->report_error_read_integer("DXF::read_layer() - no layer name");
        return false;
      }

      _layer_ColorIndex_map[layername] = colorIndex;
      return true;
    } else if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_layer()");
      return false;
    }

    get_line();
    switch (n) {
    case 2:
      layername = _str;
      break;
    case 62:
      colorIndex = string_to_int(_str);
      break;
    case 6:
    case 70:
    case 100:
    case 290:
    case 370:
    case 390:
      break;
    default:
      break;
    }
  }

  return false;
}

bool dxf_read::read_style() {
  dxf_style style;

  while (!_ifs.eof()) {
    get_line();
    const int n = string_to_int(_str, string_to_error_mode::ReturnErrorValue);
    if (n == 0) {
      if (style.name.empty()) {
        this->report_error_read_integer("DXF::read_style() - no style name");
        return false;
      }

      _map_style.insert({style.name, style});
      return true;
    } else if (is_string_to_error_value(n)) {
      this->report_error_read_integer("DXF::read_style()");
      return false;
    }

    get_line();
    switch (n) {
    case 2:
      style.name = _str;
      break;
    case 40:
      style.fixed_text_height = mm(string_to_double(_str));
      break;
    case 41:
      style.width_factor = string_to_double(_str);
      break;
    case 50:
      style.oblique_angle = string_to_double(_str);
      break;
    case 3:
      style.primary_font_file_name = _str;
      break;
    case 4:
      style.big_font_file_name = _str;
      break;
    default:
      break;
    }
  }

  return false;
}

bool dxf_read::read_acad_ver() {
  static const std::vector<std::string> VersionNames = {
      "AC1006", "AC1009", "AC1012", "AC1014", "AC1015",
      "AC1018", "AC1021", "AC1024", "AC1027", "AC1032"};

  assert(VersionNames.size() == RNewer - ROlder - 1);
  get_line();
  get_line();
  auto first = VersionNames.cbegin();
  auto last = VersionNames.cend();
  auto found = std::lower_bound(first, last, _str);
  if (found == last) {
    _version = RNewer;
  } else if (*found == _str) {
    _version = (dxf_version_t)(std::distance(first, found) + (ROlder + 1));
  } else if (found == first) {
    _version = ROlder;
  } else {
    _version = RUnknown;
  }

  return resolve_encoding();
}

bool dxf_read::read_dwg_code_page() {
  get_line();
  get_line();
  _code_page = _str;

  return resolve_encoding();
}

bool dxf_read::resolve_encoding() {
  if (_version >= R2007) {
    return this->set_source_encoding("UTF8");
  } else {
    std::transform(
        _code_page.cbegin(), _code_page.cend(), _code_page.begin(),
        [](char c) { return std::toupper(c, std::locale::classic()); });
    if (_code_page.empty())
      _code_page = "ANSI_1252";

    return this->set_source_encoding(_code_page);
  }
}

void dxf_read::handle_common_group_code(int n) {
  switch (n) {
  case 8:
    _layer_name = _str;
    break;
  case 62:
    _color_index = string_to_int(_str);
    break;
  }
}

void dxf_read::do_read(bool ignore_errors) {
  _ignore_errors = ignore_errors;
  _gcount = 0;
  if (_fail)
    return;

  std::unordered_map<std::string, std::function<bool()>> mapHeaderVarHandler;
  mapHeaderVarHandler.insert({"$INSUNITS", [=] { return read_ins_units(); }});
  mapHeaderVarHandler.insert(
      {"$MEASUREMENT", [=] { return read_measurement(); }});
  mapHeaderVarHandler.insert({"$ACADVER", [=] { return read_acad_ver(); }});
  mapHeaderVarHandler.insert(
      {"$DWGCODEPAGE", [=] { return read_dwg_code_page(); }});

  std::unordered_map<std::string, std::function<bool()>> mapEntityHandler;
  mapEntityHandler.insert({"ARC", [=] { return read_arc(); }});
  mapEntityHandler.insert({"BLOCK", [=] { return read_block_info(); }});
  mapEntityHandler.insert({"CIRCLE", [=] { return read_circle(); }});
  mapEntityHandler.insert({"DIMENSION", [=] { return read_dimension(); }});
  mapEntityHandler.insert({"ELLIPSE", [=] { return read_ellipse(); }});
  mapEntityHandler.insert({"INSERT", [=] { return read_insert(); }});
  mapEntityHandler.insert({"LAYER", [=] { return read_layer(); }});
  mapEntityHandler.insert({"LINE", [=] { return read_line(); }});
  mapEntityHandler.insert({"LWPOLYLINE", [=] { return read_lw_polyline(); }});
  mapEntityHandler.insert({"MTEXT", [=] { return read_mtext(); }});
  mapEntityHandler.insert({"POINT", [=] { return read_point(); }});
  mapEntityHandler.insert({"POLYLINE", [=] { return read_polyline(); }});
  mapEntityHandler.insert({"SECTION", [=] { return read_section(); }});
  mapEntityHandler.insert({"SOLID", [=] { return read_solid(); }});
  mapEntityHandler.insert({"3DFACE", [=] { return read_3d_face(); }});
  mapEntityHandler.insert({"SPLINE", [=] { return read_spline(); }});
  mapEntityHandler.insert({"STYLE", [=] { return read_style(); }});
  mapEntityHandler.insert({"TEXT", [=] { return read_text(); }});
  mapEntityHandler.insert({"TABLE", [=] { return read_table(); }});
  mapEntityHandler.insert({"ENDSEC", [=] { return read_end_sec(); }});

  get_line();

  ScopedCLocale _(LC_NUMERIC);
  while (!_ifs.eof()) {
    _color_index = ColorBylayer;

    {
      auto itHandler = mapHeaderVarHandler.find(_str);
      if (itHandler != mapHeaderVarHandler.cend()) {
        const auto &fn = itHandler->second;
        if (fn())
          continue;
        else
          return;
      }
    }

    if (_str == "0") {
      get_line();
      if (_str == "0")
        get_line();

      auto itHandler = mapEntityHandler.find(_str);
      if (itHandler != mapEntityHandler.cend()) {
        const auto &fn = itHandler->second;
        bool okRead = false;
        std::string exceptionMsg;
        try {
          okRead = fn();
        } catch (const std::runtime_error &err) {
          exceptionMsg = err.what();
        }

        if (okRead) {
          continue;
        } else {
          std::string errMsg = "DXF::do_read() - Failed to read " + _str;
          if (!exceptionMsg.empty())
            errMsg += "\nError: " + exceptionMsg;

          this->report_error(errMsg);
          if (_str == "LAYER")
            continue;
          else
            return;
        }
      }
    }

    get_line();
  }

  add_graphics();
}

void dxf_read::resolve_color_index() {
  if (_color_index == ColorBylayer)
    _color_index = _layer_ColorIndex_map[_layer_name];
}

void dxf_read::report_error_read_integer(const char *context) {
  std::string msg;
  if (context) {
    msg += context;
    msg += " - ";
  }

  msg += "Failed to read integer from '";
  msg += _str;
  msg += "'";
  this->report_error(msg);
}

std::streamsize dxf_read::gcount() const { return _gcount; }

std::string dxf_read::layer_name() const {
  std::string result;

  if (!_section_name.empty()) {
    result.append(_section_name);
    result.append(" ");
  }

  if (!_block_name.empty()) {
    result.append(_block_name);
    result.append(" ");
  }

  if (!_layer_name.empty()) {
    result.append(_layer_name);
  }

  return result;
}

} // namespace dxf
} // namespace flywave
