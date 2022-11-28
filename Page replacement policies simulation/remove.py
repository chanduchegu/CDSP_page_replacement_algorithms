import os
files=["random.txt","optimal.txt","nru.txt","fifo.txt","fisc.txt","clock.txt","lru.txt","nfu.txt","working_set.txt","aging.txt","wsclock.txt"]
for file in files:
    if os.path.exists(file)==True:
        os.remove(file)
lst=os.listdir('./images')
for x in lst:
    os.remove(os.path.join('./images',x))