
import cv2
import numpy as np
import sys

class faceObj:
	
	#private variuables
	__filename = None
	__img = None
	__faceCascade = None
	__faces = None
	
	def __init__(self, s, s1):
		
		self.__filename = s
		self.__img = cv2.imread(self.__filename)
		self.__face_cascade = cv2.CascadeClassifier(s1)
		
	#display image
	def disp(self):
		
		cv2.imshow("Image",self.__img)
		cv2.waitKey(0)
		
	#detects face and make bounding box
	def detectFace(self):
			
		faces = self.__face_cascade.detectMultiScale(self.__img, 1.1, 10)
		
		for (x,y,w,h) in faces:
			print(x,y,w,h)
			self.__img = cv2.rectangle(self.__img,(x,y),(x+w,y+h),(255,0,0),2)
			
			
		return self
	#Tilts image by required angle
	def imgTilt(self, angle):
		
		image_center = tuple(np.array(self.__img.shape[1::-1]) / 2)
		rot_mat = cv2.getRotationMatrix2D(image_center, angle, 1.0)
		self.__img = cv2.warpAffine(self.__img, rot_mat, self.__img.shape[1::-1], flags=cv2.INTER_LINEAR)
		
		
		cv2.imwrite("result1.png",self.__img)
    			
		return self
		
    	#Replaces pixel values
	def pixelReplace(self):
		
    	
		for i in range(self.__img.shape[0]):
			for j in range(self.__img.shape[1]):
			
				if(self.__img[i,j,0]<255 and self.__img[i,j,0]>200):
					self.__img[i,j,0]=0
				if(self.__img[i,j,1]<255 and self.__img[i,j,1]>200):
					self.__img[i,j,1]=255
				if(self.__img[i,j,2]<255 and self.__img[i,j,2]>200):
					self.__img[i,j,0]=0
    		
			
		return self
		
		
				

if(__name__=="__main__"):
	
	
	print(sys.argv[1],sys.argv[2])
	a = faceObj(sys.argv[1], sys.argv[2])
	a.detectFace().disp()
	a.imgTilt(90).disp()
	a.pixelReplace().disp()
	
	#print(a.getWordCount())

		
	
