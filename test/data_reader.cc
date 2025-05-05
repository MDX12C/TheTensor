#include "interface.hpp"

//==================================================
// this is the file that read and pre-dealing mnist
//==================================================

namespace data_reader_cc {
constexpr size_t LENTH = 28 * 28;
constexpr size_t OUT = 10;
constexpr size_t TRAIN_PCS = 60000;
constexpr size_t TEST_PCS = 10000;
}  // namespace data_reader_cc
namespace drcc = data_reader_cc;
signed main() {
  CONSTRUCT;
  // check for mnist file
  system_message::Status::refresh("check for mnist file");
  system_message::Status::print();
  auto stringBuffer = new char[512];
  std::string fileFolder = "/../datas/mnist";
  fileFolder = std::filesystem::current_path().string() + fileFolder;
  std::cout << "fileFolder is: " << fileFolder << '\n';
  auto file = mnist::read_dataset(fileFolder);
  std::cout << "lenth per images:\n" << file.training_images[0].size() << '\n';
  std::cout << "training images:\n" << file.training_images.size() << " pcs\n";
  std::cout << "training labels:\n" << file.training_labels.size() << " pcs\n";
  std::cout << "test images:\n" << file.test_images.size() << " pcs\n";
  std::cout << "test labels:\n" << file.test_labels.size() << " pcs\n";
  // ask user to write
  [] {
    char c;
    std::cout << "\nSure to write file? (y/n)\n";
    std::cin.get(c);
    std::cin.get();
    if (c != 'y') endOfMainFunction();
  }();
  // setting before write
  lina_lg::VectorF temp(drcc::LENTH);
  size_t pcs = 0;
  file_io::FileIOOrdered writingFile;
  auto ioFunc = [](const char* const& __str) -> size_t {
    std::cout << "===\nNow write the " << __str << ", how many?\n";
    int alpha;
    std::cin >> alpha;
    std::cin.get();
    std::cout << "===\n";
    return static_cast<size_t>(alpha);
  };
  auto imgFunc = [&](std::vector<uint8_t>& __vec) {
    temp.resize(__vec.size());
    for (size_t i = 0; i < __vec.size(); i++)
      temp[i] = static_cast<FloatType>(__vec[i]);
    temp /= 25.0F;
    temp -= (temp.sum() / temp.size());
    auto sigma = (basic_math::pow(temp, FloatType(2)).sum()) / temp.size();
    temp /= std::sqrt(sigma);
  };
  auto lbFunc = [&](uint8_t const& __pos) {
    temp = static_cast<FloatType>(0);
    temp[static_cast<size_t>(__pos)] = static_cast<FloatType>(1);
  };
  system_message::Status::refresh("write training files");
  system_message::Status::print();
  // write [train images]
  writingFile.setFile("/mnist.", "train_images");
  writingFile.switchMode(file_io::FileIOOrdered::writing);
  do {
    pcs = std::min(drcc::TRAIN_PCS, ioFunc("training images"));
  } while (!pcs);
  system_message::Status::announce("train images");
  for (size_t times = 0; times < pcs; times++) {
    sprintf(stringBuffer, "train images [%5ld,%5ld]", times + 1, pcs);
    system_message::Status::bar(times, pcs, stringBuffer);
    imgFunc(file.training_images[times]);
    if (!writingFile.write(temp.begin(), drcc::LENTH)) endOfMainFunction();
  }
  system_message::Status::bar(1, 1, stringBuffer);
  std::cout << '\n';
  writingFile.switchMode();
  // write [train labels]
  temp.resize(drcc::OUT);
  writingFile.setFile("/mnist.", "train_labels");
  writingFile.switchMode(file_io::FileIOOrdered::writing);
  system_message::Status::announce("train labels");
  for (size_t times = 0; times < pcs; times++) {
    sprintf(stringBuffer, "train labers [%5ld,%5ld]", times + 1, pcs);
    system_message::Status::bar(times, pcs, stringBuffer);
    lbFunc(file.training_labels[times]);
    if (!writingFile.write(temp.begin(), drcc::OUT)) endOfMainFunction();
  }
  system_message::Status::bar(1, 1, stringBuffer);
  std::cout << '\n';
  writingFile.switchMode();
  // ask user to add test part
  [] {
    char c;
    std::cout << "\nAdd test part? (y/n)\n";
    std::cin.get(c);
    std::cin.get();
    if (c != 'y') endOfMainFunction();
  }();
  // write [test images]
  system_message::Status::refresh("write testing files");
  system_message::Status::print();
  pcs = 0;
  temp.resize(drcc::LENTH);
  writingFile.setFile("/mnist.", "test_images");
  writingFile.switchMode(file_io::FileIOOrdered::writing);
  do {
    pcs = std::min(drcc::TEST_PCS, ioFunc("test_images"));
  } while (!pcs);
  system_message::Status::announce("test images");
  for (size_t times = 0; times < pcs; times++) {
    sprintf(stringBuffer, "test images [%5ld,%5ld]", times + 1, pcs);
    system_message::Status::bar(times, pcs, stringBuffer);
    imgFunc(file.test_images[times]);
    if (!writingFile.write(temp.begin(), drcc::LENTH)) endOfMainFunction();
  }
  system_message::Status::bar(1, 1, stringBuffer);
  std::cout << '\n';
  writingFile.switchMode();
  // write [test labels]
  temp.resize(drcc::OUT);
  writingFile.setFile("/mnist.", "test_labels");
  writingFile.switchMode(file_io::FileIOOrdered::writing);
  system_message::Status::announce("test labels");
  for (size_t times = 0; times < pcs; times++) {
    sprintf(stringBuffer, "test labels [%5ld,%5ld]", times + 1, pcs);
    system_message::Status::bar(times, pcs, stringBuffer);
    lbFunc(file.test_labels[times]);
    if (!writingFile.write(temp.begin(), drcc::OUT)) endOfMainFunction();
  }
  system_message::Status::bar(1, 1, stringBuffer);
  std::cout << '\n';
  writingFile.switchMode();
  delete[] stringBuffer;
  DESTRUCT;
  return 0;
}