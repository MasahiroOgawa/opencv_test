#include <iostream>
#include <thread>
#include <filesystem>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>


/// paralllel_for wrapper
/// @param st start indexstd::filesystem::current_path()
/// @param ed end index
/// @param func function to be executed in parallel
/// @ref https://qiita.com/luftfararen/items/ceaa97241e9c80a73246
template<class FUNC>
void parallel_for_idx(int st, int ed, FUNC func)
{
  int   num_cpu = std::thread::hardware_concurrency();
  int nstripes = (ed - st + num_cpu -1) / num_cpu;
  cv::parallel_for_(cv::Range(st, ed),
                    [&func](const cv::Range& range) {
    for(int idx = range.start; idx < range.end; idx++) {
      func(idx);
    }
  },nstripes);
}

int main(){
    // for vector calculation
    std::vector<int> square(101);

    parallel_for_idx(0, 101, [&](int idx){
        square[idx] = idx * idx;
    });

    for(auto i : square){
        std::cout << i << std::endl;
    }

    //for image calculation
    // currently jpeg file (including lena.jpg) doesn't works.
    cv::Mat src_img = cv::imread("../data/lena.png");
    if(src_img.empty()){
        std::cout << "current directory =" << std::filesystem::current_path() << std::endl;
        std::cout << "Failed to open image file." << std::endl;
        return -1;
    }
    // cv::Mat3b dst_img(src_img.size(), src_img.type());

    // parallel_for_idx(0, src_img.rows, [&](int y){
    //     for(int x=0; x<src_img.cols; ++x){
    //         dst_img(y,x) = src_img(y,x) * 0.5;
    //     }
    // });

    cv::imshow("src", src_img);
    // cv::imshow("dst", dst_img);
    cv::waitKey(0);

}