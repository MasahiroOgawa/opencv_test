#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  // print usage
  if (argc < 1) {
    cout << "Usage: " << argv[0] << "\n";
    return 1;
  }

  // read an image
  std::string fname = "../data/lena.jpg";

  // proces images
  cv::Mat in_img = cv::imread(fname, cv::IMREAD_GRAYSCALE);
  cv::Mat out_img = in_img.clone();
  out_img /= 255.0;

  // check
  double min, max;
  cv::minMaxLoc(out_img, &min, &max);
  cout << "out min=" << min << ", out max = " << max << endl;

  // save image
  cv::imwrite("processed_lena.jpg", out_img);

  // display
  cv::imshow("src", in_img);
  cv::imshow("result", out_img);
  cv::waitKey(0);

  return 0;
}
