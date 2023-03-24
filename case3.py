import time
import multiprocessing as mp
import random
import sys
import queue
from numba import jit

#---------------------------------------------------------
@jit
def Bubble_sort( list,q ):
    for i in range( len( list ) - 1 ):
        swapped = False
        for j in range( len(list) - i - 1  ):
            if list[j] > list[j+1] :
                list[j], list[j+1] = list[j+1], list[j]
                swapped = True

        if not swapped:
            break

    q.put(list)

    
# ----------------------------------------------------------
    
def Merge( list1, list2, q): 
    templist =[]
    left = 0
    right = 0
    while left < len( list1 ) and right < len(list2) :
        if list1[left] <= list2[right] :
            templist.append(list1[left])
            left = left + 1 
        else :
            templist.append(list2[right])
            right = right + 1

    while left < len(list1):
        templist.append(list1[left])
        left = left + 1

    while right < len(list2):
        templist.append(list2[right])
        right = right + 1

    q.put(templist)


#-----------------------------------------------------------

def Bprocess( list ):
    q = mp.Manager().Queue()   
    p = mp.Process( target = Bubble_sort, args = ( list, q ) ) 
    p.start()
    p.join()

    revalue = q.get()

    return revalue
    
# ----------------------------------------------------------

def Mprocess( list1, list2 ):
    q = mp.Manager().Queue()  
    p = mp.Process( target = Merge, args = ( list1, list2, q ) )
    p.start()
    p.join()
    
    revalue = q.get()

    return revalue


# ----------------------------------------------------------

if __name__=='__main__':
    filename = input('Input file name: ')

    f = open(filename,'r')
    templist = f.read()
    f.close()
    templist = templist.split('\n')
    command = templist[0]
    temp = templist[1]
    temp = temp.split(' ')
    temp.pop()
    datalist = []
    for i in range(len(temp)) :
        data = int(temp[i])
        datalist.append(data)

 
    #-----------------------------------------------------------

    k_process = []
    temp_k = input("切幾份: ")
    k= int(temp_k)
    datasize = int(len(datalist) / k)

    for i in range(1,k+1):
        temp = []
        if i < k :
            for j in range((i-1)*datasize,i*datasize) :
                temp.append(datalist[j])
        else:
            for j in range((i-1)*datasize,len(datalist)) :
                temp.append(datalist[j])        
        k_process.append(temp)


    start_time = time.time()
    # ************************************
    for i in range (len(k_process)):
        k_process[i] = Bprocess( k_process[i] )
 

    for i in range (1,len(k_process)) :
        k_process[0] = Mprocess( k_process[0], k_process[i] )

    # ************************************
    end_time = time.time()

    #for i in range(len(datalist)) :
        #print(datalist[i])

    f = open('output.txt','w')
    f.write('排序:\n')
    for i in range(len(k_process[0])) :
        f.write(str(k_process[0][i]))
        f.write(' ')

    f.write('\n執行時間:')
    total_time = str(end_time-start_time)
    f.write(total_time)
    f.close()
    print('finish')

