# :oncoming_automobile: 주차 관리 시스템 PMS 
![image.png](attachment:cb2288c2-048b-4865-8607-a2fb1a2f459a:image.png)

# 프로젝트 소개 
* PMS(ParkingManagementSystem)은 주차장에 진입하기전에 미리 주차 공간을 확인할 수 있도록 개발된 시스템입니다.
* 초록색 테두리와 빨간색 테두리로 주차 가능 공간을 구분할 수 있습니다.
  
# 기술 스택
* C++
  * 윈도우 응용 프로그램의 통합 개발 환경인 마이크로소프트 비주얼 C++에 부속되는 클래스 라이브러리인 MFC(Microsoft Foundation Class Libary)을 활용해 클라이언트의 주차 공간 확인을 위함
  * python에 비해 복잡하나 실행속도가 빠르며 이후에 시스템 규모가 커졌을 경우를 고려해 대규모 데이터 처리에서 성능적인 면에서 우위이기 때문에 C++ 채택
* OpenCV
  * 핵심 MVP인 주차장 CCTV를 통한 여유 공간 확인을 위함
  * 오픈소스이지만 BSD(Berkely Software Distribution) 라이선스를 따르기 때문에 추후에 시스템 규모가 확장되었을 경우에 상업적 목적으로도 활용될 수 있는 점을 고려

# 프로젝트 구조
```
📦PMS
 ┣ 📂.vs
 ┣ 📂.vscode
 ┣ 📂CMakeFiles
 ┣ 📂Debug
 ┣ 📂models
 ┃ ┣ 📜ConfigLoad.cpp
 ┃ ┣ 📜ConfigLoad.h
 ┃ ┣ 📜Parking.cpp
 ┃ ┣ 📜Parking.h
 ┃ ┣ 📜resource.h
 ┃ ┣ 📜utils.cpp
 ┃ ┗ 📜utils.h
 ┣ 📂utils
 ┃ ┣ 📜Parking lot.png
 ┃ ┣ 📜parkinglot_1.txt
 ┃ ┣ 📜parkinglot_2.txt
 ┃ ┗ 📜parking_video.mp4
 ┣ 📂x64
 ┣ 📜CMakeCache.txt
 ┣ 📜CMakeLists.txt
 ┣ 📜config.cfg
 ┣ 📜libmysql.dll
 ┣ 📜main.cpp
 ┣ 📜PMS.APS
 ┣ 📜PMS.rc
 ┣ 📜PMS.sln
 ┣ 📜PMS.vcxproj
 ┣ 📜PMS.vcxproj.filters
 ┗ 📜PMS.vcxproj.user
```
