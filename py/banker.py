import tkinter as tk
import tkinter.messagebox
from tkinter import ttk

window = tk.Tk()
window.title("银行家算法")
window.geometry('600x700')



#存储lable的列表初始化
available_tk=[]
allocation_tk=[]
need_tk=[]


#数据初始化
resource_name=['A','B','C']
available=[3,3,2]#m种资源，每种资源可用数目
max=[[7,5,3],[3,3,2],[9,0,2],[2,2,2],[4,3,3]]#第i个进程第j种资源最大需求量
allocation=[[0,1,0],[2,0,0],[3,0,2],[2,1,1],[0,0,2]]#第i个进程第j种资源已经分配的量
need=[[7,4,3],[1,2,2],[6,0,0],[0,1,1],[4,3,1]]#第i个进程第j种资源还需要的量
finish=[0,0,0,0,0]
result_list=[]
the_queue=[]

#静态标签初始化
tk.Label(window,text="进程：").place(x=20,y=620)

tk.Label(window,text="请求向量").place(x=120,y=620)
tk.Label(window,text="A:").place(x=180,y=570)
tk.Label(window,text="B:").place(x=180,y=620)
tk.Label(window,text="C:").place(x=180,y=670)

#选择框
comvalue = tk.StringVar()  # 窗体自带的文本，新建一个值
comboxlist = ttk.Combobox(window, textvariable=comvalue)  # 初始化
comboxlist["values"] = ("p0", "p1", "p2", "p3", "p4")
comboxlist.current(0)
comboxlist.place_configure(x=60,y=620)
comboxlist.config(width=5)


#输入框
e1 = tk.Entry(window)
e1.place_configure(x=200, y=570)
e1.config(width=5)

e2 = tk.Entry(window)
e2.place_configure(x=200, y=620)
e2.config(width=5)

e3 = tk.Entry(window)
e3.place_configure(x=200, y=670)
e3.config(width=5)



tk.Label(window, text='系统在t0的资源分配表:', ).place(x=40, y=10)
tk.Label(window, text='process', ).place(x=40, y=50)
tk.Label(window, text='MAX', ).place(x=150, y=50)
tk.Label(window, text='Allocation', ).place(x=280, y=50)
tk.Label(window, text='Need', ).place(x=420, y=50)
tk.Label(window, text='Available', ).place(x=520, y=50)
tk.Label(window, text='检查t0时刻安全性:', ).place(x=40, y=350)
#数据打印到面板

tk.Label(window,text=resource_name).place(x=150,y=80)
tk.Label(window,text=resource_name).place(x=280,y=80)
tk.Label(window,text=resource_name).place(x=420,y=80)
tk.Label(window,text=resource_name).place(x=520,y=80)



y_location=120

avtk=tk.Label(window, text=available, )
avtk.place_configure(x=520, y=y_location)
available_tk.append(avtk)
for i in range(5):
    tk.Label(window,text=max[i]).place(x=150,y=y_location)

    altk=tk.Label(window, text=allocation[i], )
    altk.place_configure(x=280, y=y_location)
    allocation_tk.append(altk)

    netk= tk.Label(window, text=need[i], )
    netk.place_configure(x=420, y=y_location)
    need_tk.append(netk)

    tk.Label(window, text="p"+str(i), ).place(x=40, y=y_location)

    y_location+=50

#进程请求向量
def ask():
#标识为全局变量，使可以修改
    global available
    global max
    global allocation
    global need
    global finish
    global the_queue

    resource_a=int(e1.get())
    resource_b=int(e2.get())
    resource_c=int(e3.get())

    process_name=comboxlist.get()
    process_num=str(process_name).split('p')[1]
#请求的矩阵和available矩阵比较，多与available则出错
    if resource_a<=available[0] and resource_b <= available[1] and resource_c<=available[2]:
        available[0] -= resource_a
        available[1] -= resource_b
        available[2] -= resource_c
        need[int(process_num)][0] -= resource_a
        need[int(process_num)][1] -= resource_b
        need[int(process_num)][2] -= resource_c
        allocation[int(process_num)][0] += resource_a
        allocation[int(process_num)][1] += resource_b
        allocation[int(process_num)][2] += resource_c
        available_tk[0].config(text=available)
        for i in range(len(allocation_tk)):
            allocation_tk[i].config(text=allocation[i])
            need_tk[i].config(text=need[i])
    else:
        tk.messagebox.showinfo('提示','分配失败')

#检查安全序列
def check():
    the_queue = []
    for i in range(len(max)):
        for j in range(len(max)):
            if finish[j] == 1:
                continue
            count = 0
            for k in range(len(available)):
                if (need[j])[k] <= available[k]:
                    count += 1
            if count == 3:
                tmp = available.copy()
                result_list.append(tmp)
                finish[j] = 1
                the_queue.append(j)
                for i in range(len(available)):
                    available[i] += max[j][i]


    if len(the_queue) < 5:
        tk.messagebox.showinfo('提示', '系统是不安全的')
    else:
        w=tk.Tk()
        w.geometry('700x300')
        tk.Label(w,text="系统在t0时刻存在安全序列" + str(the_queue) + "，系统是安全的").place(x=100,y=20)
        tk.Label(w,text="Free").place(x=120,y=50)
        tk.Label(w,text="Need").place(x=220,y=50)
        tk.Label(w,text="Allocation").place(x=320,y=50)
        tk.Label(w,text="Free+Allocation").place(x=420,y=50)
        tk.Label(w,text="Finish").place(x=500,y=50)

        tk.Label(w, text=resource_name).place(x=120, y=80)
        tk.Label(w, text=resource_name).place(x=220, y=80)
        tk.Label(w, text=resource_name).place(x=320, y=80)
        tk.Label(w, text=resource_name).place(x=420, y=80)

        y_location=100
        count = 0
        for i in the_queue:

            tk.Label(w,text="p"+str(i)).place(x=30,y=y_location)
            tk.Label(w,text=result_list[count]).place(x=120,y=y_location)
            tk.Label(w,text=need[i]).place(x=220,y=y_location)
            tk.Label(w,text=allocation[i]).place(x=320,y=y_location)
            tmp=[]
            for j in range(len(available)):
                tmp.append(allocation[i][j]+result_list[count][j])
            tk.Label(w, text=tmp).place(x=420, y=y_location)
            tk.Label(w, text='True'if finish[i]==1 else 'False').place(x=500, y=y_location)
            y_location+=40
            count +=1
    init_that()
#初始化面板
def init_that():
    global available
    global max
    global allocation
    global need
    global finish
    global the_queue
    global result_list

    result_list=[]
    available = [3, 3, 2]  # m种资源，每种资源可用数目
    max = [[7, 5, 3], [3, 3, 2], [9, 0, 2], [2, 2, 2], [4, 3, 3]]  # 第i个进程第j种资源最大需求量
    allocation = [[0, 1, 0], [2, 0, 0], [3, 0, 2], [2, 1, 1], [0, 0, 2]]  # 第i个进程第j种资源已经分配的量
    need = [[7, 4, 3], [1, 2, 2], [6, 0, 0], [0, 1, 1], [4, 3, 1]]  # 第i个进程第j种资源还需要的量
    finish = [0, 0, 0, 0, 0]
    the_queue = []

    available_tk[0].config(text=available)
    for i in range(len(allocation_tk)):
        allocation_tk[i].config(text=allocation[i])
        need_tk[i].config(text=need[i])







tk.Button(window, text="安全检查", command=check, padx=12, pady=3).place(x=150, y=400)

tk.Button(window, text="进程发起请求向量", command=ask, padx=12, pady=3).place(x=400, y=600)
tk.Button(window, text="初始化", command=init_that, padx=12, pady=3).place(x=350, y=400)

window.mainloop()