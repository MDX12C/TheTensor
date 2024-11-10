#include "define.hpp"
#ifndef ROM_H
#include "basic.hpp"
#include "log.hpp"
#include "matrix.hpp"

#define ROM_H 1
namespace rom_io {
class RomSupport {
 private:
  static H5::H5File fileSelf;

 public:
  static inline void starter(const char* const&, const char* const&);
  static inline void ender();
  static inline void switchMode(bool const&);
  template <typename T>
  static inline bool read(const char* const&, T* const&);
  template <typename T>
  static inline bool write(const char* const&, T* const&, unsigned int const&);
  static inline bool remove(const char* const&);
};

/**
 * @brief constructor for rom
 * @param fileName the __FILE__
 * @param stamp the __TIMESTAMP__
 * @warning don't use it
 */
void RomSupport::starter(const char* const& fileName,
                         const char* const& stamp) {
  LOG("S:Rom IO start");
  // create fileName
  std::string name = fileName;
  for (auto i = name.size() - 1; i >= 0; i--) {
    if (name[i] == '/') {
      name = name.substr(i + 1);
      break;
    }
  }
  name.pop_back();
  name.pop_back();
  name += "hdf5";
  name = "/../datas/" + name;
  name = std::filesystem::current_path().string() + name;
  LOG("C:name %s\n", name.c_str());
  // open file
  RomSupport::fileSelf.openFile(name, H5F_ACC_RDWR);
  // check for file version
  std::string value = stamp;
  H5::StrType sType(H5::PredType::C_S1, H5T_VARIABLE);
  if (RomSupport::fileSelf.attrExists("version")) {
    LOG("C:version exist\n");
    H5::Attribute attr = RomSupport::fileSelf.openAttribute("version");
    std::string temp;
    attr.read(sType, temp);
    if (temp != value) {
      LOG("C:version not match");
      H5::Group root = RomSupport::fileSelf.openGroup("/");
      hsize_t nums;
      nums = root.getNumObjs();
      LOG("C:%d objects in old version", nums);
      H5G_obj_t objType;
      for (hsize_t i = 0; i < nums; i++) {
        LOG("C:delete\n");
        name = root.getObjnameByIdx(0);
        objType = root.getObjTypeByIdx(0);
        if (objType == H5G_DATASET) RomSupport::fileSelf.unlink(name);
      }
    }
  } else {
    LOG("C:version not exist");
    H5::Attribute attr = RomSupport::fileSelf.createAttribute(
        "version", sType, H5::DataSpace(H5S_SCALAR));
    attr.write(sType, value);
    H5::Group root = RomSupport::fileSelf.openGroup("/");
    hsize_t nums;
    nums = root.getNumObjs();
    LOG("C:%d objects in old version", nums);
    H5G_obj_t objType;
    for (hsize_t i = 0; i < nums; i++) {
      LOG("C:delete\n");
      name = root.getObjnameByIdx(0);
      objType = root.getObjTypeByIdx(0);
      if (objType == H5G_DATASET) RomSupport::fileSelf.unlink(name);
    }
  }
  name.clear();
  return;
}
/**
 * @brief destructor for rom
 * @warning don't use it
 */
void RomSupport::ender() {
  LOG("S:Rom IO end");
  RomSupport::fileSelf.close();
  return;
}
/**
 * @brief remove the block
 * @param name the name of the block
 * @return if remove success, true. False otherwise.
 */
bool RomSupport::remove(const char* const& name) {
  LOG("C:remove for %s", name);
  if (RomSupport::fileSelf.nameExists(name)) {
    RomSupport::fileSelf.unlink(name);
    return true;
  }
  return false;
}
/**
 * @brief write the datas into the file
 * @param name the name of the memory block
 * @param obj the pointer
 * @param size the size
 * @return If it success, true. False otherwise.
 */
template <typename T>
bool RomSupport::write(const char* const& name, T* const& obj,
                       unsigned int const& size) {
  LOG("C:write %s", name);
  if ((size == 0) || (obj == nullptr)) return false;
  H5::DataSet block;
  if (RomSupport::fileSelf.nameExists(name)) {
    LOG("C:name exist");
    block = RomSupport::fileSelf.openDataSet(name);
    if ((block.getStorageSize() / sizeof(T)) != size) {
      LOG("E:wrong size");
      block.close();
      RomSupport::fileSelf.unlink(name);
      hsize_t dim[1];
      dim[0] = size;
      H5::DataSpace space(1, dim);
      if constexpr (std::is_same_v<T, int>) {
        block = RomSupport::fileSelf.createDataSet(
            name, H5::PredType::NATIVE_INT, space);
      } else if constexpr (std::is_same_v<T, float>) {
        block = RomSupport::fileSelf.createDataSet(
            name, H5::PredType::NATIVE_FLOAT, space);
      } else {
        LOG("B:unsupport type");
        return false;
      }
    }
    if constexpr (std::is_same_v<T, int>) {
      block.write(obj, H5::PredType::NATIVE_INT);
    } else if constexpr (std::is_same_v<T, float>) {
      block.write(obj, H5::PredType::NATIVE_FLOAT);
    } else {
      LOG("B:unsupport type");
      return false;
    }
  } else {
    LOG("C:name not exist");
    hsize_t dim[1];
    dim[0] = size;
    H5::DataSpace space(1, dim);
    if constexpr (std::is_same_v<T, int>) {
      LOG("C:write int");
      block = RomSupport::fileSelf.createDataSet(name, H5::PredType::NATIVE_INT,
                                                 space);
      block.write(obj, H5::PredType::NATIVE_INT);
    } else if constexpr (std::is_same_v<T, float>) {
      LOG("C:write float");
      block = RomSupport::fileSelf.createDataSet(
          name, H5::PredType::NATIVE_FLOAT, space);
      block.write(obj, H5::PredType::NATIVE_FLOAT);
    } else {
      LOG("B:unsupport type");
      return false;
    }
  }
  return true;
}
/**
 * @brief read the datas from the file
 * @param name the name of the memory block
 * @param obj the pointer
 * @return If it success, true. False otherwise.
 * @warning if memory of obj is not enough, will leak memory
 */
template <typename T>
bool RomSupport::read(const char* const& name, T* const& obj) {
  LOG("C:read %s", name);
  H5::DataSet block;
  if (RomSupport::fileSelf.nameExists(name)) {
    block = RomSupport::fileSelf.openDataSet(name);
    if constexpr (std::is_same_v<T, int>) {
      block.read(obj, H5::PredType::NATIVE_INT);
    } else if constexpr (std::is_same_v<T, float>) {
      block.read(obj, H5::PredType::NATIVE_FLOAT);
    } else {
      LOG("B:unsupport type");
      return false;
    }
    return true;
  }
  return false;
}
}  // namespace rom_io
#define ROM_CON rom_io::RomSupport::starter(__FILE__, __TIMESTAMP__);
#define ROM_DES rom_io::RomSupport::ender();
#endif