#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

std::vector<cv::Point2f> control_points;

void mouse_handler(int event, int x, int y, int flags, void *userdata) 
{
    if (event == cv::EVENT_LBUTTONDOWN) 
    {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", "
        << y << ")" << '\n';
        control_points.emplace_back(x, y);
    }
}

void naive_bezier(const std::vector<cv::Point2f> &points, cv::Mat &window) 
{
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) 
    {
        auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 +
                 3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;

        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

cv::Point2f recursive_bezier(const std::vector<cv::Point2f> &control_points, float t) 
{
    // TODO: Implement de Casteljau's algorithm
    std::vector<cv::Point2f> trans = control_points;
    int size = trans.size();
    while (size > 1)
    {
        std::vector<cv::Point2f> temp;
        temp.clear();
        for (int i = 0; i < size-1; ++i)
        {
            temp.push_back(cv::Point2f((1-t)*trans[i]+t*trans[i+1]));
        }
        trans = temp;
        size = trans.size();
    }
    return trans[0];

}

void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window) 
{
    // TODO: Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's 
    // recursive Bezier algorithm.
    for (double t = 0; t <= 1.0; t += 0.001)
    {
        cv::Point2f point_t = recursive_bezier(control_points,t);
        window.at<cv::Vec3b>(point_t.y,point_t.x)[1] =  255;
    }
}

void piecewise_bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window)
{
    int size = control_points.size();
    for (int i = 0; i < size ; i += 3)
    {
        std::vector<cv::Point2f> temp;
        temp.resize(4);
        if(i+4 >= size){
            temp.resize(control_points.end()-(control_points.begin()+i));
            std::copy(control_points.begin()+i,control_points.end(),temp.begin());
        }
        else{
            std::copy(control_points.begin()+i,control_points.begin()+i+4,temp.begin());
        }
        for (double t = 0; t <= 1.0; t += 0.001)
        {
            cv::Point2f point_t = recursive_bezier(temp,t);
            window.at<cv::Vec3b>(point_t.y,point_t.x)[2] =  255;
        }
    }
}

int main() 
{
    cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
    cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);

    int key = -1;
    while (key != 27) 
    {
        window = cv::Scalar(0);

        for (auto &point : control_points) 
        {
            cv::circle(window, point, 3, {255, 255, 255}, 3);
        }

        if (control_points.size() >= 3) 
        {
            //bezier(control_points, window);
            piecewise_bezier(control_points,window);
        }
        cv::imshow("Bezier Curve", window);
        key = cv::waitKey(20);
    }

return 0;
}
