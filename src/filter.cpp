#include <iostream>
#include <opencv2/imgproc.hpp>

using namespace std;

int main() {
  // create input
  cv::Matx33f in_mat{1, 0, 0, 0, 0, 0, 0, 0, 0};
  //  cv::Matx33f filter{0, 1, 2, 3, 4, 5, 6, 7, 80};
  //  cv::Matx22f filter{0, 1, 2, 3};
  cv::Matx23f filter{10, 1, 2, 3, 4, 5};

  // process
  cv::Matx33f out_mat{};
  int ddepth{-1}; // negative means the depth is the same with the source.
  cv::filter2D(in_mat, out_mat, ddepth, filter);

  // check the result
  cout << "in_mat=" << in_mat << endl;
  cout << "filter=" << filter << endl;
  cout << "out_mat=" << out_mat << endl;
  cout << out_mat << endl;

  return 0;
}
