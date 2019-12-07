import numpy as np
from matplotlib import pyplot as plt

N = 64
mi = 100
nw = 100

grid = np.zeros([N+2,N+2],dtype='int')
grid = grid.transpose((1,0))



x = np.zeros(nw,dtype='int')
y = np.zeros(nw,dtype='int')

x_step = np.array([-1,0,1,0])
y_step = np.array([0,-1,0,1])

# x = np.arange(1, 11)
# y = 2 * x + 5

#设定边界
plt.axis([-N, N, -N, N])


plt.title("Matplotlib demo")
plt.xlabel("x axis caption")
plt.ylabel("y axis caption")

#生成10个点，取值为-N到N
x=np.random.randint(-N,N,size=10)
y=np.random.randint(-N,N,size=10)

#迭代mi次
for i in range(mi):
    x+=int(np.random.choice(10,1)[0])
    y+=int(np.random.choice(10,1)[0])

#位置修改
    count_x=0
    count_y=0
    for i in x:
        if abs(i)>N:
            if i > N:
                i-=2*N
            else:
                i+=2*N
        x[count_x]=i
        count_x+=1
    for i in y:
        if abs(i)>N:
            if i > N:
                i-=2*N
            else:
                i+=2*N
        y[count_y]=i
        count_y+=1

    #清除画布
    plt.cla()
    #设定边界
    plt.axis([-N, N, -N, N])
    plt.plot(x, y, "ob")
    #中断时间
    plt.pause(0.2)


plt.show()