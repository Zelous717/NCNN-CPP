#include <opencv2/opencv.hpp>
#include <net.h>
#include <iostream>

static void preprocess(const cv::Mat& img, ncnn::Mat& in) {
    int target_size = 640;
    int w = img.cols, h = img.rows;
    float scale = (w > h) ? (float)target_size / w : (float)target_size / h;
    w = (w > h) ? target_size : w * scale;
    h = (w > h) ? h * scale : target_size;
    ncnn::Mat in_pad = ncnn::Mat::from_pixels_resize(img.data, ncnn::Mat::PIXEL_BGR2RGB, img.cols, img.rows, w, h);
    int wpad = target_size - w, hpad = target_size - h;
    ncnn::copy_make_border(in_pad, in, hpad / 2, hpad - hpad / 2, wpad / 2, wpad - wpad / 2, ncnn::BORDER_CONSTANT, 114.f);
    const float norm_vals[3] = {1 / 255.f, 1 / 255.f, 1 / 255.f};
    in.substract_mean_normalize(0, norm_vals);
}

int main(int argc, char** argv) {
    ncnn::Net yolov8;
    yolov8.load_param(argv[1]);
    yolov8.load_model(argv[2]);
    cv::Mat img = cv::imread(argv[3]);
    
    ncnn::Mat in; 
    preprocess(img, in);
    
    ncnn::Extractor ex = yolov8.create_extractor();
    ex.input("in0", in); // 修改1：输入层名字改为 in0
    
    ncnn::Mat out; 
    ex.extract("out0", out); // 修改2：输出层名字改为 out0
    
    std::cout << "Model inference successful! Output shape: w=" << out.w << ", h=" << out.h << ", c=" << out.c << std::endl;

    // 画一个测试框，证明图被读取了
    cv::rectangle(img, cv::Rect(50, 50, 200, 200), cv::Scalar(0, 255, 0), 2);
    cv::putText(img, "C++ NCNN YOLOv8 Ready!", cv::Point(50, 40), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
    
    // 修改3：不用 imshow 弹窗了，直接保存成图片文件
    cv::imwrite("result.jpg", img);
    std::cout << "Result saved to result.jpg" << std::endl;

    return 0;
}
