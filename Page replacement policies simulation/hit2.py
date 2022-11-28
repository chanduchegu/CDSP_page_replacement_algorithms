import matplotlib.pyplot as plt
import os
alg=["random","optimal","nru","fifo","fisc","clock","lru","nfu","working_set","aging","wsclock"]
files=["random.txt","optimal.txt","nru.txt","fifo.txt","fisc.txt","clock.txt","lru.txt","nfu.txt","working_set.txt","ageing.txt","wsclock.txt"]
colors=["blue","black","red","yellow","lawngreen","pink","violet","brown","darkgoldenrod","grey","darkolivegreen"]
ind=0
for file in files:
    print(file)
    if os.path.exists(file)==False:
        ind+=1
        continue
    else:
        print(file+" exists")
    fp=open(file,'r')
    line=fp.readlines()
    x=[]
    y=[]
    for i in range(len(line)):
        lst=line[i].split(' ')
        print(lst)
        x.append(lst[0])
        y.append(lst[1])
    
    plt.plot(x,y,label=alg[ind],color=colors[ind])
    fp.close()
    ind+=1

plt.xlabel('Frames')
plt.ylabel('Hit ratio')
plt.legend()
plt.show()