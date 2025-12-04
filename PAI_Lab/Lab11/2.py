import cv2
import numpy as np

width, height = 500, 500
blank_img = np.zeros((height, width, 3), dtype=np.uint8)

cv2.rectangle(blank_img, (50, 50), (200, 200), (0, 255, 0), 3)
cv2.rectangle(blank_img, (250, 250), (450, 400), (0, 0, 255), -1)

cv2.circle(blank_img, (125, 350), 75, (255, 0, 0), -1)

cv2.imshow('Shapes on Blank Image', blank_img)
cv2.waitKey(0)
cv2.destroyAllWindows()
