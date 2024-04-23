//
// Created by BreizhHardware on 23/04/2024.
//

#include "MyClient.h"

MyClient::~MyClient() {
    this -> stop();
}

MyClient::MyClient(const char* ip, const int &port) : TCPClient(ip, port), points(0) {

}

void MyClient::handleMessage(const std::string&message) {
    std::vector<std::string> messageSplited = TCPSocket::split(message, ";");
    if (messageSplited[1] == "point" || messageSplited[1] == "all") {
        if (messageSplited[2] == "ping") {
            this->sendMessage("point;ihm;pong;1");
        }
    }
    if(messageSplited[0] == "aruco") {
        if(messageSplited[1] == "strat") {
            if(messageSplited[2] == "get aruco") {
                if(messageSplited[3] == "404") {
                    return;
                }
                else {
                    for (auto& [tag, pos] : arucoTags) {
                        double firstMatrixElement = pos.first.at<double>(2, 0);

                        double secondMatrixElement0 = pos.second.at<double>(0, 0);
                        double secondMatrixElement1 = pos.second.at<double>(1, 0);
                        double secondMatrixElement2 = pos.second.at<double>(2, 0);

                        // Check if the tag is in the depot area
                        if (firstMatrixElement < 0.5) {
                            if (secondMatrixElement0 > 0.5 && secondMatrixElement0 < 1.5) {
                                if (secondMatrixElement1 > 0.5 && secondMatrixElement1 < 1.5) {
                                    if (secondMatrixElement2 > 0.5 && secondMatrixElement2 < 1.5) {
                                        // The tag is in the depot area so add 1 point
                                        this->setPoints(this->getPoints() + 1);
                                        // Send the new points to the IHM
                                        this->sendMessage("point;ihm;update;" + std::to_string(this->getPoints()));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int MyClient::getPoints() const {
    return this->points;
}

void MyClient::setPoints(const int &points) {
    this->points = points;
}
