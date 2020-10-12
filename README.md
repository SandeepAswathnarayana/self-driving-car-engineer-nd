# Self-Driving Car Engineering  


**Note To Readers**:  
- Please find the **'System Integration and Programming a Real Self-Driving Car'** Final Capstone on my **[GitHub repository](https://github.com/SandeepAswathnarayana/Udacity-SDCND-Programming-a-Real-Self-Driving-Car)**.  
- A comprehensive explanation and instructions on how to modify the code to build and deploy your own custom object detection model is available on my **[Medium article](https://towardsdatascience.com/how-to-build-a-custom-object-detector-classifier-using-tensorflow-object-detection-api-811b7bcd31c4)**.  
- Given the time constraint and my concrete schedule, I have given my best to learn and build the modules in an attempt to implent working prototypes and models. After having completed the SDC Nanodegree, I have kept my learning appetite active by: (a) working towards applying the state-of-the-art models and (b) following the works of some of the smartest minds in the field. I have only been strengthening my intuition based on Innovation ever since.  
- The projects wouldn't have been possible without the: insightful videos on concepts by the Instructors, inputs from the mentors, constant interaction with the peers/community, and my persevered efforts to overcome botttlenecks & failed attempts while implementing the code.  
- Should you have any inputs that you want to share with me (or) provide me with any relevant feedback on my projects or approach, I’d be glad to hear from you. Please feel free to connect with me on **[Twitter](https://twitter.com/ThisIsSandeepA)**, **[LinkedIn](https://www.linkedin.com/in/sandeep-a/)**, or follow me on **[GitHub](https://github.com/SandeepAswathnarayana)**.  


# Core Project Ideas in SDC Nanodegree  
Computer Vision  
Deep Learning  
Sensor Fusion 
Localization & Mapping  
Path Planning  
Control  
System Integration  


# Brief Overview of the Projects  
### (1). COMPUTER VISION  
In this module, I used a combination of cameras and software to find lane lines on difficult roads and to track vehicles.  

Project 1: [**Finding Lane Lines on the Road**](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/tree/master/CarND-LaneLines-P1)  
In this project, I wrote code to identify lane lines on the road, first in an image, and later in a video stream. To complete this project I used Python, OpenCV and other tools I learned about in the Computer Vision course lessons and later built upon them.  
![solid white lane](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/blob/master/CarND-LaneLines-P1/GIFs/output_solidWhiteRight.gif)  

Project 2: [**Advanced Lane Finding**](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/tree/master/CarND-Advanced-Lane-Lines)  
Building on the previous project, I accomplished my goal of writing a software pipeline to identify the lane boundaries in a video from a front-facing camera on a car. The output annotated video identifies: the positions of the lane lines, the location of the vehicle relative to the center of the lane, the radius of curvature of the road.  
![final_result_demo](img/final_result_demo.gif)  


### (2). DEEP LEARNING  
Deep learning is the most important frontier in both machine learning and autonomous vehicle development. I learned from Experts from NVIDIA to build deep neural networks and train them with data from the real world and from the Udacity simulator. Later, I trained convolutional neural networks to classify traffic signs, and then trained a neural network to drive a vehicle in the simulator.  

Project 3: [**Traffic Sign Classifier**](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/tree/master/CarND-Traffic-Sign-Classifier-Project)  
I built a Convolutional Neural Network in TensorFlow to classify traffic sign images from the German Traffic Sign Dataset. I designed and implemented the model architecture for LeNet-5 and VGGNet to train the model and reached an accuracy of >95% on the validation set.  

Project 4: [**Behavioral Cloning**](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/tree/master/CarND-Behavioral-Cloning-P3)  
I trained a deep neural network built using TensorFlow's Keras API to clone the human steering behavior while driving, thus being able to drive autonomously on a simulator provided by Udacity. The neural network's input includes the dataset generated from Udacity's Self-Driving Car Simulator, images taken from three different camera angles (Left, Center & Right), steering angle, throttle, brake, and speed during each frame. The neural network is based on NVIDIA's 'End to End Learning for Self-Driving Cars' paper, which has been proven to work in this problem domain.  


### (3). SENSOR FUSION  
Tracking objects over time is a major challenge for understanding the environment surrounding a vehicle. It was a pleasure learning from Sensor fusion engineers from Mercedes-Benz to program fundamental mathematical tools called Kalman filters. I used these filters to predict and determine with certainty the location of other vehicles on the road. Also, I used an advanced technique called Extended Klaman Filter to do the same with difficult-to-follow objects.  

Project 5: [**Extended Kalman Filter**](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/tree/master/CarND-Extended-Kalman-Filter-Project)  
Kalman Filter is a mathematical approach of determining the state of the system and it clarifies the state using the measurement information. In this project, I implemented an Extended Kalman Filter (EKF) using the Constant Velocity (CV) model in C++ to fuse together data from RADAR and LIDAR. I tracked a bicycle's (that travels around the car) position & velocity using noisy LIDAR and RADAR measurements.  


### (4). LOCALIZATION  
Localization is how we determine where our vehicle is in the world. GPS is only accurate to within a few meters. I applied the technique used by Mercedes-Benz engineers in achieving single-digit centimeter-level accuracy. So, I applied the principles of Markov localization to program a particle filter, which uses data and a map to determine the precise location of a vehicle.  

Project 6: [**Kidnapped Vehicle**](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/tree/master/CarND-Kidnapped-Vehicle-Project)  
In this project, I built a particle filter and combined it with a map to localize a vehicle. To do so, I implemented a 2-dimensional particle filter in C++. Using the particle filter's map, observation data, control data, initial localization information (analogous to what a GPS would provide), I implemented and coded a particle filter that localizes the vehicle within the desired accuracy making sure the particle ran within the specified time of 100 seconds.  


### (5). PLANNING  
To implement this phase, I went through the three stages of planning with the help of the Mercedes-Benz team. First, I applied model-driven and data-driven approaches to predict how other vehicles on the road will behave. Then, I constructed a finite state machine to decide which of several maneuvers my own vehicle should undertake. Finally, I generated a safe and comfortable trajectory to execute that maneuver.  

Project 7: [**Highway Driving**](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/tree/master/CarND-Path-Planning-Project)  
I implemented the code for the Path Planning algorithm which is considered to be the 'cognitive system' of an autonomous vehicle. I designed a planner that is able to create smooth, safe paths for the car to navigate through traffic on a three-lane highway. To do so, I designed a path planner module which is able to drive a car around a virtual 3 lane highway with a lot of traffic around. By coding the modules, I made sure the car drove at least one complete round of about 4.32 miles in a highway loop with a length of 6952m, changed lanes to pass slower moving traffic, never collided with other vehicles. I met the requiremenets of trying to get the car as close to the speed limit of 50mph as possible, while still not exceeding this speed limit. To meet the smooth and safe acceleration for the comfort of the passengers, I made sure the car doesn't exceed a maximum acceleration of 10m/s² and a jerk of 10m/s³.  


### (6). CONTROL  
This includes sending steering, acceleration, and brake commands to move the car through the world. Uber ATG walked me through building a proportional-integral-derivative (PID) controller to actuate the vehicle. A Proportional–Integral–Derivative (PID) Controller is one of the most common control loop feedback mechanisms. A PID controller continuously calculates an error function (which in our case is the distance from the center of the lane) and applies a correction based on these P, I, and D terms.  

Project 8: [**PID Controller**](https://github.com/SandeepAswathnarayana/self-driving-car-engineer-nd/tree/master/CarND-PID-Control-Project)  
I implemented a PID controller to steer the self driving car around the track in Udacity's Simulator. I built the PID controller in C++ based on Udacity's starter code and made sure to keep the car on the lake race track by appropriately adjusting the steering angle to maneuver the vehicle around the track. I computed the appropriate steering angle using the simulator's Cross Track Error (CTE) and the Velocity (mph). Also, driving the car safely with a desired speed by controlling the throttle.  


### (7). SYSTEM INTEGRATION  
This is the capstone of the entire Self-Driving Car Engineer Nanodegree Program! I worked on implementing and running my code on Carla, the Udacity self-driving car, and the Robot Operating System that controls her. I worked with a team of Nanodegree students to combine what I’ve learned over the course of the entire Nanodegree Program to drive Carla, a real self-driving car, around the Udacity test track.  

Project 9: [**Programming a Real Self-Driving Car**](https://github.com/SandeepAswathnarayana/Udacity-SDCND-Programming-a-Real-Self-Driving-Car)  
I initiated this Final System Integration project and spearheaded a team of 4 where we worked on the integration of Carla's 4 major subsystems including SENSOR, PERCEPTION, PLANNING, and CONTROL. We built ROS nodes to implement the core functionality of the autonomous vehicle system, including traffic light detection, traffic light classification, throttle, drive-by-wire, vehicle control, and waypoint following. This software system will be deployed on Carla (Udacity’s Self Driving Lincoln MKZ) to autonomously drive it around a test track meeting all the requitements.  



Please note that this repository is still under development. Any potential improvements or iterations would be added in the future.  
