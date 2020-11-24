#include "utils.h"

// *******************************************************
// * 주차 데이터로 텍스트 파일 구문 분석
// * 텍스트 파일의 각 줄 형식 :
// *   id x1 y1 x2 y2 x3 y3 x4 y4
// *******************************************************
vector<Parking> parse_parking_file(string filename) {
	fstream infile(filename);
	string line;
	vector<Parking> parkings;

	while (getline(infile, line)) {
		Parking park;
		vector<Point> points;
		istringstream iss(line);
		int id, x1, y1, x2, y2, x3, y3, x4, y4;

		if (!(iss >> id >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4))
			break; 
																				
		points.push_back(Point(x1, y1));
		points.push_back(Point(x2, y2));
		points.push_back(Point(x3, y3));
		points.push_back(Point(x4, y4));
		park.setId(id);
		park.setPoints(points);
		park.calcBoundingRect();
		parkings.push_back(park);
	}
	return parkings;
}

vector<Parking> parse_parking_file2(string filename) {
	fstream infile(filename);
	string line;
	vector<Parking> parkings;

	while (getline(infile, line)) {
		Parking park;
		vector<Point> points;
		istringstream iss(line);
		int id, x1, y1, x2, y2, x3, y3, x4, y4;

		if (!(iss >> id >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4))
			break;

		points.push_back(Point(x1, y1));
		points.push_back(Point(x2, y2));
		points.push_back(Point(x3, y3));
		points.push_back(Point(x4, y4));
		park.setPoints2(points);
		parkings.push_back(park);
	}
	return parkings;
}