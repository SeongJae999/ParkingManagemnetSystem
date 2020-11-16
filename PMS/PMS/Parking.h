#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Parking
{
private:
	int id;
	vector<vector<cv::Point>> contours_points;
	vector<cv::Point> polygon_points_in_bounding_rect;
	Rect bounding_rect;  // pre-calculated bounding_rect, to cut the ROI
	bool occupied;
	Mat mask;  // mask of polygon in bounding_rect coordinates
public:
	Parking();
	void setStatus(bool status);
	bool getStatus(void);
	void setId(int n);
	int getId(void);
	void setPoints(vector<cv::Point> points);
	vector<vector<cv::Point>> getContourPoints(void);
	void calcBoundingRect(void);
	Rect getBoundingRect(void);
	Mat getMask(void);
	Point getCenterPoint(void);
};