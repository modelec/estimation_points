//
// Created by BreizhHardware on 23/04/2024.
//

#ifndef MYCLIENT_H
#define MYCLIENT_H
#pragma once

#include <TCPSocket/TCPClient.hpp>
#include <TCPSocket/TCPUtils.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

enum ArucoTagType
{
    FLOWER,
    SOLAR_PANEL
};

class ArucoTag {
    int id;
    std::string name;
    float length;
    cv::Mat objectRepresenation;
    ArucoTagType type;
    std::vector<std::pair<ArucoTag, std::pair<cv::Mat, cv::Mat>>> arucoTags;
    ArucoTag(const int id, std::string name, const float length, const ArucoTagType type) : id(id), name(std::move(name)), length(length), type(type)
    {
        this->objectRepresenation = cv::Mat(4, 1, CV_32FC3);
        this->objectRepresenation.ptr<cv::Vec3f>(0)[0] = cv::Vec3f(-length/2.f, length/2.f, 0);
        this->objectRepresenation.ptr<cv::Vec3f>(0)[1] = cv::Vec3f(length/2.f, length/2.f, 0);
        this->objectRepresenation.ptr<cv::Vec3f>(0)[2] = cv::Vec3f(length/2.f, -length/2.f, 0);
        this->objectRepresenation.ptr<cv::Vec3f>(0)[3] = cv::Vec3f(-length/2.f, -length/2.f, 0);
    }
};

class MyClient : public TCPClient {
protected:
    int points;

public:

    ~MyClient() override;

    explicit MyClient(const char* ip = "127.0.0.1", const int &port = 8080);

    void handleMessage(const std::string &message) override;

    int getPoints() const;

    void setPoints(const int &points);

};

#endif //MYCLIENT_H
