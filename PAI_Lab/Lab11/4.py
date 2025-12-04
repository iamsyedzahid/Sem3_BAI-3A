import cv2
import numpy as np

image_path = 'image.jpg' 
img = cv2.imread(image_path)

if img is not None:
    text = "Loaded Image Example"
    org = (50, 50)
    font = cv2.FONT_HERSHEY_SIMPLEX
    fontScale = 1
    color = (255, 255, 255)
    thickness = 2
    
    cv2.putText(img, text, org, font, fontScale, color, thickness, cv2.LINE_AA)
    cv2.imshow('Text on Loaded Image', img)

width, height = 600, 200
blank_img_text = 255 * np.ones((height, width, 3), dtype=np.uint8)

text_blank = "Hello OpenCV!"
org_blank = (50, 100)
font_blank = cv2.FONT_HERSHEY_COMPLEX
fontScale_blank = 1.5
color_blank = (0, 100, 0)
thickness_blank = 3

cv2.putText(blank_img_text, text_blank, org_blank, font_blank, fontScale_blank, color_blank, thickness_blank, cv2.LINE_AA)
cv2.imshow('Text on Blank Image', blank_img_text)

cv2.waitKey(0)
cv2.destroyAllWindows()
