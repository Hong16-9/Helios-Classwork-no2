#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;
Mat src,srchsv,redtig,blucir;
Mat result;
int red_low_H = 0,red_high_H = 0;
int blue_low_H = 60,blue_high_H = 120;
void tiaotiao(int, void*)  
{  
    result = src.clone();
     
    Scalar lower_red = Scalar(red_low_H, 100, 100);  
    Scalar higher_red = Scalar(red_high_H, 255, 255);  
    inRange(srchsv, lower_red, higher_red, redtig);  
    vector<vector<cv::Point>> contours_red;  
    vector<Vec4i> hierarchy_red;  
    findContours(redtig, contours_red, hierarchy_red, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);  
    drawContours(result, contours_red, -1, Scalar(0, 255, 0), 2);  
    cout << "找到 " << contours_red.size() << " 个红色三角形轮廓" << std::endl;  

    Scalar lower_blue = Scalar(blue_low_H, 100, 100);  
    Scalar higher_blue = Scalar(blue_high_H, 255, 255);  
    inRange(srchsv, lower_blue, higher_blue, blucir);  
    vector<vector<cv::Point>> contours_blue;  
    vector<Vec4i> hierarchy_blue;  
    findContours(blucir, contours_blue, hierarchy_blue, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);  
    drawContours(result, contours_blue, -1, Scalar(0, 255, 0), 2);  
    cout << "找到 " << contours_blue.size() << " 个蓝色圆形轮廓" << std::endl;  

    for (const auto& contour : contours_red) {
        Rect boundingRect = cv::boundingRect(contour);
        rectangle(result, boundingRect, Scalar(255, 0, 0), 2);
        putText(result, "Redtriangle", Point(boundingRect.x, boundingRect.y - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 2);
    }
    for (const auto& contour : contours_blue) {
        Rect boundingRect = cv::boundingRect(contour);
        rectangle(result, boundingRect, Scalar(255, 0, 0), 2);
        putText(result, "Bluecircle", Point(boundingRect.x, boundingRect.y - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0), 2); 
    }
    imshow("Contours", result);  
}
int main()
{
    src = imread("/home/h16/1class/redtig.PNG") ;
    imshow("ceshi", src);
    cvtColor(src, srchsv, COLOR_BGR2HSV);
    result = src.clone();
    namedWindow("redttt");
    namedWindow("blueccc");
    namedWindow("Contours");
    createTrackbar("Low H", "redttt", &red_low_H, 179, tiaotiao);
    createTrackbar("High H", "redttt", &red_high_H, 179, tiaotiao);
    createTrackbar("Low H", "blueccc", &blue_low_H, 179, tiaotiao);
    createTrackbar("High H", "blueccc", &blue_high_H, 179, tiaotiao);    waitKey(0);
    return 0;
    
}