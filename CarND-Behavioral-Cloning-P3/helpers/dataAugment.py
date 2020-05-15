import cv2
import random
import numpy as np

GAMMA_COR_CHANCE = 0.3
FLIP_CHANCE      = 0.5
SHEAR_CHANCE     = 0.4
SHEAR_RANGE      = 90

def happens(prob):
    """ Trigger a random event to happen
    
    Arguments:
        prob {float} -- chances to return true
    
    Returns:
        [bool] -- if the random event happens
    """
    chance = random.uniform(0,1)
    return chance <= prob

def rand_gamma(image, steering, max=2.5, min=0.5, prob=GAMMA_COR_CHANCE):
    """Apply a gamma correction to the image
    
    Keyword Arguments:
        max {float} -- maximum correction (default: {2.5})
        min {float} -- minimum correction (default: {0.3})
        prob {float} -- chance of applying this function (default: {0.6})
    """
    if happens(prob):
        gamma = np.random.uniform(max, min)
        invGamma = 1.0 / gamma
        table = np.array([((i / 255.0) ** invGamma) * 255 
            for i in np.arange(0, 256)]).astype("uint8")
        return cv2.LUT(image, table), steering
    else:
        return image, steering

def flip(image, steering, axis=1, prob=FLIP_CHANCE):
    """Flip an image, default to horizontal flip
    
    Keyword Arguments:
        axis {int} -- axis around which to flip (default: {1})
        prob {float} -- chance of applying this function (default: {0.5})
    """

    if happens(prob):
        return cv2.flip(image, axis), steering * -1
    else:
        return image, steering

def rand_shear(image, steering, shear_range=SHEAR_RANGE, prob=SHEAR_CHANCE):
    """Shear an image at a random location
    
    Keyword Arguments:
        shear_range {int} -- the degree to which the image is sheared
        prob {float} -- chance of applying this function  {default: {0.6}}
    Source reference: https://medium.com/@ksakmann/behavioral-cloning-make-a-car-drive-like-yourself-dc6021152713
    """
    if happens(prob):
        rows, cols, ch = image.shape
        dx = np.random.randint(-1 * shear_range, shear_range + 1)
        random_point = [cols / 2 + dx, rows / 2]
        pts1 = np.float32([[0, rows], [cols, rows], [cols / 2, rows / 2]])
        pts2 = np.float32([[0, rows], [cols, rows], random_point])
        dsteering = dx / (rows / 2) * 360 / (2 * np.pi * 25.0) / 10.0    
        M = cv2.getAffineTransform(pts1, pts2)
        image = cv2.warpAffine(image, M, (cols, rows),borderMode=1)
        steering += dsteering
        
    return image, steering

def augment_image(image, steering):
    image, steering = rand_shear(image, steering)
    image, steering = rand_gamma(image, steering)
    image, steering = flip(image, steering)
    return image, steering

def crop_n_resize(image, top_rows, bottom_rows, new_size):
    top  = top_rows
    bot  = image.shape[0] - bottom_rows
    image = image[top:bot:]
    return cv2.resize(image, new_size)