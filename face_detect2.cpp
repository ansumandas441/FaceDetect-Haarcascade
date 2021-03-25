#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include<string>

using namespace cv;
using namespace std;

class faceObj{
	
	//private variuables
	private:
		
		string filename;
		Mat img;
		CascadeClassifier faceCascade;
		vector<Rect> faces;
	public:
		//constructor
		faceObj(string s, string s1){
			filename = s;
			img = imread(filename);
			//error handling
			try{
				faceCascade.load(s1);
				if(faceCascade.empty()){
					throw 404;
				}
			}catch(int num){
				cout<<"File not found.\n";
				cout << "Error number: " << num;
			}
			
		}
		
		//display image
		void disp(){
			imshow("Image",img);
			waitKey(0);
		}
		
		//detects face and make bounding box
		faceObj& detectFace(){
			
			
			faceCascade.detectMultiScale(img, faces, 1.1, 10);
			for(int i = 0; i < faces.size(); i++){
				rectangle(img, faces[i].tl(), faces[i].br(), Scalar(0,255,0), 4);
			}
			
			return *this;
		}
		
		
		//Tilts image by required angle
		faceObj& imgTilt(float angle){
			Point2f center((img.cols-1)/2.0, (img.rows-1)/2.0);
    			Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
    			Rect2f bbox = cv::RotatedRect(cv::Point2f(), img.size(), angle).boundingRect2f();
    			
    			rot.at<double>(0,2) += bbox.width/2.0 - img.cols/2.0;
    			rot.at<double>(1,2) += bbox.height/2.0 - img.rows/2.0;
    			Mat dst;
    			warpAffine(img, dst, rot, bbox.size());
    			imwrite("rotated_im.png", dst);
    			
    			return *this;
		}
		
		//Replaces pixel values
		faceObj& pixelReplace(){
			for(int y=0;y<img.rows;y++){
        			for(int x=0;x<img.cols;x++){
        				Vec3b color = img.at<Vec3b>(Point(x,y));
        				if(color[0] > 200 && color[0] < 255){
						color[0] = 0;
					}
					if(color[1] > 200 && color[1] < 255){
						color[1] = 255;
					}
					if(color[3] > 200 && color[3] < 255){
						color[3] = 0;
					}
					
					img.at<Vec3b>(Point(x,y)) = color;
        			
        			}}
			return *this;
		}
		

};


int main(int argc, char** argv){
	
	
	
	faceObj face(argv[1], argv[2]);
	face.pixelReplace().disp();
	face.detectFace().disp();
	face.detectFace().imgTilt(90);
	


}
