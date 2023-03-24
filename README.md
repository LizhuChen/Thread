# Thread
模擬thread排程

讀取Input檔案中大量的data，將其資料經過四種排序方式後得到由小到大的排序結果，比較經過四種方式的執行時間，最後輸出排序好的結果和執行時間至output檔中。

Input:

![image](https://github.com/LizhuChen/Thread/blob/main/img/input.png)

Output:

![image](https://github.com/LizhuChen/Thread/blob/main/img/output.png)


Case 1:

僅使用bubble sort的排序方式進行排序，由於bubble sort的原理是每筆資料互相比較再進行交換，因此當資料數量逐漸增加時，所需執行時間也會越來越長。

Case 2:

使用執行緒的方式進行排序，其執行方式是以多程序形式，允許多個任務同時執行，因此當使用者分割成較多份時，其執行時間會比分割成較少份時來的快。和Case 1相比，原先採取bubble sort進行排序在至Merge sort進行合併的方式，本身就比直接使用Bubble sort來的快，又採取執行緒同時並行處理，因此其執行時間比Case 1少好幾倍以上。

Case 3:

採取多process的方式進行，將一個process分成多個process輪流進行執行，和Case 1相比，原先採取bubble sort進行排序在至Merge sort進行合併的方式，本身就比直接使用Bubble sort來的快，並且又加入多process處理，因此執行時間會較快。和Case 2相比，由於是多個process輪流進行執行，因此和執行緒的同時進行處理相比，會較慢。

Case 4:

採取先分成多份資料進行Bubble sort在使用Merge sort進行合併，雖然只有一個process進行處理，但和Case 1相比還是快了許多，其差異原因可能是因為分成多份資料，可以減少大量進行bubble sort的時間，再藉由Merge sort的方式進行合併。


比較:
 - 四種方式分別執行一萬筆，十萬筆，五十萬筆，一百萬筆資料，並對執行時間進行分析:(二、四皆切成50份)(第三題為python並切成10份)
 
 ![image](https://github.com/LizhuChen/Thread/blob/main/img/table.PNG)
