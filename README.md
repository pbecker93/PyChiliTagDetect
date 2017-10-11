# PyChiliTagDetect

Wraps the detection functionality of the chilitags (https://github.com/chili-epfl/chilitags) libraries.  

## Installation 
1. Install the chilitag library
2. Run 'sudo ldconfig'
3. Install the PyChiliTagDetect Package using the setup.py 

Only tested with Python 3.5 on Linux Ubuntu 16.04LTS

## Usage 
With some image 'img' (as numpy array)

```python 
import chili_tag_detector as ctd
tag_list = ctd.detect(img)
```
markers is a list of tuples. There is one tuple for each detected chilitag. The first entry is the ID of the tag and the second entry a 4x2 numpy array containing the image coordinates of the 4 corner points of the tag.

## Demo 
You can find a short demo in "test_script.py". It will stream images from a webcam, detect and highlight chilitags in real time. OpenCV and numpy are required to run the script.
