#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

char grayscaleToAscii(int grayscaleValue) {
    const std::string asciiChars = "@#8&$%*o!;:. ";
    int index = (grayscaleValue * (asciiChars.length() - 1)) / 255;
    return asciiChars[index];
}

int main() {
    std::string url = "https://i.pinimg.com/originals/77/5f/e9/775fe9b8114aa96c0994246cc899da1c.jpg"; 

    cv::VideoCapture cap(url);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    cv::Mat image;
    cap.read(image);

    if (image.empty()) {
        std::cerr << "Error: Could not read the image from URL!" << std::endl;
        return -1;
    }

    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);

    cv::Mat resizedImage;
    int newWidth = 100;
    double aspectRatio = static_cast<double>(image.cols) / image.rows;
    int newHeight = static_cast<int>((newWidth / aspectRatio) * 0.5);
    cv::resize(image, resizedImage, cv::Size(newWidth, newHeight));

    std::vector<std::string> asciiArt;
    asciiArt.reserve(resizedImage.rows);
    for (int y = 0; y < resizedImage.rows; ++y) {
        std::string line;
        line.reserve(resizedImage.cols);
        for (int x = 0; x < resizedImage.cols; ++x) {
            int pixelValue = resizedImage.at<uchar>(y, x);
            line += grayscaleToAscii(pixelValue);
        }
        asciiArt.push_back(std::move(line));
    }

    for (const std::string& line : asciiArt) {
        std::cout << line << std::endl;
    }

    return 0;
}
