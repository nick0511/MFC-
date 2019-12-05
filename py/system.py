import random
import time
import tkinter as tk


window = tk.Tk()
window.title("test")
window.geometry('200x200')


#时间片轮转
def RR():
    window = tk.Tk()
    window.title("时间片轮转")
    window.geometry('900x500')
    w=tk.Tk()
    w.title("初始进程情况")
    w.geometry('400x300')
    tk.Label(w, text='作业状态', ).place(x=20, y=30)
    tk.Label(w, text='作业名', ).place(x=100, y=30)
    tk.Label(w, text='作业长度', ).place(x=180, y=30)


    tk.Label(window, text='作业状态', ).place(x=20, y=30)
    tk.Label(window, text='作业名', ).place(x=100, y=30)
    tk.Label(window, text='作业长度', ).place(x=180, y=30)
    tk.Label(window, text='调度', ).place(x=400, y=30)
    tk.Label(window, text='完成率', ).place(x=800, y=30)
    # 初始化图形界面

    # 初始化数据
    job_name = ['p1', 'p2', 'p3', 'p4', 'p5', 'p6', 'p7', 'p8', 'p9', 'p10']
    n = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  # 用于进度条更新的参数
    job_length = [5, 3, 2, 11, 43, 22, 55, 44, 77, 44]  # job需要时间片长度
    job_used_time = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  # job的已用时间
    job_status = ['就绪', '就绪', '就绪', '就绪', '就绪', '就绪', '就绪', '就绪', '就绪', '就绪']  # job的状态
    job_priority = [10, 20, 2, 3, 1, 15, 2, 3, 2, 4]
    a = []  # 存进度条的对象列表
    lb = []  # 存label的对象列表
    bfb = []  # 百分比
    location = 60  # y轴位置参数
    for y in range(10):
        tmp_string = str(job_used_time[y] / job_length[y] * 100) + '%'
        bfb.append(tmp_string)

    for y in range(10):

        tk.Label(w, text=job_length[y], ).place(x=180, y=location)  # 作业长度
        tk.Label(w, text=job_name[y], ).place(x=100, y=location)  # 作业名
        tk.Label(w, text=job_status[y], ).place(x=30, y=location)  # 作业状态

        tk.Label(window, text=job_length[y], ).place(x=180, y=location)  # 作业长度
        tk.Label(window, text=job_name[y], ).place(x=100, y=location)  # 作业名
        tk.Label(window, text=job_status[y], ).place(x=30, y=location)  # 作业状态
        lb1 = tk.Label(window, text=bfb[y])  # 创建label对象
        lb.append(lb1)  # 将对象存储到列表
        lb1.place_configure(x=800, y=location)
        canvas = tk.Canvas(window, width=450, height=22, bg="white")
        canvas.place(x=300, y=location)  # 进度条
        a.append(canvas)
        location += 30  # 位置参数+30

    # 初始化数据

    for j in range(max(job_length)):            #最大的工作进程需要时间片数
        for i in range(len(a)):
            if job_used_time[i]>=job_length[i]: #时间片够了的进程就跳过下面的操作
                continue
            fill_line = a[i].create_rectangle(1.5, 1.5, 0, 23, width=0, fill="green")
            n[i] = n[i] + 460 / job_length[i]
            a[i].coords(fill_line, (0, 0, n[i], 60))
            job_status[i]='运行'                      #更改运行进程的状态
            job_used_time[i]+=1
            location = 60                             #更新页面
            for y in range(10):
                bfb[y]=str(round(job_used_time[y] / job_length[y]*100,2)) + '%'
                lb[y].config(text=bfb[y])
                tk.Label(window, text=job_status[y], ).place(x=30, y=location)
                location+=30
            window.update()
            if job_used_time[i]>=job_length[i]:
                job_status[i] = '完成'
            else:
                job_status[i] = '就绪'                    #完成后状态修改
            time.sleep(0.2)
              # 控制进度条流动的速度

def dynamic():
    w = tk.Tk()
    w.title("初始进程状态")
    w.geometry('400x300')

    window = tk.Tk()
    window.title("动态优先权算法")
    window.geometry('900x500')
    tk.Label(w, text='作业状态', ).place(x=20, y=30)
    tk.Label(w, text='作业名', ).place(x=100, y=30)
    tk.Label(w, text='作业长度', ).place(x=180, y=30)
    tk.Label(w, text='作业优先级', ).place(x=240, y=30)
    tk.Label(window, text='作业状态', ).place(x=20, y=30)
    tk.Label(window, text='作业名', ).place(x=100, y=30)
    tk.Label(window, text='作业长度', ).place(x=180, y=30)
    tk.Label(window, text='作业优先级', ).place(x=240, y=30)
    tk.Label(window, text='调度', ).place(x=400, y=30)
    tk.Label(window, text='完成率', ).place(x=800, y=30)
    # 初始化图形界面

    # 初始化数据
    job_name = ['p1', 'p2', 'p3', 'p4', 'p5', 'p6', 'p7', 'p8', 'p9', 'p10']
    n = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  # 用于进度条更新的参数
    job_length = [5, 3, 2, 11, 43, 22, 55, 44, 77, 44]  # job需要时间片长度
    job_used_time = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  # job的已用时间
    job_status = ['就绪', '就绪', '就绪', '就绪', '就绪', '就绪', '就绪', '就绪', '就绪', '就绪']  # job的状态
    job_priority = [-10, 19, -2, 3, 1, 15, 2, 3, 2, 4]
    real_priority= [-10, 19, -2, 3, 1, 15, 2, 3, 2, 4]
    a = []  # 存进度条的对象列表
    lb = []  # 存label的对象列表，是完成率的label
    lb_priority=[]  # 存label的对象列表，是优先级的label
    bfb = []  # 百分比
    location = 60  # y轴位置参数
    for y in range(10):
        tmp_string = str(job_used_time[y] / job_length[y] * 100) + '%'
        bfb.append(tmp_string)

    for y in range(10):
        tk.Label(window, text=job_length[y], ).place(x=180, y=location)  # 作业长度
        tk.Label(window, text=job_name[y], ).place(x=100, y=location)  # 作业名
        tk.Label(window, text=job_status[y], ).place(x=30, y=location)  # 作业状态
        tk.Label(w, text=job_length[y], ).place(x=180, y=location)  # 作业长度
        tk.Label(w, text=job_name[y], ).place(x=100, y=location)  # 作业名
        tk.Label(w, text=job_status[y], ).place(x=30, y=location)  # 作业状态
        tk.Label(w, text=job_priority[y], ).place(x=250, y=location)  # 作业状态
        lb_p = tk.Label(window, text=job_priority[y])
        lb_priority.append(lb_p)
        lb_p.place_configure(x=250,y=location)
        lb1 = tk.Label(window, text=bfb[y])  # 创建label对象
        lb.append(lb1)  # 将对象存储到列表
        lb1.place_configure(x=800, y=location)
        canvas = tk.Canvas(window, width=450, height=22, bg="white")
        canvas.place(x=300, y=location)  # 进度条
        a.append(canvas)
        location += 30  # 位置参数+30

    # 初始化数据

          #最大的工作进程需要时间片数
    for i in range(1000):
        i=i%10;
        real_priority.sort()
        real_priority.reverse()
        if job_used_time[i]>=job_length[i]: #时间片够了的进程就跳过下面的操作
            continue
        if job_priority[i]>real_priority[-1]:
            continue

        fill_line = a[i].create_rectangle(1.5, 1.5, 0, 23, width=0, fill="green")
        n[i] = n[i] + 460 / job_length[i]
        a[i].coords(fill_line, (0, 0, n[i], 60))
        job_status[i]='运行'                      #更改运行进程的状态
        job_used_time[i]+=1
        if job_priority[i]<20:
            job_priority[i]+=1                      #每次调度完成优先级变化
            real_priority[-1]+=1
        location = 60                             #更新页面
        for y in range(10):
            bfb[y]=str(round(job_used_time[y] / job_length[y]*100,2)) + '%'

            lb[y].config(text=bfb[y])
            lb_priority[y].config(text=job_priority[y])
            tk.Label(window, text=job_status[y], ).place(x=30, y=location)
            location+=30
        window.update()
        if job_used_time[i]>=job_length[i]:
            job_status[i] = '完成'
            real_priority.pop()
        else:
            job_status[i] = '就绪'                    #完成后状态修改
        time.sleep(0.2)
          # 控制进度条流动的速度

def HRRN():
    w = tk.Tk()
    w.title("初始进程状态")
    w.geometry('400x300')

    window = tk.Tk()
    window.title("动态优先权算法")
    window.geometry('900x500')
    alltime=0

    tk.Label(w, text='作业状态', ).place(x=20, y=30)
    tk.Label(w, text='作业名', ).place(x=100, y=30)
    tk.Label(w, text='作业长度', ).place(x=180, y=30)
    tk.Label(w, text='作业响应比', ).place(x=240, y=30)
    tk.Label(w, text='作业到达时间', ).place(x=320, y=30)

    tk.Label(window, text='作业状态', ).place(x=20, y=30)
    tk.Label(window, text='作业名', ).place(x=100, y=30)
    tk.Label(window, text='作业长度', ).place(x=180, y=30)
    tk.Label(window, text='作业响应比', ).place(x=240, y=30)
    tk.Label(window, text='调度', ).place(x=400, y=30)
    tk.Label(window, text='完成率', ).place(x=800, y=30)
    # 初始化图形界面

    # 初始化数据
    job_name = ['p1', 'p2', 'p3', 'p4', 'p5', 'p6', 'p7', 'p8', 'p9', 'p10']
    n = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  # 用于进度条更新的参数
    job_length = [5, 3, 2, 11, 43, 22, 55, 44, 77, 44]  # job需要服务时间
    job_used_time = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]  # job的已用时间
    job_status = ['就绪', '就绪', '就绪', '就绪', '就绪', '就绪', '就绪', '就绪', '就绪', '就绪']# job的状态
    job_cometime=[0,1,3,4,4,5,6,7,8,9]
    job_xyb = []
    real_xyb= []
    for i in range(len(job_cometime)):
        HRRN_Value=(job_cometime[i]+job_length[i]+alltime)/job_length[i]
        job_xyb.append(HRRN_Value)
        real_xyb.append(HRRN_Value)
#    计算相应比
    a = []  # 存进度条的对象列表
    lb = []  # 存label的对象列表，是完成率的label
    lb_xyb=[]  # 存label的对象列表，是相应比的label
    bfb = []  # 完成率百分比
    location = 60  # y轴位置参数
    for y in range(10):
        tmp_string = str(job_used_time[y] / job_length[y] * 100) + '%'
        bfb.append(tmp_string)

    for y in range(10):



        tk.Label(window, text=job_length[y], ).place(x=180, y=location)  # 作业长度
        tk.Label(window, text=job_name[y], ).place(x=100, y=location)  # 作业名
        tk.Label(window, text=job_status[y], ).place(x=30, y=location)  # 作业状态
        tmp = str(round(job_xyb[y] * 100, 2)) + '%'
        lb_b = tk.Label(window, text=tmp)
        lb_xyb.append(lb_b)
        lb_b.place_configure(x=250,y=location)
        lb1 = tk.Label(window, text=bfb[y])  # 创建label对象
        lb.append(lb1)  # 将对象存储到列表
        lb1.place_configure(x=800, y=location)
        canvas = tk.Canvas(window, width=450, height=22, bg="white")
        canvas.place(x=300, y=location)  # 进度条
        a.append(canvas)

        tk.Label(w, text=job_cometime[y]).place(x=340, y=location)
        tk.Label(w, text=tmp).place(x=250,y=location)
        tk.Label(w, text=job_length[y], ).place(x=180, y=location)
        tk.Label(w, text=job_name[y], ).place(x=100, y=location)
        tk.Label(w, text=job_status[y], ).place(x=30, y=location)
        location += 30  # 位置参数+30


    # 初始化数据


    for i in range(10000):

        if(len(real_xyb)==0):
            break
        real_xyb = []

        i=i%10
        flag = 0
        #更新响应比
        for j in range(len(job_name)):
            if job_used_time[j] < job_length[j]:
                job_xyb[j]=((job_cometime[j] + job_length[j]+alltime) / job_length[j])

        for j in range(len(job_name)):
            if job_used_time[j]<job_length[j]:
                real_xyb.append((job_cometime[j] + job_length[j]+alltime) / job_length[j])

        real_xyb.sort()

        if job_used_time[i]>=job_length[i]: #时间片够了的进程就跳过下面的操作
            continue
        if job_xyb[i]!=real_xyb[-1]:
            continue
        fill_line = a[i].create_rectangle(1.5, 1.5, 0, 23, width=0, fill="green")

        job_status[i]='运行'                      #更改运行进程的状态
        for j in range(1000):
            n[i] = n[i] + 460 / job_length[i]
            a[i].coords(fill_line, (0, 0, n[i], 60))
            job_used_time[i]+=1
            alltime+=1
            bfb[i] = str(round(job_used_time[i] / job_length[i] * 100, 2)) + '%'
            lb[i].config(text=bfb[i])
            lb_xyb[i].config(text=job_xyb[i])
            time.sleep(0.1)
            if job_length[i]==job_used_time[i]:
                job_status[i] = '完成'
                real_xyb.pop(-1)
                flag=1
            location = 60  # 更新页面
            for y in range(10):
                bfb[y] = str(round(job_used_time[y] / job_length[y] * 100, 2)) + '%'
                lb[y].config(text=bfb[y])
                tmp=str(round(job_xyb[y]*100,2)) + '%'
                lb_xyb[y].config(text=tmp)
                tk.Label(window, text=job_status[y], ).place(x=30, y=location)
                location += 30
            window.update()
            if flag==1:
                break
        time.sleep(0.2)
if __name__=='__main__':
    #调用RR

    tk.Button(window, text="RR", command=RR, padx=12, pady=3).place(x=40, y=20)
    tk.Button(window, text="Dynamic", command=dynamic, padx=12, pady=3).place(x=40, y=70)
    tk.Button(window, text="HRRN", command=HRRN, padx=12, pady=3).place(x=40, y=120)
    window.mainloop()
