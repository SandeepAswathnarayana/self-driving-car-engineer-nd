/*
 * particle_filter.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: Tiffany Huang
 */

#include <random>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <math.h> 
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>

#include "particle_filter.h"

using namespace std;

static const int NUM_PARTICLES = 125;
static default_random_engine gen;

void ParticleFilter::init(double x, double y, double theta, double std[]) {
	// TODO: Set the number of particles. Initialize all particles to first position (based on estimates of 
	//   x, y, theta and their uncertainties from GPS) and all weights to 1. 
	// Add random Gaussian noise to each particle.
	// NOTE: Consult particle_filter.h for more information about this method (and others in this file).
	num_particles = NUM_PARTICLES;

	// Allocate the vectors
	particles.reserve(num_particles);
	weights.reserve(num_particles);

	// Setting standard deviations for x, y, and theta.
	double std_x = std[0];
	double std_y = std[1];
	double std_theta = std[2];
	
	// A normal (Gaussian) distribution for x, y and theta.
	normal_distribution<double> dist_x(x, std_x);
	normal_distribution<double> dist_y(y, std_y);
	normal_distribution<double> dist_theta(theta, std_theta);

	for (int i = 0; i < num_particles; ++i) {
		Particle p;
		p.id = i;
		// Sampling from the normal distribution
		p.x = dist_x(gen);
		p.y = dist_y(gen);
		p.theta = dist_theta(gen);
		p.weight = 1.0;

		weights.push_back(1.0);
		particles.push_back(p);
	}
	is_initialized = true;
}


void ParticleFilter::prediction(double delta_t, double std_pos[], double velocity, double yaw_rate) {
	// TODO: Add measurements to each particle and add random Gaussian noise.
	// NOTE: When adding noise std::normal_distribution and std::default_random_engine are useful.
	//  http://en.cppreference.com/w/cpp/numeric/random/normal_distribution
	//  http://www.cplusplus.com/reference/random/default_random_engine/

	// Initialize measurement noise
	normal_distribution<double> noise_x(0, std_pos[0]);
	normal_distribution<double> noise_y(0, std_pos[1]);
	normal_distribution<double> noise_theta(0, std_pos[2]);

	for (int i=0; i<num_particles; ++i) {
		if (fabs(yaw_rate) < 0.00001) { // if yaw rate is zero
			particles[i].x += velocity * delta_t * cos(particles[i].theta);
			particles[i].y += velocity * delta_t * sin(particles[i].theta);
		}
		else {
			double delta_theta = yaw_rate * delta_t;
			particles[i].x += velocity / yaw_rate * (sin(particles[i].theta + delta_theta) - sin(particles[i].theta));
			particles[i].y += velocity / yaw_rate * (cos(particles[i].theta) - cos(particles[i].theta + delta_theta));
			particles[i].theta += delta_theta;
		}
		// add noise
		particles[i].x += noise_x(gen);
		particles[i].y += noise_y(gen);
		particles[i].theta += noise_theta(gen);
	}
}


void ParticleFilter::dataAssociation(std::vector<LandmarkObs> predicted, std::vector<LandmarkObs>& observations) {
	// TODO: Find the predicted measurement that is closest to each observed measurement and assign the 
	//   observed measurement to this particular landmark.
	// NOTE: this method will NOT be called by the grading code. But you will probably find it useful to 
	//   implement this method and use it as a helper during the updateWeights phase.
	for (int i=0; i<observations.size(); ++i) {
		// Initialize distance buffer to maximum 
		double min_dist = numeric_limits<double>::max();
		int lm_id = -1; // initialize default landmark id
		for (int j=0; j<predicted.size(); ++j) {
			// Calculate the distance between the current landmark and prediction
			double cur_dist = dist(observations[i].x, observations[i].y, predicted[j].x, predicted[j].y);
			if (cur_dist < min_dist) {
				min_dist = cur_dist;
				lm_id = predicted[j].id;
			}
		}
		observations[i].id = lm_id;
	}
}

void ParticleFilter::updateWeights(double sensor_range, double std_landmark[], 
		const std::vector<LandmarkObs> &observations, const Map &map_landmarks) {
	// TODO: Update the weights of each particle using a mult-variate Gaussian distribution. You can read
	//   more about this distribution here: https://en.wikipedia.org/wiki/Multivariate_normal_distribution
	// NOTE: The observations are given in the VEHICLE'S coordinate system. Your particles are located
	//   according to the MAP'S coordinate system. You will need to transform between the two systems.
	//   Keep in mind that this transformation requires both rotation AND translation (but no scaling).
	//   The following is a good resource for the theory:
	//   https://www.willamette.edu/~gorr/classes/GeneralGraphics/Transforms/transforms2d.htm
	//   and the following is a good resource for the actual equation to implement (look at equation 
	//   3.33
	//   http://planning.cs.uiuc.edu/node99.html

	// Precalculate constants
	const double X_STD = std_landmark[0];
	const double Y_STD = std_landmark[1];
	const double X_VAR = X_STD * X_STD;
	const double Y_VAR = Y_STD * Y_STD;
	const double GAUSSIAN_NORMALIZER = 2 * M_PI * X_STD * Y_STD;

	for (int i=0; i<particles.size(); ++i) {
		
		Particle p = particles[i];
		
		/* 
		 * Part A: Transform landmark observations from car coord -> map coord
		 */
		// Declare a new vector for the transformed observation
		std::vector<LandmarkObs> observations_trans;
		// Reserve memory since we know how many observations prior
		observations_trans.reserve(observations.size());
		for (int j=0; j<observations.size(); ++j) {
			LandmarkObs obs = observations[j];
			double x_trans = cos(p.theta) * obs.x - sin(p.theta) * obs.y + p.x;
			double y_trans = sin(p.theta) * obs.x + cos(p.theta) * obs.y + p.y;
			observations_trans.push_back({ obs.id, x_trans, y_trans }); //shortcut to initialize LandmarkObs struct
		}
		
		/* 
		 * Part B: Select landmarks within the sensor_range from the particle
		 */
		std::vector<LandmarkObs> predictions;
		for (int k=0; k<map_landmarks.landmark_list.size(); ++k) {
			double landmark_x = map_landmarks.landmark_list[k].x_f;
			double landmark_y = map_landmarks.landmark_list[k].y_f;
			int landmark_id = map_landmarks.landmark_list[k].id_i;
			// we can either consider a circular (dist methdo) or rectangular range 
			// (x, y comparsion) around each particle
			if (fabs(landmark_x - p.x) <= sensor_range && fabs(landmark_y - p.y) <= sensor_range) {
				predictions.push_back(LandmarkObs{ landmark_id, landmark_x, landmark_y }); // Another way to initialize a struct
			}
		}
		
		/* 
		 * Part C: Find the closest pair of landmark and its observation.
		 */
		dataAssociation(predictions, observations_trans); 
		// Observation id now should be reassigned to the closest landmark's id.
		
		/* 
		 * Part D: Update weights of each particle w/ multvariate Gaussian distribution
		 */
		for (int m=0; m<observations_trans.size(); ++m) {
			LandmarkObs obs = observations_trans[m];
			if (obs.id == -1) { // if no landmark is associated with the observation, 0 the weight.
				particles[i].weight = 0;
				break;
			}
			else {
				// We assume that the map's vector is indexed by landmark's id
				Map::single_landmark_s lm = map_landmarks.landmark_list[obs.id - 1]; //map id is not 0 indexed.
				double x_2 = pow(obs.x - lm.x_f, 2);
				double y_2 = pow(obs.y - lm.y_f, 2);
				double gaussian_exp = exp( -(x_2 / (2 * X_VAR) + y_2 / (2 * Y_VAR)) );
				double weight = gaussian_exp / GAUSSIAN_NORMALIZER;
				particles[i].weight *= weight; // scaling weights by multiplying
			}
		}
		weights[particles[i].id] = particles[i].weight;
	}
}

void ParticleFilter::resample() {
	// TODO: Resample particles with replacement with probability proportional to their weight. 
	// NOTE: You may find std::discrete_distribution helpful here.
	//   http://en.cppreference.com/w/cpp/numeric/random/discrete_distribution

	vector<Particle> resampled;
	resampled.reserve(num_particles); // pre-allocate memory for the vector
	
	discrete_distribution<int> dist(weights.begin(), weights.end());
	for (int i = 0; i < num_particles; ++i) {
		Particle p = particles[dist(gen)];
		resampled.push_back({ i, p.x, p.y, p.theta, 1.0 });
	}
	particles = resampled;

}

Particle ParticleFilter::SetAssociations(Particle& particle, const std::vector<int>& associations, 
                                     const std::vector<double>& sense_x, const std::vector<double>& sense_y)
{
    //particle: the particle to assign each listed association, and association's (x,y) world coordinates mapping to
    // associations: The landmark id that goes along with each listed association
    // sense_x: the associations x mapping already converted to world coordinates
    // sense_y: the associations y mapping already converted to world coordinates

    particle.associations= associations;
    particle.sense_x = sense_x;
    particle.sense_y = sense_y;
}

string ParticleFilter::getAssociations(Particle best)
{
	vector<int> v = best.associations;
	stringstream ss;
    copy( v.begin(), v.end(), ostream_iterator<int>(ss, " "));
    string s = ss.str();
    s = s.substr(0, s.length()-1);  // get rid of the trailing space
    return s;
}
string ParticleFilter::getSenseX(Particle best)
{
	vector<double> v = best.sense_x;
	stringstream ss;
    copy( v.begin(), v.end(), ostream_iterator<float>(ss, " "));
    string s = ss.str();
    s = s.substr(0, s.length()-1);  // get rid of the trailing space
    return s;
}
string ParticleFilter::getSenseY(Particle best)
{
	vector<double> v = best.sense_y;
	stringstream ss;
    copy( v.begin(), v.end(), ostream_iterator<float>(ss, " "));
    string s = ss.str();
    s = s.substr(0, s.length()-1);  // get rid of the trailing space
    return s;
}