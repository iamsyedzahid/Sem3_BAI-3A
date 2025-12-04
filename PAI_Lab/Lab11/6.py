import cv2

image_path1 = 'image.jpg' 
image_path2 = 'image2.jpg' 
img1 = cv2.imread(image_path1)
img2 = cv2.imread(image_path2)

if img1 is not None and img2 is not None:
    img2 = cv2.resize(img2, (img1.shape[1], img1.shape[0])) 
    
    alpha = 0.7 
    beta = 1.0 - alpha
    blended_img = cv2.addWeighted(img1, alpha, img2, beta, 0)
    cv2.imshow('Blended Image', blended_img)
    
    gray_blended = cv2.cvtColor(blended_img, cv2.COLOR_BGR2GRAY)
    cv2.imshow('Grayscale Blended', gray_blended)
    
    equalized_img = cv2.equalizeHist(gray_blended)
    cv2.imshow('Equalized Contrast', equalized_img)
    
    cv2.waitKey(0)
    cv2.destroyAllWindows()
