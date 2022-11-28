import matplotlib.pyplot as plt
import os
alg = ["random", "optimal", "nru", "fifo", "fisc", "clock",
       "lru", "nfu", "working_set", "aging", "wsclock"]
files = ["random.txt", "optimal.txt", "nru.txt", "fifo.txt", "fisc.txt",
         "clock.txt", "lru.txt", "nfu.txt", "working_set.txt", "ageing.txt", "wsclock.txt"]
colors = ["blue", "black", "red", "yellow", "green",
          "pink", "violet", "brown", "lavender", "grey", "maroon"]


def Plot(x, y, f, algo):
    plt.plot(x, y)
    #print(f)
    plt.xlabel('Frames')
    plt.ylabel('Misses')
    plt.title(algo)
    plt.savefig(f)
    # plt.scatter(x, y, label=algo)
    # plt.xlabel("frames")
    # plt.ylabel("misses")
    # plt.plot(x, y, '--')
    # plt.savefig(f)
    plt.clf()

ind = 0

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
        y.append(lst[2])
    f = "./images/"+alg[ind]+'_miss.png'
    plt.clf()
    Plot(x,y,f,alg[ind])
    # plt.plot(x, y, label=alg[ind], color=colors[ind])
    # plt.xlabel('Frames')
    # plt.ylabel('Miss ratio')
    # plt.legend()
    # plt.savefig()
    # plt.show()
    fp.close()
    ind += 1