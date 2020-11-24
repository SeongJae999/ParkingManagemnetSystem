#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "Parking.h"

using namespace std;

// 주차 데이터로 텍스트 파일 구문 분석
vector<Parking> parse_parking_file(string filename);

vector<Parking> parse_parking_file2(string filename);