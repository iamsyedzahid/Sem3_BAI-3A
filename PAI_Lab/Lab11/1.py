import cv2

image_path = 'image.jpg'
img = cv2.imread(image_path)

if img is not None:
    cv2.imshow('Original Image', img)
    
    gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    cv2.imshow('Grayscale Image', gray_img)
    
    new_width = 300
    new_height = 200
    resized_img = cv2.resize(img, (new_width, new_height))
    cv2.imshow('Resized Image', resized_img)
    
    cv2.waitKey(0)
    cv2.destroyAllWindows()
