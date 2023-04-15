import time
from PIL import Image
import urllib.request
import numpy as np
import asyncio
import threading

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

def download_img(url):
    img = np.array(Image.open(urllib.request.urlopen(url)))
    print(f'{url}: {img.shape} {threading.get_ident()}')
    return (url, img.shape)

@asyncio.coroutine
def extract_img_shape(loop, url):
    data = yield from loop.run_in_executor(None, lambda: download_img(url))

if __name__ == "__main__":
    start = time.time()
    loop = asyncio.get_event_loop()
    loop.run_until_complete(
        asyncio.wait(
            [
                extract_img_shape(loop, prefix+img_name)
                for img_name in url_paths
            ]
        )
    )
    end = time.time()
    print(end-start)