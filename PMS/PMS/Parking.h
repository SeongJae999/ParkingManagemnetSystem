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
	vector<vector<Point>> contours_points;
	vector<vector<Point>> contours_points2;
	vector<Point> polygon_points_in_bounding_rect;
	Rect bounding_rect;  // pre-calculated bounding_rect, to cut the ROI
	bool occupied;
	Mat mask;  // mask of polygon in bounding_rect coordinates
public:
	Parking();
	void setStatus(bool status);
	bool getStatus(void);
	void setId(int n);
	int getId(void);
	void setPoints(vector<Point> points);
	void setPoints2(vector<Point> points);
	vector<vector<Point>> getContourPoints(void);
	vector<vector<Point>> getContourPoints2(void);
	void calcBoundingRect(void);
	Rect getBoundingRect(void);
	Mat getMask(void);
	Point getCenterPoint(void);
};