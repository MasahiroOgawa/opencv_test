#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int main(int argc, char **argv) {
  // create 2 rects
  cv::Rect rect1{0, 0, 200, 200};
  cv::Rect rect2{10, 10, 20, 20};

  // check inside or not.
  if ((rect2 & rect1) == rect2) {
    cout << "rect2 is in rect1.\n";
  } else {
    cout << "rect 2 is not inside rect1.\n";
  }

  return 0;
}
