#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/superres.hpp>

using namespace std;
using namespace cv;

void drawFlow(const cv::Mat &flow, const int rows, const int cols,
              cv::Mat &flow_img) {
  flow_img = cv::Mat(rows, cols, CV_8UC3, Scalar(0, 0, 0));
  for (int i = 0; i < flow_img.rows; i += 5) {
    for (int j = 0; j < flow_img.cols; j += 5) {
      Point2f flow_at_point = flow.at<Point2f>(i, j);
      arrowedLine(
          flow_img, Point(j, i),
          Point(cvRound(j + flow_at_point.x), cvRound(i + flow_at_point.y)),
          Scalar(0, 255, 0), 1, 8, 0, 0.1);
    }
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " input_videoname" << endl;
    return -1;
  }
  // Open the video file
  VideoCapture cap(argv[1]);
  if (!cap.isOpened()) {
    cerr << "Failed to open the video file" << endl;
    return -1;
  }

  // Initialize the background image and the foreground mask
  Mat background, foreground;
  cap.read(background);
  foreground = cv::Mat::zeros(background.size(), CV_8UC1);

  // Initialize the optical flow algorithm
  Ptr<superres::DenseOpticalFlowExt> opticalFlow =
      cv::superres::createOptFlow_DualTVL1();

  // Process the remaining frames
  Mat frame, motionVectors, magnitude, mask;
  while (cap.read(frame)) {
    // Apply the optical flow algorithm to get the motion vectors
    opticalFlow->calc(background, frame, motionVectors);

    // Calculate the magnitude of the motion vectors
    magnitude = cv::Mat::zeros(frame.size(), CV_16UC1);
    for (int i = 0; i < magnitude.rows; i++) {
      for (int j = 0; j < magnitude.cols; j++) {
        float x = motionVectors.at<Vec2f>(i, j)[0];
        float y = motionVectors.at<Vec2f>(i, j)[1];
        magnitude.at<unsigned short>(i, j) = sqrt(x * x + y * y);
      }
    }

    // Threshold the magnitude to get the moving object mask
    // threshold 25.0 will be ignored when I use THRESH_OTSU.
    threshold(magnitude, mask, 25.0, 255.0, THRESH_BINARY + THRESH_OTSU);
    mask.convertTo(mask, CV_8UC1);

    // Apply morphology to remove small noise and fill holes
    morphologyEx(mask, mask, MORPH_OPEN,
                 getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    morphologyEx(mask, mask, MORPH_CLOSE,
                 getStructuringElement(MORPH_ELLIPSE, Size(15, 15)));

    // Update the foreground mask by ORing it with the current mask
    bitwise_or(foreground, mask, foreground);

    // create optical flow image
    cv::Mat flow_img;
    drawFlow(motionVectors, foreground.rows, foreground.cols, flow_img);

    // Show the original frame and the moving object mask
    imshow("Original Frame", frame);
    imshow("Moving Object Mask", foreground);
    imshow("optical flow", flow_img);

    // Update the background image by blending it with the current frame
    addWeighted(background, 0.95, frame, 0.05, 0.0, background);

    // Wait for a key press to continue
    if (waitKey(1) == 27) // Escape key
    {
      break;
    }
  }

  // Release the video file and close all windows
  cap.release();
  destroyAllWindows();

  return 0;
}
