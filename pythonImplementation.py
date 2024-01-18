import numpy as np
import matplotlib.pyplot as plt
import cv2

# Set image path
imgPath = '/Users/spencerevans-cole/Desktop/Coding/SVD-Image-Compression/images/nyc.jpeg'

# Read image
img = cv2.imread(imgPath)

# Make image grayscale
img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# Create SVD
U, S, V = np.linalg.svd(img)

components = [S.shape[0],1, 5, 10, 20, 50, 100, 150]
# Plot images
plt.figure(figsize=(16, 6))
for i in range(len(components)):
    if components[i] > S.shape[0]:
        break
    plt.subplot(2, 4, i+1)
    plt.imshow(U[:, :components[i]] @ np.diag(S[:components[i]]) @ V[:components[i], :], cmap='gray')
    plt.title('Singular Values: {}'.format(components[i]))
    plt.axis('off')

plt.show()