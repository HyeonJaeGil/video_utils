#! /usr/bin/python

# import argparse
import cv2

def get_pixel(event, x, y, flags, param):
    if event == cv2.EVENT_FLAG_LBUTTON:
        print(f'{x}, {y}')

img = cv2.imread("/home/hj/Dropbox/dataset/warehouse/210624/rgb/1624516958.683195.png")
clone = img.copy()
cv2.namedWindow("image")
cv2.setMouseCallback("image", get_pixel)

while True:
	cv2.imshow("image", img)
	key = cv2.waitKey(1) & 0xFF

	# if the 'r' key is pressed, reset the cropping region
	if key == ord("r"):
		img = clone.copy()

	# if the 'c' key or esc are pressed, break from the loop
	elif key == ord("q") or key == 27:
		break

cv2.destroyAllWindows()
