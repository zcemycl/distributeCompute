import time
from PIL import Image
import urllib.request
import numpy as np
import matplotlib.pyplot as plt
import threading
from threading import Thread, Lock
import random
from multiprocessing import Process

def download_img(url):
    img = np.array(Image.open(urllib.request.urlopen(url)))
    print(f'{url}: {img.shape} {threading.get_ident()}')
    return (url, img.shape)

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

    # overhead
    processes = [Process(target=download_img, args=(prefix+img_name,))
        for img_name in url_paths]
    for process in processes:
        process.start()
    for process in processes:
        process.join()
    end3 = time.time()
    print(end3-end2)


