import chili_tag_detector as ctd
import cv2
import numpy as np

video_capture = 0
cap = cv2.VideoCapture(video_capture)

while (cap.isOpened()):
    ret, img = cap.read()
    if ret == True:
       tag_list = ctd.detect(img)
       for tag in tag_list: 
           points = tag[1]
           cv2.line(img, tuple(points[0]), tuple(points[1]), [0, 0, 255])
           cv2.line(img, tuple(points[1]), tuple(points[2]), [0, 0, 255])
           cv2.line(img, tuple(points[2]), tuple(points[3]), [0, 0, 255])
           cv2.line(img, tuple(points[3]), tuple(points[0]), [0, 0, 255])
           cv2.putText(img, str(tag[0]), tuple(np.mean(points, 0)), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 255), 2, cv2.LINE_AA)
       cv2.imshow('ChiliTagLiveDetection', img)
       if cv2.waitKey(1) & 0xFF == ord('q'):
           break

