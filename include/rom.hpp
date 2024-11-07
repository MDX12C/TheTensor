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
  static inline void starter(char* const&, char* const&);
  static inline void ender();
  template <typename T>
  static inline bool read(std::string const&, T* const&);
  template <typename T>
  static inline bool write(std::string const&, T* const&, unsigned int const&);
  static inline bool remove(std::string const&);
};

/**
 * @brief constructor for rom
 * @param fileName the __FILE__
 * @param stamp the __TIMESTAMP__
 * @warning don't use it
 */
void RomSupport::starter(char* const& fileName, char* const& stamp) {
  LOG("S:Rom IO start\n");
  // create fileName
  std::string name;
  name = fileName;
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
  // open file
  fileSelf.openFile(name, H5F_ACC_RDWR);
  // check for file version
  std::string value = stamp;
  H5::StrType sType(H5::PredType::C_S1, H5T_VARIABLE);
  if (fileSelf.attrExists("version")) {
    H5::Attribute attr = fileSelf.openAttribute("version");
    std::string temp;
    attr.read(sType, temp);
    if (temp != value) {
      H5::Group root = fileSelf.openGroup("/");
      hsize_t nums;
      nums = root.getNumObjs();
      H5G_obj_t objType;
      for (hsize_t i = nums - 1; i >= 0; i--) {
        name = root.getObjnameByIdx(i);
        objType = root.getObjTypeByIdx(i);
        if (objType == H5G_DATASET) {
          fileSelf.unlink(name);
        }
      }
    }
  } else {
    H5::Attribute attr =
        fileSelf.createAttribute("version", sType, H5::DataSpace(H5S_SCALAR));
    attr.write(sType, value);
    H5::Group root = fileSelf.openGroup("/");
    hsize_t nums;
    nums = root.getNumObjs();
    H5G_obj_t objType;
    for (hsize_t i = nums - 1; i >= 0; i--) {
      name = root.getObjnameByIdx(i);
      objType = root.getObjTypeByIdx(i);
      if (objType == H5G_DATASET) {
        fileSelf.unlink(name);
      }
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
  LOG("S:Rom IO end\n");
  block.close();
  fileSelf.close();
  return;
}
/**
 * @brief remove the block
 * @param name the name of the block
 * @return if remove success, true. False otherwise.
 */
bool RomSupport::remove(std::string const& name) {
  LOG("C:remove for %s\n", name);
  if (fileSelf.nameExists(name)) {
    fileSelf.unlink(name);
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
bool RomSupport::write(std::string const& name, T* const& obj,
                       unsigned int const& size) {
  LOG("C:write %s\n", name);
  H5::DataSet block;
  if (fileSelf.nameExists(name)) {
    block = fileSelf.openDataSet(name);
    if ((block.getStorageSize() / sizeof(T)) != size) {
      LOG("E:wrong size\n");
      block.close();
      fileSelf.unlink(name);
      hsize_t dim[1];
      dim[0] = size;
      H5::DataSpace space(1, dim);
      if constexpr (std::is_same_v<T, int>) {
        block = fileSelf.createDataSet(name, H5::PredType::NATIVE_INT, space);
      } else if constexpr (std::is_same_v<T, float>) {
        block = fileSelf.createDataSet(name, H5::PredType::NATIVE_FLOAT, space);
      } else {
        LOG("B:unsupport type\n");
        return false;
      }
    }
    if constexpr (std::is_same_v<T, int>) {
      block.write(obj, H5::PredType::NATIVE_INT);
    } else if constexpr (std::is_same_v<T, float>) {
      block.write(obj, H5::PredType::NATIVE_FLOAT);
    } else {
      LOG("B:unsupport type\n");
      return false;
    }
  } else {
    hsize_t dim[1];
    dim[0] = size;
    H5::DataSpace space(1, dim);
    if constexpr (std::is_same_v<T, int>) {
      block = fileSelf.createDataSet(name, H5::PredType::NATIVE_INT, space);
      block.write(obj, H5::PredType::NATIVE_INT);
    } else if constexpr (std::is_same_v<T, float>) {
      block = fileSelf.createDataSet(name, H5::PredType::NATIVE_FLOAT, space);
      block.write(obj, H5::PredType::NATIVE_FLOAT);
    } else {
      LOG("B:unsupport type\n");
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
bool RomSupport::read(std::string const& name, T* const& obj) {
  LOG("C:read %s\n", name);
  H5::DataSet block;
  if (fileSelf.nameExists(name)) {
    block = fileSelf.openDataSet(name);
    if constexpr (std::is_same_v<T, int>) {
      block.read(obj, H5::PredType::NATIVE_INT);
    } else if constexpr (std::is_same_v<T, float>) {
      block.read(obj, H5::PredType::NATIVE_FLOAT);
    } else {
      LOG("B:unsupport type\n");
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