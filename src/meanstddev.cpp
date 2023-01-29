#include <filesystem>
#include <opencv2/opencv.hpp>
#include <regex>
using namespace std;

int main() {
  // get *frame0000.jpg match files
  string dirname{"/home/mas/proj/sensyn-vision/data/powerlines/"};
  regex reg(".*frame0000.jpg$");
  smatch match;
  vector<string> imgnames{};

  for (const auto &file : filesystem::recursive_directory_iterator(dirname)) {
    string fname = file.path().string();
    if (regex_match(fname, match, reg)) {
      imgnames.push_back(match[0].str());
    }
  }

  // read images
  cv::Mat img;
  for (const auto &imgname : imgnames) {
    cout << imgname << endl;

    img = cv::imread(imgname, cv::IMREAD_GRAYSCALE);

    // display
    cv::imshow("input image", img);
    cv::waitKey(0);
  }
}
