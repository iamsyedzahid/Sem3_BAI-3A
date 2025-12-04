import cv2

image_path = 'image.jpg' 
img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)

if img is not None:
    cv2.imshow('Grayscale Image', img)
    
    threshold_value = 127
    max_value = 255
    _, binary_img = cv2.threshold(img, threshold_value, max_value, cv2.THRESH_BINARY)
    cv2.imshow('Binary Thresholded Image', binary_img)
    
    (h, w) = img.shape[:2]
    center = (w // 2, h // 2)
    angle = 60.0
    scale = 1.0
    
    M = cv2.getRotationMatrix2D(center, angle, scale)
    
    rotated_img = cv2.warpAffine(binary_img, M, (w, h))
    cv2.imshow('Rotated Binary Image', rotated_img)
    
    cv2.waitKey(0)
    cv2.destroyAllWindows()
