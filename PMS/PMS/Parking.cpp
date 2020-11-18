#include "Parking.h"

Parking::Parking() {
	id = -1;
	occupied = false;
}

void Parking::setStatus(bool status) {
	occupied = status;
}

bool Parking::getStatus() {
	return occupied;
}

void Parking::setId(int n) {
	id = n;
}

int Parking::getId() {
	return id;
}

void Parking::setPoints(vector<Point> points) {
	vector<vector<Point>> contours;
	contours.push_back(points);
	contours_points = contours;
}

vector<vector<Point>> Parking::getContourPoints() {
	return contours_points;
}

void Parking::calcBoundingRect() {
	if (!contours_points.empty()) {
		bounding_rect = boundingRect(contours_points.at(0));
		// Create a mask for contour, to mask out that region from roi.
		mask = Mat::zeros(bounding_rect.size(), CV_8UC1);
		for (Point p : contours_points.at(0))
			polygon_points_in_bounding_rect.push_back(Point(p.x - bounding_rect.x, p.y - bounding_rect.y));
		vector<vector<Point>> contours;
		contours.push_back(polygon_points_in_bounding_rect);
		drawContours(mask, contours, -1, Scalar(255), FILLED);
	}
	else
		throw logic_error("Cannot calculate boundingRect when polygon_points are empty");
}

Rect Parking::getBoundingRect() {
	return bounding_rect;
}

Mat Parking::getMask() {
	return mask;
}

Point Parking::getCenterPoint() {
	Point center = Point((2 * bounding_rect.x + bounding_rect.width) / 2, (2 * bounding_rect.y + bounding_rect.height) / 2);
	return center;
}