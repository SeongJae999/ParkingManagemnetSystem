#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "Parking.h"
#include "utils.h"
#include "ConfigLoad.h"

#define DETECT_PARKING true
#define SAVE_VIDEO false

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

	// 명령인수에 값이 제대로 있는지 확인
	if (argc != 3) {	
		printf("usage: DetectParking.exe <Video_Filename or Camera_Number> <ParkingData_Filename>\n\n");
		printf("<Camera_Number> can be 0, 1, ... for attached cameras\n");
		printf("<ParkingData_Filename> should be simple txt file with lines of: id x1 y1 x2 y2 x3 y3 x4 y4\n");
		return -1;
	}

	ConfigLoad::parse();

	const string videoFilename = argv[1];
	vector<Parking>  parking_data = parse_parking_file(argv[2]);
	const int delay = 1;

	// 비디오 파일이나 카메라 불러오기
	VideoCapture cap;
	if (videoFilename == "0" || videoFilename == "1" || videoFilename == "2") {
		printf("Loading Connected Camera...\n");
		cap.open(stoi(videoFilename));
		waitKey(500); // 키 입력 대기 시간
	}
	else {
		cap.open(videoFilename);
		//cap.set(cv::CAP_PROP_POS_FRAMES, 60000); // 프레임 바로 읽어 들이기
	}
	if (!cap.isOpened()) {
		cout << "Could not open: " << videoFilename << endl;
		return -1;
	}

	const unsigned long int total_frames = cap.get(CAP_PROP_FRAME_COUNT);
	Size videoSize = Size((int)cap.get(CAP_PROP_FRAME_WIDTH), (int)cap.get(CAP_PROP_FRAME_HEIGHT));

	// 인식된 영상 출력
	VideoWriter outputVideo;
	if (ConfigLoad::options["SAVE_VIDEO"] == "true") {
		string::size_type pAt = videoFilename.find_last_of('.');                 
		const string videoOutFilename = videoFilename.substr(0, pAt) + "_out.avi"; 
		//int ex = static_cast<int>(cap.get(CAP_PROP_FOURCC));    		
		//int fourcc = VideoWriter::fourcc('C', 'R', 'A', 'M');
		outputVideo.open(videoOutFilename, -1, cap.get(CAP_PROP_FPS), videoSize, true);
	}

	Mat frame, frame_blur, frame_gray, frame_out, roi, laplacian;
	Scalar delta, color;
	char c;
	ostringstream oss;
	Size blur_kernel = Size(3, 3);

	while (cap.isOpened()) {
		cap.read(frame);
		if (frame.empty()) {
			printf("Error reading frame\n");
			return -1;
		}
		double video_pos_msec = cap.get(CAP_PROP_POS_MSEC);
		double video_pos_frame = cap.get(CAP_PROP_POS_FRAMES);

		frame_out = frame.clone();
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
		GaussianBlur(frame_gray, frame_blur, blur_kernel, 1, 3);
		cout << ConfigLoad::options["DETECT_PARKING"];
		printf("\n");

		if (ConfigLoad::options["DETECT_PARKING"] == "true") {
			for (Parking& park : parking_data) {
				// 주차장 자리에 차량이 있는지 확인
				roi = frame_blur(park.getBoundingRect());
				Laplacian(roi, laplacian, CV_64F);
				delta = mean(abs(laplacian), park.getMask());
				park.setStatus(delta[0] < atof(ConfigLoad::options["PARK_LAPLACIAN_TH"].c_str()));
				printf("| %d: d=%-5.1f", park.getId(), delta[0]);
			}
			printf("\n");
		}
		// Parking Overlay
		for (Parking park : parking_data)
		{
			if (park.getStatus())  
				color = Scalar(0, 255, 0);
			else 
				color = Scalar(0, 0, 255);
			drawContours(frame_out, park.getContourPoints(), -1, color, 2, LINE_AA);

			// Parking ID overlay
		/*	cv::Point p = park.getCenterPoint();
			cv::putText(frame_out, to_string(park.getId()), cv::Point(p.x + 1, p.y + 1), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2, cv::LINE_AA);
			cv::putText(frame_out, to_string(park.getId()), cv::Point(p.x - 1, p.y - 1), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2, cv::LINE_AA);
			cv::putText(frame_out, to_string(park.getId()), cv::Point(p.x - 1, p.y + 1), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2, cv::LINE_AA);
			cv::putText(frame_out, to_string(park.getId()), cv::Point(p.x + 1, p.y - 1), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2, cv::LINE_AA);
			cv::putText(frame_out, to_string(park.getId()), p, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0), 2, cv::LINE_AA);
			*/
		}
		// Text Overlay		
		oss.str("");
		oss << (unsigned long int)video_pos_frame << "/" << total_frames;
		putText(frame_out, oss.str(), Point(5, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 255), 2, LINE_AA);

		// Save Video
		if (ConfigLoad::options["SAVE_VIDEO"] == "true")
			outputVideo.write(frame_out);

		// Show Video
		imshow("Video", frame_out);
		c = (char)cv::waitKey(delay);
		if (c == 27) break;
	}

	return 0;
}