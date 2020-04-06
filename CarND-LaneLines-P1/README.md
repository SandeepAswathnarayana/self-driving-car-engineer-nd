# **Finding Lane Lines on the Road** 
[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

<img src="examples/laneLines_thirdPass.jpg" width="480" alt="Combined Image" />

Overview
---

When we drive, we use our eyes to decide where to go.  The lines on the road that show us where the lanes are act as our constant reference for where to steer the vehicle.  Naturally, one of the first things we would like to do in developing a self-driving car is to automatically detect lane lines using an algorithm.

In this project you will detect lane lines in images using Python and OpenCV.  OpenCV means "Open-Source Computer Vision", which is a package that has many useful tools for analyzing images.  

Solution Pipeline Overview
---
![Solution Pipeline Overview](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/blob/master/CarND-LaneLines-P1/img/solution%20pipeline%20overview.png)  
1. ### **Grayscaling**: We process the image or frame within the video by changing colorful image into grayscale. Each pixel can be represented with single 8-bit number (0~255).  

![grayscale](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/blob/master/CarND-LaneLines-P1/results/solution%20pipeline%20output/grayscale/output_solidWhiteCurve.jpg)  


2. **Gaussian Blurring**: To avoid sharp change in the image, we use Gaussian blurring in this project. We do so to avoid noise because we need to detect edge in next step. Smoothing can significantly improve the accuracy of edge detection later.  

![gaussian blur](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/blob/master/CarND-LaneLines-P1/results/solution%20pipeline%20output/gaussian%20blur/output_solidWhiteCurve.jpg)  


3. **Canny Edge Detection**: The lane line has different color from its neighboring region. It is quite natural to detect edges in the image, which are more likely to be the lane lines. Here we use classic Canny Edge Detection.  

![canny](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/blob/master/CarND-LaneLines-P1/results/solution%20pipeline%20output/canny/output_solidWhiteCurve.jpg)  


4. **Finding the Region of Interest**: There are too many edges found from previous step. To narrow down to region that more likely have lane line, we need to restrict our search within more small portion of the image, which is called region of interest. Similar to cropping the photos on our smartphones.  

![region of interest](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/blob/master/CarND-LaneLines-P1/results/solution%20pipeline%20output/region%20of%20interest/output_solidWhiteCurve.jpg)  


5. **Hough Line Transform**: Previous step generates many points consisting of edges. To detect continuous lane line, we need to find a line from these points. The most classic approach is to use Hough Transfrom and find intersection of different curves in Hough Space.  

![Hough Line Transform](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/blob/master/CarND-LaneLines-P1/img/hough%20line%20transform.jpg)  

![hough transform](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/blob/master/CarND-LaneLines-P1/results/solution%20pipeline%20output/hough%20transform/output_solidWhiteCurve.jpg)  


6. **Extrapolating the left & right lane lines**: A continuous line like Y = a*X + b comprises of two components:
slope of the line: coefficient “a”
intercept of the line: coefficient “b”
Using these two parameters, we can find the top and bottom points on the line, so we can draw them on the image. Here, we use left line as an example, but the same holds true for the right line except its slope has opposite sign.
A brief illustration of this step:
- Pre-Processing: we start with a bunch of segments from Hough Transform, and calculate slope of each segment (shown as directed blue line in the below): positive slope means the segment belongs to left line, while negative slope means right line. Meanwhile, we can find the minimum Y-coordinate of all points on both lines ( “minY” as shown with the dashed red line in the middle of image as below).
- Avgerage Slope: starting from a bunch of segments with , we can calculate the slope of each segment. Then average value of them is the average slope of this lane line, that is the coefficient “a” in Y = a*X + b.
- Average Position: we can compute the average value of X and Y coordinate of all points in the line, which determines the average position of this lane line( as shown with Yellow Dot in the below.)
Here, using avg. slope “a”, we can easily calculate coefficient “b” using average position (avg_x, avg_y) as: b = avg_y -a*avg_x
- Determine the Top and Bottom Position: in order to draw lane line on the image, we need to know the start and end points. We call them top and bottom points in the image since the line is vertical.
top_x = (minY -b)/a <note: minY is the minimum Y value of all points>
bottom_x=(maxY -b)/a = (image.shape[0] -b)/a
As such, we can draw left lane line between points:
(top_x, minY) and (bottom_x, maxY)  

![Extrapolation of lane lines](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/blob/master/CarND-LaneLines-P1/img/extrapolating%20lines.png)  

![draw lines](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/blob/master/CarND-LaneLines-P1/results/output_solidWhiteCurve.jpg)  


The Project
---

## If you have already installed the [CarND Term1 Starter Kit](https://github.com/udacity/CarND-Term1-Starter-Kit/blob/master/README.md) you should be good to go!   If not, you should install the starter kit to get started on this project. ##

**Step 1:** Set up the [CarND Term1 Starter Kit](https://github.com/udacity/CarND-Term1-Starter-Kit/blob/master/README.md) if you haven't already.

**Step 2:** Open the code in a Jupyter Notebook

You will complete the project code in a Jupyter notebook.  If you are unfamiliar with Jupyter Notebooks, check out [Udacity's free course on Anaconda and Jupyter Notebooks](https://classroom.udacity.com/courses/ud1111) to get started.

Jupyter is an Ipython notebook where you can run blocks of code and see results interactively.  All the code for this project is contained in a Jupyter notebook. To start Jupyter in your browser, use terminal to navigate to your project directory and then run the following command at the terminal prompt (be sure you've activated your Python 3 carnd-term1 environment as described in the [CarND Term1 Starter Kit](https://github.com/udacity/CarND-Term1-Starter-Kit/blob/master/README.md) installation instructions!):

`> jupyter notebook`

A browser window will appear showing the contents of the current directory.  Click on the file called "P1.ipynb".  Another browser window will appear displaying the notebook.  Follow the instructions in the notebook to complete the project.  

**Step 3:** Complete the project and submit both the Ipython notebook and the project writeup

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

