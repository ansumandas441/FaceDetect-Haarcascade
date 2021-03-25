This a basic application of Haarcascade classifier for recognizing faces in opencv4
You need to compile opencv4 to run these files



For face_detect.cppxample usage in commandline:
	g++ face_detect2.cpp -o output `pkg-config --cflags --libs opencv4`
	./output face2.png haarcascade_frontalface_default1.xml
	
For face_detect.py usage in commandline usage:

	python /home/ansuman/cpp_test/face_detector_py/face2.png haarcascade_frontalface_default1.xml

*Need to compile opencv correctly otherwise the libraries will not be recognised by face_detect.cpp	
