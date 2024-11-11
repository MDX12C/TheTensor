
#include "interface.hpp"

#define SHOW(X) std::cout << #X << '=' << X << std::endl;
H5::H5File fileSelf;
void starter(const char* const&, const char* const&);
void ender();
template <typename T>
bool write(const char* const&, T* const&, unsigned int const&);
template <typename T>
bool read(const char* const&, T* const&);
signed main() {
  CONSTRUCT;
  starter(__FILE__, __TIMESTAMP__);
  std::vector<float> alpha(10);
  read("alpha", alpha.begin().base());
  for (auto i : alpha) std::cout << i << std::endl;
  for (auto i = 0; i < 10; i++) {
    alpha[i] = i;
  }
  write("alpha", alpha.begin().base(), static_cast<unsigned int>(alpha.size()));
  ender();
  DESTRUCT;
  return 0;
}
void ender() {
  LOG("S:Rom IO end");
  fileSelf.close();
  return;
}
void starter(const char* const& fileName, const char* const& stamp) {
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
#if 1
  name = "/../datas/" + name;
  name = std::filesystem::current_path().string() + name;
#else
  name = "../datas/" + name;
#endif
  LOG("C:name=%s\n", name.c_str());
  // open file
  fileSelf.openFile(name, H5F_ACC_RDONLY);
  // check for file version
  std::string value = stamp;
  H5::StrType sType(H5::PredType::C_S1, H5T_VARIABLE);
  if (fileSelf.attrExists("version")) {
    LOG("C:version exist\n");
    H5::Attribute attr = fileSelf.openAttribute("version");
    std::string temp;
    attr.read(sType, temp);
    if (temp != value) {
      LOG("C:version not match");
      fileSelf.close();
      fileSelf.openFile(name, H5F_ACC_TRUNC);
      H5::Group root = fileSelf.openGroup("/");
      hsize_t nums;
      nums = root.getNumObjs();
      LOG("C:%d objects in old version", nums);
      H5G_obj_t objType;
      for (hsize_t i = 0; i < nums; i++) {
        LOG("C:delete\n");
        name = root.getObjnameByIdx(0);
        objType = root.getObjTypeByIdx(0);
        if (objType == H5G_DATASET) fileSelf.unlink(name);
      }
    }
  } else {
    LOG("C:version not exist");
    fileSelf.close();
    fileSelf.openFile(name, H5F_ACC_TRUNC);
    H5::Attribute attr =
        fileSelf.createAttribute("version", sType, H5::DataSpace(H5S_SCALAR));
    attr.write(sType, value);
    H5::Group root = fileSelf.openGroup("/");
    hsize_t nums;
    nums = root.getNumObjs();
    LOG("C:%d objects in old version", nums);
    H5G_obj_t objType;
    for (hsize_t i = 0; i < nums; i++) {
      LOG("C:delete\n");
      name = root.getObjnameByIdx(0);
      objType = root.getObjTypeByIdx(0);
      if (objType == H5G_DATASET) fileSelf.unlink(name);
    }
  }
  fileSelf.close();
  fileSelf.openFile(name, H5F_ACC_RDWR);
  return;
}
template <typename T>
bool write(const char* const& name, T* const& obj, unsigned int const& size) {
  LOG("C:write %s", name);
  if ((size == 0) || (obj == nullptr)) return false;
  H5::DataSet block;
  if (fileSelf.nameExists(name)) {
    LOG("C:name exist");
    block = fileSelf.openDataSet(name);
    if ((block.getStorageSize() / sizeof(T)) != size) {
      LOG("E:wrong size");
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
      block = fileSelf.createDataSet(name, H5::PredType::NATIVE_INT, space);
      block.write(obj, H5::PredType::NATIVE_INT);
    } else if constexpr (std::is_same_v<T, float>) {
      LOG("C:write float");
      block = fileSelf.createDataSet(name, H5::PredType::NATIVE_FLOAT, space);
      block.write(obj, H5::PredType::NATIVE_FLOAT);
    } else {
      LOG("B:unsupport type");
      return false;
    }
  }
  return true;
}
template <typename T>
bool read(const char* const& name, T* const& obj) {
  LOG("C:read %s", name);
  H5::DataSet block;
  if (fileSelf.nameExists(name)) {
    block = fileSelf.openDataSet(name);
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