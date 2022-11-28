import matplotlib.pyplot as plt
import os
alg = ["random", "optimal", "nru", "fifo", "fisc", "clock",
       "lru", "nfu", "working_set", "aging", "wsclock"]
files = ["random.txt", "optimal.txt", "nru.txt", "fifo.txt", "fisc.txt",
         "clock.txt", "lru.txt", "nfu.txt", "working_set.txt", "ageing.txt", "wsclock.txt"]
colors = ["blue", "black", "red", "yellow", "green",
          "pink", "violet", "brown", "lavender", "grey", "maroon"]
fig, axs = plt.subplots(len(files))
ind = 0
def Plot(x,y,f,algo):
    plt.plot(x,y)
    #print(f)
    plt.xlabel('Frames')
    plt.ylabel('Hits')
    plt.title(algo)
    plt.savefig(f)
    # plt.scatter(x,y,label=algo)
    # plt.plot(x,y,'--')
    # plt.xlabel("frames")
    # plt.ylabel("hits")
    # plt.savefig(f)
    plt.clf()

for file in files:
    print(file)
    if os.path.exists(file) == False:
        ind += 1
        continue
    else:
        print(file+" exists")
    fp = open(file, 'r')
    line = fp.readlines()
    x = []
    y = []
    for i in range(len(line)):
        lst = line[i].split(' ')
        print(lst)
        x.append(lst[0])
        y.append(lst[1])
    f = "./images/"+alg[ind]+'_hit.png'
    plt.clf()
    # plt.plot(x,y)
    # plt.xlabel("Frames")
    # plt.ylabel("Hits")
    # plt.legend()
    # plt.savefig(f)
    Plot(x,y,f,alg[ind])
    fp.close()
    ind += 1