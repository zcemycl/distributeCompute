import time
from PIL import Image
import urllib.request
import numpy as np
import matplotlib.pyplot as plt
import threading
from threading import Thread, Lock
import random

def download_img(url):
    img = np.array(Image.open(urllib.request.urlopen(url)))
    print(f'{url}: {img.shape} {threading.get_ident()}')
    return (url, img.shape)

class FakeList:
    def __init__(self):
        self.arr = []
        self._lock = Lock()

    def locked_update(self, url):
        img = np.array(Image.open(urllib.request.urlopen(url)))
        with self._lock:
            local_copy = self.arr.copy()
            time.sleep(1)
            local_copy.append(img.shape)
            self.arr = local_copy

    def bad_update(self, url):
        img = np.array(Image.open(urllib.request.urlopen(url)))
        local_copy = self.arr.copy()
        time.sleep(1)
        local_copy.append(img.shape)
        self.arr = local_copy



prefix = "https://raw.githubusercontent.com/zcemycl/zcemycl.github.io/master/resources/"

url_paths = [
    "970evo.jpg",
    "8pins.png",
    "9pinouts.jpg",
    "SCCs.png",
    "acc1.png",
    "19pins.jpeg",
    "3pins.jpg",
    "addCurve.png",
    "blenderaddplane.png",
    "blink1.png",
    "blink2.png",
    "bottom.jpg"
]

if __name__ == "__main__":
    start = time.time()
    for img_name in url_paths:
        download_img(prefix+img_name)
    end = time.time()
    print(end-start)

    threads = [Thread(target=download_img, args=(prefix+img_name,)) 
        for img_name in url_paths]
    for thread in threads:
        thread.start()
    for thread in threads:
        thread.join()
    end2 = time.time()
    print(end2-end)

    Good_List = FakeList()
    threads_good_update = [Thread(target=Good_List.locked_update, args=(prefix+img_name,)) 
        for img_name in url_paths]
    for thread in threads_good_update:
        thread.start()
    for thread in threads_good_update:
        thread.join()
    end3 = time.time()
    print(Good_List.arr, end3-end2)

    Bad_List = FakeList()
    threads_bad_update = [Thread(target=Bad_List.bad_update, args=(prefix+img_name,)) 
        for img_name in url_paths]
    for thread in threads_bad_update:
        thread.start()
    for thread in threads_bad_update:
        thread.join()
    end4 = time.time()
    print(Bad_List.arr, end4-end3)