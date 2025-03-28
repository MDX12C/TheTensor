#include "define.hpp"
#ifndef ROM_H
#define ROM_H 1
#include "basic.hpp"
// the suppurt space, don't touch it
namespace file_io {
// the accuracy of rom to store
constexpr size_t ROM_ACC = 6;
template <typename T>
concept _FloatLong = std::is_floating_point_v<T> && basic_math::longer<T> &&
                     basic_math::support<T>;
template <typename T>
concept _IntShort = (!std::is_floating_point_v<T>) &&
                    (!basic_math::longer<T>) && basic_math::support<T>;
template <typename T>
concept _IntLong = (!std::is_floating_point_v<T>) && basic_math::longer<T> &&
                   basic_math::support<T>;
template <typename T>
concept _FloatShort = std::is_floating_point_v<T> && (!basic_math::longer<T>) &&
                      basic_math::support<T>;
template <typename T>
concept _Float = std::is_floating_point_v<T> && basic_math::support<T>;
template <typename T>
concept _Int = (!std::is_floating_point_v<T>) && basic_math::support<T>;

/**
 * @brief retrun if the character is [digits,dot,plus,minus]
 */
inline bool isNumber(char const& __c) noexcept {
  return ((__c >= '0') && (__c <= '9')) || (__c == '+') || (__c == '-') ||
         (__c == '.');
}
/**
 * @brief retrun if the character is [alphabet,blank,underline,digit]
 */
inline bool isAlphabet(char const& __c) noexcept {
  return ((__c >= 'A') && (__c <= 'Z')) || ((__c >= 'a') && (__c <= 'z')) ||
         (__c == ' ') || (__c == '_') || ((__c >= '0') && (__c <= '9'));
}
/**
 * @brief num to string
 * @param __str the answer string, also the answer
 * @param __num the number
 * @return the reference of the string
 * @throw when the type of number is not supported
 */
template <typename T>
inline std::string& numToString(std::string& __str, T& __num) {
  throw system_message::Error("unsupport type for NTS");
}
template <_Int T>
inline std::string& numToString(std::string& __str, T& __num) noexcept {
  LOG("C:num to string <interal>");
  T num = __num;
  __str.clear();
  __str.resize(basic_math::intDigits(num) + 1);
  if constexpr (std::is_signed_v<T>) {
    if (num >= 0) {
      __str[0] = '+';
    } else {
      __str[0] = '-';
      num *= static_cast<T>(-1);
    }
  } else {
    __str[0] = '+';
  }
  for (auto i = basic_math::intDigits(num); i > 0; i--) {
    __str[i] = static_cast<char>((num % 10) + '0');
    num /= 10;
  }
  return __str;
}
template <_Float T>
inline std::string& numToString(std::string& __str, T& __num) noexcept {
  LOG("C:num to string <floating>");
  T num=__num;
  __str.clear();
  __str.resize(basic_math::intDigits(num) + 2 + ROM_ACC);
  if (num >= 0) {
    __str[0] = '+';
  } else {
    __str[0] = '-';
    num *= static_cast<T>(-1);
  }
  DEBUG(num);
  unsigned long long intPart =
      static_cast<unsigned long long>(std::floor(num));
  num -= static_cast<T>(intPart);
  unsigned long long floatPart = num * std::pow(10, ROM_ACC);
  DEBUG(intPart);
  DEBUG(floatPart);
  size_t i = __str.size() - 1;
  for (size_t w = 0; w < ROM_ACC; w++) {
    __str[i] = static_cast<char>((floatPart % 10) + '0');
    floatPart /= 10;
    i--;
  }
  __str[i] = '.';
  i--;
  while (i > 0) {
    __str[i] = static_cast<char>((intPart % 10) + '0');
    intPart /= 10;
    i--;
  }
  return __str;
}
/**
 * @brief string to number
 * @param __str the string
 * @param __num the number, also the answer
 * @return the reference of the number
 * @throw when the type of number is not supported
 */
template <typename T>
inline T& stringToNum(std::string& __str, T& __num) {
  throw system_message::Error("unsupport type for STN");
}
template <_Int T>
inline T& stringToNum(std::string& __str, T& __num) noexcept {
  LOG("C:string to num <interal>")
  __num = static_cast<T>(0);
  for (size_t i = 1; i < __str.size(); i++) {
    __num *= static_cast<T>(10);
    __num += static_cast<T>(__str[i] - '0');
  }
  if constexpr (std::is_signed_v<T>)
    if (__str[0] == '-') __num *= static_cast<T>(-1);
  return __num;
}
template <_Float T>
inline T& stringToNum(std::string& __str, T& __num) noexcept {
  LOG("C:string to num <floating>")
  __num = static_cast<T>(0);
  float interPart = static_cast<T>(0);
  auto i = __str.size() - 1;
  for (size_t w = 0; w < ROM_ACC; w++) {
    __num += static_cast<T>(__str[i] - '0');
    __num /= static_cast<T>(10);
    i--;
  }
  DEBUG(__num);
  for (size_t w = 1; w < i; w++) {
    interPart *= 10;
    interPart += static_cast<float>(__str[w] - '0');
  }
  DEBUG(interPart);
  __num += static_cast<T>(interPart);
  if constexpr (std::is_signed_v<T>)
    if (__str[0] == '-') __num *= static_cast<T>(-1);
  return __num;
}

class FileIO {
 public:
  // the mode of file item
  typedef enum IOMode {
    // idling, also the default mode
    idle,
    // reading, read from the file
    reading,
    // writing, write into the file
    writing
  } Status;

 private:
  std::string fileName_;
  std::fstream fileSelf_;
  std::fstream fileIndex_;
  Status mode_;
  inline bool find(std::string&);
  inline void regist(std::string&);

 public:
  FileIO() noexcept;
  ~FileIO() noexcept;
  inline void setFile(const char* const&, const char* const&);
  inline bool switchMode(Status const&, bool const&) noexcept;
  // return the name of file
  inline std::string checkName() noexcept { return fileName_; }
  // retrun the mode now
  inline Status checkMode() noexcept { return mode_; }
  inline void print(std::ostream&) noexcept;
  template <typename T, typename W>
  inline bool read(W&, T* const&, size_t const&);
  template <typename T, typename W>
  inline bool write(W&, T* const&, size_t const&);
};
FileIO::FileIO() noexcept {
  LOG("C:constructor of FileIO");
  fileName_ = "";
  mode_ = idle;
  return;
}
FileIO::~FileIO() noexcept {
  LOG("C:destructor of FileIO");
  if (fileSelf_.is_open()) fileSelf_.close();
  if (fileIndex_.is_open()) fileIndex_.close();
  return;
}
/**
 * @brief set the file
 * @param __file put __FILE__ define in here
 * @param __type the type of the file, "txt" is default
 */
inline void FileIO::setFile(const char* const& __file,
                            const char* const& __type = "txt") {
  LOG("C:set file of FileIO");
  fileName_ = __file;
  fileName_.pop_back();
  fileName_.pop_back();
  fileName_ = fileName_.substr(fileName_.find_last_of('/'));
  fileName_.insert(0, "/../datas");
  fileName_.insert(0, std::filesystem::current_path().string());
  fileName_ += __type;
  DEBUG(fileName_);
  return;
}
/**
 * @brief switch mode in [idle,read,writing]
 * @param __obj mode you want
 * @return if the switch is successful, return true
 */
inline bool FileIO::switchMode(Status const& __obj = idle,
                               bool const& __special = false) noexcept {
  LOG("C:switch to mode %d of FileIO", __obj);
  if (__obj >= 3) {
    LOG("E:bad argument");
    return false;
  }
  if (mode_ == __obj) {
    LOG("E:same mode");
    return true;
  }
  if (fileSelf_.is_open()) fileSelf_.close();
  if (fileIndex_.is_open()) fileIndex_.close();
  mode_ = __obj;
  if (__obj == idle) return true;
  if (__obj == reading) {
    fileSelf_.open(fileName_, std::ios::in | std::ios::binary);
    fileIndex_.open(fileName_ + "index", std::ios::in | std::ios::binary);
  } else if (__obj == writing) {
    if (__special) {
      fileSelf_.open(fileName_,
                     std::ios::out | std::ios::app | std::ios::binary);
      fileIndex_.open(fileName_ + "index",
                      std::ios::out | std::ios::app | std::ios::binary);
    } else {
      fileSelf_.open(fileName_,
                     std::ios::out | std::ios::trunc | std::ios::binary);
      fileIndex_.open(fileName_ + "index",
                      std::ios::out | std::ios::trunc | std::ios::binary);
    }
  }
  if (!(fileSelf_.is_open() && fileIndex_.is_open())) {
    mode_ = idle;
    LOG("E:open fail!");
    return false;
  }
  return true;
}
/**
 * @brief print the file status now
 * @param __os the stream, std::cout is default
 */
inline void FileIO::print(std::ostream& __os = std::cout) noexcept {
  LOG("C:print of FileIO");
  __os << "++++++++++\nfile name: " << fileName_ << "\nmode: ";
  if (mode_ == idle) {
    __os << "idle\n++++++++++\n";
  } else if (mode_ == reading) {
    __os << "reading\n++++++++++\n";
  } else if (mode_ == writing) {
    __os << "writing\n++++++++++\n";
  }
  return;
}
// the private function
inline bool FileIO::find(std::string& __str) {
  LOG("C:find of FileIO");
  fileIndex_.seekg(0, std::ios::beg);
  char c;
  size_t i = 0;
  bool checking = false;
  while (!fileIndex_.eof()) {
    fileIndex_.get(c);
    if (checking) {
      if (isAlphabet(c)) {
        if ((i < __str.size()) && (c == __str[i])) {
          i++;
        } else {
          checking = false;
          i = 0;
        }
      } else if ((c == ',') && (i == __str.size())) {
        std::string s;
        while (true) {
          fileIndex_.get(c);
          if (isNumber(c)) {
            s.push_back(c);
          } else {
            break;
          }
        }
        DEBUG(s);
        unsigned long long size;
        stringToNum(s, size);
        DEBUG(size);
        fileSelf_.seekg(size, std::ios::beg);
        return true;
      } else {
        checking = false;
        i = 0;
      }
    } else {
      if (c == '(') {
        i = 0;
        checking = true;
      }
    }
  }
  return false;
}
// the private function
inline void FileIO::regist(std::string& __str) {
  LOG("C:regist of FileIO");
  unsigned long long position = fileSelf_.tellp();
  std::string s;
  numToString(s, position);
  fileIndex_.put('(');
  for (auto i : __str) fileIndex_.put(i);
  fileIndex_.put(',');
  for (auto i : s) fileIndex_.put(i);
  fileIndex_.put(')');
  return;
}
/**
 * @brief read datas from the file
 * @param __str the name of the data block, can be c-style or STL
 * @param __ptr the pointer of the datas buffer
 * @param __size how many datas you want read
 * @return true if the read is successful, false otherwise
 */
template <typename T, typename W>
inline bool FileIO::read(W& __str, T* const& __ptr, size_t const& __size) {
  LOG("C:read of FileIO");
  if (mode_ != reading) {
    LOG("E:invalid way in mode\"%d\"", static_cast<int>(mode_));
    return false;
  }
  std::string temp = __str;
  if (!find(temp)) {
    LOG("E:cann't find block=\"%s\"", temp.c_str());
    return false;
  }
  char c;
  fileSelf_.get(c);
  if (c != '[') {
    LOG("E:bad file");
    return false;
  }
  size_t i = 0;
  temp.clear();
  while ((!fileSelf_.eof()) && (i < __size)) {
    fileSelf_.get(c);
    if (isNumber(c)) {
      temp.push_back(c);
    } else {
      stringToNum(temp, __ptr[i]);
      temp.clear();
      i++;
      if (c == ']') break;
    }
  }
  return true;
}
/**
 * @brief write datas into the file
 * @param __str the name of the data block, can be c-style or STL
 * @param __ptr the pointer of the datas buffer
 * @param __size how many datas you want write
 * @return true if the write is successful, false otherwise
 */
template <typename T, typename W>
inline bool FileIO::write(W& __str, T* const& __ptr, size_t const& __size) {
  LOG("C:write of FileIO");
  if (mode_ != writing) {
    LOG("E:invalid way in mode\"%d\"", static_cast<int>(mode_));
    return false;
  }
  std::string temp = __str;
  regist(temp);
  fileSelf_.put('[');
  for (size_t i = 0; i < __size - 1; i++) {
    numToString(temp, __ptr[i]);
    for (size_t w = 0; w < temp.size(); w++) fileSelf_.put(temp[w]);
    fileSelf_.put(',');
  }
  numToString(temp, __ptr[__size - 1]);
  for (size_t w = 0; w < temp.size(); w++) fileSelf_.put(temp[w]);
  fileSelf_.put(']');
  return true;
}

class FileIOOrdered {
 public:
  // the mode of file item
  typedef enum IOMode {
    // idling, also the default mode
    idle,
    // reading, read from the file
    reading,
    // writing, write into the file
    writing,
    // end of file, when read to the end
    eof
  } Status;

 private:
  std::string fileName_;
  std::fstream fileSelf_;
  Status mode_;

 public:
  FileIOOrdered() noexcept;
  ~FileIOOrdered() noexcept;
  inline void setFile(const char* const&, const char* const&);
  inline bool switchMode(Status const&, bool const&) noexcept;
  // return the name of file
  inline std::string checkName() noexcept { return fileName_; }
  // retrun the mode now
  inline Status checkMode() noexcept { return mode_; }
  inline void print(std::ostream&) noexcept;
  template <typename T>
  inline bool read(T* const&, size_t const&);
  template <typename T>
  inline bool write(T* const&, size_t const&);
};
FileIOOrdered::FileIOOrdered() noexcept {
  LOG("C:constructor of FileIOOrdered");
  fileName_ = "";
  mode_ = idle;
  return;
}
FileIOOrdered::~FileIOOrdered() noexcept {
  LOG("C:destructor of FileIOOrdered");
  if (fileSelf_.is_open()) fileSelf_.close();
  return;
}
/**
 * @brief set the file
 * @param __file put __FILE__ define in here
 * @param __type the type of the file, "txt" is default
 */
inline void FileIOOrdered::setFile(const char* const& __file,
                                   const char* const& __type = "txt") {
  LOG("C:set file of FileIOOrdered");
  fileName_ = __file;
  fileName_.pop_back();
  fileName_.pop_back();
  fileName_ = fileName_.substr(fileName_.find_last_of('/'));
  fileName_.insert(0, "/../datas");
  fileName_.insert(0, std::filesystem::current_path().string());
  fileName_ += __type;
  DEBUG(fileName_);
  return;
}
/**
 * @brief switch mode in [idle,read,writing]
 * @param __obj mode you want
 * @return if the switch is successful, return true
 */
inline bool FileIOOrdered::switchMode(Status const& __obj = idle,
                                      bool const& __special = false) noexcept {
  LOG("C:switch mode of FileIOOrdered");
  if (__obj >= 3) {
    LOG("E:bad argument");
    return false;
  }
  if (mode_ == __obj) {
    LOG("E:same mode");
    return true;
  }
  if (fileSelf_.is_open()) fileSelf_.close();
  mode_ = __obj;
  if (__obj == idle) return true;
  if (__obj == reading) {
    fileSelf_.open(fileName_, std::ios::in | std::ios::binary);
    fileSelf_.seekg(0, std::ios::beg);
  } else if (__obj == writing) {
    if (__special) {
      fileSelf_.open(fileName_,
                     std::ios::out | std::ios::app | std::ios::binary);
    } else {
      fileSelf_.open(fileName_,
                     std::ios::out | std::ios::trunc | std::ios::binary);
      fileSelf_.seekp(0, std::ios::beg);
    }
  }
  if (!fileSelf_.is_open()) {
    mode_ = idle;
    LOG("E:open fail!");
    return false;
  }
  return true;
}
/**
 * @brief print the file status now
 * @param __os the stream, std::cout is default
 */
inline void FileIOOrdered::print(std::ostream& __os = std::cout) noexcept {
  LOG("C:print of FileIOOrdered");
  __os << "++++++++++\nfile name: " << fileName_ << "\nmode: ";
  if (mode_ == idle) {
    __os << "idle\n++++++++++\n";
  } else if (mode_ == reading) {
    __os << "reading\n++++++++++\n";
  } else if (mode_ == writing) {
    __os << "writing\n++++++++++\n";
  } else if (mode_ == eof) {
    __os << "read to end\n++++++++++\n";
  }
  return;
}
/**
 * @brief read datas from the file
 * @param __ptr the pointer of the datas buffer
 * @param __size how many datas you want read
 * @return true if the read is successful, false otherwise
 */
template <typename T>
inline bool FileIOOrdered::read(T* const& __ptr, size_t const& __size) {
  LOG("C:read of FileIOOrdered");
  if (mode_ != reading) {
    LOG("E:invalid way in mode\"%d\"", static_cast<int>(mode_));
    return false;
  }
  if (fileSelf_.eof()) {
    mode_ = eof;
    return false;
  }
  std::string temp;
  char c;
  do {
    fileSelf_.get(c);
    if (fileSelf_.eof()) {
      mode_ = eof;
      return false;
    }
  } while (c != '[');
  size_t i = 0;
  temp.clear();
  while ((!fileSelf_.eof()) && (i < __size)) {
    fileSelf_.get(c);
    if (isNumber(c)) {
      temp.push_back(c);
    } else {
      stringToNum(temp, __ptr[i]);
      temp.clear();
      i++;
      if (c == ']') break;
    }
  }
  if (fileSelf_.eof()) mode_ = eof;
  return true;
}
/**
 * @brief write datas into the file
 * @param __ptr the pointer of the datas buffer
 * @param __size how many datas you want write
 * @return true if the write is successful, false otherwise
 */
template <typename T>
inline bool FileIOOrdered::write(T* const& __ptr, size_t const& __size) {
  LOG("C:write of FileIOOrdered");
  if (mode_ != writing) {
    LOG("E:invalid way in mode\"%d\"", static_cast<int>(mode_));
    return false;
  }
  std::string temp;
  fileSelf_.put('[');
  for (size_t i = 0; i < __size - 1; i++) {
    numToString(temp, __ptr[i]);
    for (size_t w = 0; w < temp.size(); w++) fileSelf_.put(temp[w]);
    fileSelf_.put(',');
  }
  numToString(temp, __ptr[__size - 1]);
  for (size_t w = 0; w < temp.size(); w++) fileSelf_.put(temp[w]);
  fileSelf_.put(']');
  return true;
}
}  // namespace file_io
#endif