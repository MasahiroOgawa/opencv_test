#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  // print usage
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " image_directory_name\n";
    return 1;
  }

  // constants
  const bool read_recursive{true};
  const double thre{20};
  const double inimg_reduce_britness{0.2}; // should be (0,1).
  const double img_resize_ratio{0.2};      //

  // read images
  vector<string> fnames;
  cv::glob(string(argv[1]) + "/*", fnames, read_recursive);

  // proces images
  for (auto fname : fnames) {
    // binarize
    cv::Mat in_img = cv::imread(fname, cv::IMREAD_GRAYSCALE);
    cv::Mat out_img = in_img.clone();
    cv::threshold(out_img, out_img, thre, 255, cv::THRESH_BINARY_INV);

    // overlay for output
    out_img += in_img * inimg_reduce_britness;
    cout << "outimg type=" << out_img.type() << endl; // 16 means CV_8UC3.

    // save image
    cv::imwrite(
        string(basename(fname.substr(0, fname.find_last_of(".")).c_str())) +
            "_extractbrack.jpg",
        out_img);

    // display
    cv::resize(in_img, in_img, cv::Size(), img_resize_ratio, img_resize_ratio);
    cv::resize(out_img, out_img, cv::Size(), img_resize_ratio,
               img_resize_ratio);
    cv::imshow("src", in_img);
    cv::imshow("result", out_img);
    cv::waitKey(0);
  }

  return 0;
}
