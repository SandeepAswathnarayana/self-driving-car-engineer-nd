

## Market and Leading Tech companies in Autonomous Driving  
**Leading SDC Companies**: Google, Mercedes, BMW, Toyota, Ford, GM, Nissan  
Tier-1 Suppliers: Bosch, Continental AG, Aptiv, Mobileye,  
Chip companies: Nvidia, Intel,  
Ride sharing companies: Didi, Uber, Udacity, Lyft,  

## Core Project Ideas in SDC Nanodegree:  
Deep Learning, Sensor Fusion, Localization & Mapping, Controls, Path Planning, Systems Integration.  
These core principles extend into other industries: Robotics, Smart Buildings, IOTs, Medical Devices, Hardware Monitors, Intelligent Hospitals,  




### Core Project Ideas in SDC Nanodegree:  
Computer Vision, Deep Learning, Sensor Fusion, Localization & Mapping, Controls, Path Planning, Systems Integration.  


### Brief Overview:  

(1). COMPUTER VISION  
Using a combination of cameras and software to find lane lines on difficult roads and to track vehicles.  

Project 1: **Finding Lane Lines on the Road**  
In this project, I wrote code to identify lane lines on the road, first in an image, and later in a video stream. To complete this project I used Python, OpenCV and other tools I learned about in the Computer Vision course lessons and built upon them.  

Project 2: **Advanced Lane Finding**  
Building on the previous project, I accomplished my goal of writing a software pipeline to identify the lane boundaries in a video from a front-facing camera on a car. The output annotated video identifies: the positions of the lane lines, the location of the vehicle relative to the center of the lane, the radius of curvature of the road.  


(2). DEEP LEARNING  
Deep learning is the most important frontier in both machine learning and autonomous vehicle development. I learned from Experts from NVIDIA to build deep neural networks and train them with data from the real world and from the Udacity simulator. Later, I trained convolutional neural networks to classify traffic signs, and then trained a neural network to drive a vehicle in the simulator!  

Project 3: **Traffic Sign Classifier**  
In this project, you will use what you've learned about deep neural networks and convolutional neural networks to classify traffic signs.  

Project 4: **Behavioral Cloning**  
Using the deep learning skills I gained from the course modules and coding-quizzes, I trained a deep neural network to drive a car like a human does!  

(3). SENSOR FUSION  
Tracking objects over time is a major challenge for understanding the environment surrounding a vehicle. It was a pleasure learning from Sensor fusion engineers from Mercedes-Benz to program fundamental mathematical tools called Kalman filters. I used these filters to predict and determine with certainty the location of other vehicles on the road. Also, I used an advanced technique called Extended Klaman Filter to do the same with difficult-to-follow objects.  

Project 5: **Extended Kalman Filter**  
I implemented an Extended Kalman Filter (EKF) using the Constant Velocity (CV) model in C++ to fuse together data from RADAR and LIDAR. I tracked a bicycle's (that travels around the car) position & velocity using noisy LIDAR and RADAR measurements.  

(4). LOCALIZATION  
Localization is how we determine where our vehicle is in the world. GPS is only accurate to within a few meters. I applied the technique used by Mercedes-Benz engineers in achieving single-digit centimeter-level accuracy. So, I applied the principles of Markov localization to program a particle filter, which uses data and a map to determine the precise location of a vehicle.  

Project 6: **Kidnapped Vehicle**  
In this project, I built a particle filter and combined it with a map to localize a vehicle. To do so, I implemented a 2 dimensional particle filter in C++. Using the particle filter's map, observation data, control data, initial localization information (analogous to what a GPS would provide), I implemented and coded a particle filter that localizes the vehicle within the desired accuracy making sure the particle ran within the specified time of 100 seconds.  

(5). PLANNING  
To implement this phase, I went through the three stages of planning with the help of the Mercedes-Benz team. First, I applied model-driven and data-driven approaches to predict how other vehicles on the road will behave. Then, I constructed a finite state machine to decide which of several maneuvers your own vehicle should undertake. Finally, I generated a safe and comfortable trajectory to execute that maneuver.  

Project 7: **Highway Driving**  
I implemented the code for the Path Planning algorithm which considered to be the 'cognitive system' of an autonomous vehicle. I designed a planner that is able to create smooth, safe paths for the car to navigate through traffic on a three-lane highway. To do so, I designed a path planner module which is able to drive a car around a virtual 3 lane highway with a lot of traffic around. By coding the modules, I made sure the car drove at least one complete round of about 4.32 miles in a highway loop with a length of 6946m, changed lanes to pass slower moving traffic, never collided with other vehicles. I met the rqquiremenets of trying to get the car as close to the speed limit of 50mph as possible, but not exceeding this speed limit. To meet the smooth and safe acceleration for the comfort of a passenger, I made sure the car doesn't exceed a maximal acceleration of 10m/s² and a jerk of 10m/s³.  




