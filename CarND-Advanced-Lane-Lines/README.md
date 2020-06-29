# Advanced Lane Finding
[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)


In this project, the primary goal is to write a software pipeline to identify the lane boundaries in a video. This include detecting the lane lines, determining the curvature of the lane.

The goals / steps of this project are the following:

* Compute the camera calibration matrix and distortion coefficients given a set of chessboard images.
* Apply a distortion correction to raw images.
* Use color transforms, gradients, etc., to create a thresholded binary image.
* Apply a perspective transform to rectify binary image ("birds-eye view").
* Detect lane pixels and fit to find the lane boundary.
* Determine the curvature of the lane and vehicle position with respect to center.
* Warp the detected lane boundaries back onto the original image.
* Output visual display of the lane boundaries and numerical estimation of lane curvature and vehicle position.

The images for camera calibration are stored in the folder called `camera_cal`.  The images in `test_images` are for testing our pipeline on single frames.  If we want to extract more test images from the videos, we can simply use an image writing method like `cv2.imwrite()`, i.e., we can read the video in frame by frame as usual, and for frames we want to save for later you can write to an image file.  

To help the reviewer examine our work, please save examples of the output from each stage of our pipeline in the folder called `output_images`, and include a description in our writeup for the project of what each image shows. The video called `project_video.mp4` is the video our pipeline should work well on.  

The `challenge_video.mp4` video is an extra (and optional) challenge for us if we want to test your pipeline under somewhat trickier conditions.  The `harder_challenge.mp4` video is another optional challenge and is brutal!


## Installation:

Please refer to the "Installing Packages & Dependencies" section of the README.md file in [Finding Lane Lines](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/tree/master/CarND-LaneLines-P1) project that I completed prior to working on this one.

## Helper Functions:

Please note that I have used helper_functions.py file and imported the same in the jupyter notebook at the beginning. The brief description for each of the helper functions and its purpose/operation is stated in the same file with comments.


## Step 1: Compute the camera calibration matrix and distortion coefficients given a set of chessboard images.

The OpenCV functions cv2.findChessboardCorners() and cv2.drawChessboardCorners() are used for image calibration. We have 20 images of a chessboard, located in ./camera_cal, taken from different angles with the same camera, and we'll use them as input for camera calibration routine.

cv2.findChessboardCorners() attempts to determine whether the input image is a view of the chessboard pattern and locate the internal chessboard corners, and then cv2.drawChessboardCorners() draws individual chessboard corners detected.

Arrays of object points, corresponding to the location of internal corners of a chessboard, and image points, the pixel locations of the internal chessboard corners determined by cv2.findChessboardCorners(), are fed to cv2.drawChessboardCorners() which returns camera calibration and distortion coefficients.

These will then be used by the OpenCV cv2.calibrateCamera() to find the camera intrinsic and extrinsic parameters from several views of a calibration pattern. These parameters will be fed to cv2.undistort function to correct for distortion on any image produced by the same camera.

![step 1](img/step%201.JPG)


## Step 2: Apply a distortion correction to raw images.

OpenCV provides cv2.undistort function, which transforms an image to compensate for radial and tangential lens distortion.

![step 2](img/step%202.JPG)

The effect of undistort is particularly noticeable, by the change in shape of the car hood at the bottom corners of the image.

## Step 3: Use color transforms, gradients, etc., to create a thresholded binary image.

Next, we apply a Sobel filter in the X direction (on a grayscaled image) and apply thresholding to filter out pixels that aren't of interest. We also convert the RGB image to HLS color space and use the S channel to pick out lane lines.

![step 3](img/step%203.JPG)

## Step 4: Apply a perspective transform to rectify binary image ("birds-eye view").

A common task in autonomous driving is to convert the vehicle’s camera view of the scene into a top-down “birds-eye view". We'll use OpenCV's cv2.getPerspectiveTransform() and cv2.getPerspectiveTransform() to do this task.

![warped_straight_lines](img/warped_straight_lines.jpg)

Now, we will use color transform and Sobel differentiation to detect the lane lines in the image. 

![step 4](img/step%204.JPG)

## Step 5: Detect lane pixels and fit to find the lane boundary.

After applying calibration, thresholding, and a perspective transform to a road image, we should have a binary image where the lane lines stand out clearly. However, we still need to decide explicitly which pixels are part of the lines and which belong to the left line and which belong to the right line.

Sliding Window Search:
We'll compute a histogram of the bottom half of the image and find the base of the left and right lane lines. Originally these locations were identified from the local maxima of the left and right halves of the histogram, but in the final implementation we used quarters of the histogram just left and right of the midpoint. This helped to reject lines from adjacent lanes. The function identifies windows from which to identify lane pixels, each one centered on the midpoint of the pixels from the window below. This effectively "follows" the lane lines up to the top of the binary image, and speeds processing by only searching for activated pixels over a small portion of the image.

Polyfit Using Fit from Previous Frame:
The Polyfit Using Fit from Previous Frame is another way that performs basically the same task, but alleviates much difficulty of the search process by leveraging a previous fit (from a previous video frame, for example) and only searching for lane pixels within a certain range of that fit.

![step 5](img/step%205.JPG)

## Step 6: Determine the curvature of the lane and vehicle position with respect to center.

## Step 7: Warp the detected lane boundaries back onto the original image.

From these polynomials, we can convert to real space and determine the radius of curvature of the road and the position of the car within the lane with the code cell as shown in the jupyter notebook.

![step 6](img/steps%206%2C%207%2C%20%26%208.JPG)

## Step 8: Output visual display of the lane boundaries and numerical estimation of lane curvature and vehicle position.

Once the x positions of both of the lane are found, we can find a second degree polynomial fit on these positions, producing two functions in the form of Ay^2 + By + C for the two lanes.

The curvature of the lanes are calculated using the follow equation.

![radius_of_curvature](img/radius_of%20_curvature.jpg)

The A and B corresponds to the coefficients of the lane of fit of the lane. However, the result of the calculation will be in unit pixel, and we still need to convert to metric units.

To do this unit conversion, we can modify the coefficients of the lane of fit as follows:

Before:
    Ay^2 + By + C

After:
    mx/(my^ 2)Ay^2 + (mx/my)By + C
    
where mx and my corresponds to the ratio of pixels to meter in the x and y direction.

The distance that the car is away from the center of the lane is calculated by subtracting the center of the two lanes from the center of the image. The result is in unit pixels so we then multiply by the mx ratio mentioned above


## Results & Video Pipeline:

![final_result_demo](img/final_result_demo.gif)

**Please refer to [project_video_output](project_video_output.mp4) for the full video output**  

NOTE: Considering my concrete schedule, I haven't explored or given the "challenge_video" and "harder_challenge_video" a try. I'd greatly appreciate an opportunity to learn about the necessary 'functions' and 'hyperparameter tuning' to reduce the distortion and obtain an optimal solution for the challenge videos.  

## Discussion

- Both lane detection and vehicle detection depend on neural network models trained on 14 example images. These models are unlikely to work on roads with different lane appearances, or even on different car models. This could be fixed just by collecting images on which the models performed poorly, adding labels, and including these new images in the training set.

- The search algorithm for lane lines in this project assumes that the car is fairly close to the center of the lanes. That search algorithm would need to be modified to find lane lines in arbitrary positions with respect to the car.

- The perspective transformation assumes that the road is flat. That algorithm would not be useable on hills.

- There were some issues around the tree shadow which caused the algorithm to fail, so it appears the smart lane finding method was not working as inteded. Calculating and utilizing a moving average of the lane slope may be a good idea so that we can extrapolating from previous N frames rather than just the last one.

## Potential Improvements

- Other ways to improve the model include more dynamic thresholding, perhaps considering separate threshold parameters for different horizontal slices of the image, or dynamically selecting threshold parameters based on the resulting number of activated pixels, designating a confidence level for fits and rejecting new fits that deviate beyond a certain amount, or rejecting the right fit (for example) if the confidence in the left fit is high and right fit deviates too much (enforcing roughly parallel fits).

- A few placed involved hardcoding parameters (warp perspective, binary thresholding coefficients), these could be automated by using some form of optimizer based on the imput camera angles etc. Automating the binary threshold coefficients would lead to a much more robust lane finding algorithm in all terrains (snow, rain, etc.). Lastly, the smart line detection algorithm could use frames past the previous one to better extrapolate values for the current frame.

## References & Acknowledgement:
- [Demo video](https://www.youtube.com/watch?v=vWY8YUayf9Q&feature=youtu.be) with Q&A session by David Silver, Head of Self-Driving Cars at Udacity.  
- Course material & Quizzes from the "Advanced Lane Finding" part of this nanodegree.  
- Other relevant sources: (OpenCV Python Tutorial)[], Bogposts from [Medium](http://medium.com/), [OpenCV Tutorials](https://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_tutorials.html).  
- Stackoverflow and Stackexchange: The expert community groups and channels under [Stack Overflow](https://stackoverflow.com/) and [Stack Exchange](https://stackexchange.com/) has greatly helped me with optimal use of functions and debugging the code.  
