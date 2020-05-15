import csv
import matplotlib.pyplot as plt
import numpy as np
import dataAugment as da
from sklearn.utils import shuffle

def read_data_csv(path, filename):
    samples = []
    with open(path + filename) as f:
        reader = csv.reader(f)
        for line in reader:
            # cleanse spaces in the data
            line = list(map(lambda str: str.strip(), line))
            samples.append(line)
    # remove the column names
    del samples[0]
    return samples

def select_image(sample, data_path):
    """Select an image from a list of options
    
    Arguments:
        sample {list]} -- a csv row, list of strings
    """
    choice_index = np.random.choice(3)
    filename = data_path + '/IMG/' + sample[choice_index].split('/')[-1]
    angle = np.float(sample[3])
    img = plt.imread(filename)
    if choice_index == 0:
        return img, angle
    # Left Camera Image: adjust with a small right turn
    elif choice_index == 1:
        return img, angle + 0.25
    # Right Camera Imageadjust with a small left turn
    else:
        return img, angle - 0.25

class DataGenerator(object):
    def __init__(self):
        self.steering = []

    # From Udacity course notes
    def sample_generator(self, samples, data_path, batch_size=32, augment_enable=True):
        num_samples = len(samples)
        while 1: # Loop forever so the generator never terminates
            shuffle(samples)
            for offset in range(0, num_samples, batch_size):
                batch_samples = samples[offset:offset+batch_size]
                images = []
                angles = []
                for batch_sample in batch_samples:
                    img, angle = select_image(batch_sample, data_path)
                    # augment the image
                    if augment_enable:
                        img, angle = da.augment_image(img, angle)
                    img = da.crop_n_resize(img, 70, 25, (320, 160))
                    # Keep tract of the steering angles for reporting
                    self.steering.append(angle)
                    images.append(img)
                    angles.append(angle)

                X_train = np.array(images)
                y_train = np.array(angles)
                yield shuffle(X_train, y_train)