import cv2

image_path = 'image.jpg' 
img = cv2.imread(image_path)

if img is not None:
    blurred_img = cv2.GaussianBlur(img, (5, 5), 0)
    cv2.imshow('Blurred Image', blurred_img)
    
    height, width, _ = img.shape
    crop_end_row = height // 2
    crop_end_col = width // 2
    
    cropped_img = img[0:crop_end_row, 0:crop_end_col]
    cv2.imshow('Cropped Image', cropped_img)
    
    cv2.waitKey(0)
    cv2.destroyAllWindows()
