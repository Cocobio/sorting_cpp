import matplotlib.pyplot as plt
import numpy as np

colors = {"quicksort":'r', "quicksortRandomPivot":'g',"mergesort":'b',"mergesortInPlace":'c',"heapsort":'m', "std_sort":'y',"bubblesort":'k',"insertionsort":'#b1f9cf',"selectionsort":'#e354f3'}

# PLOT UNIQUE RANDOM VALUES
folder = "Sort/Datasets/vectorInt random With Unique Values/Sorted/"

sort_list = ["quicksort", "quicksortRandomPivot","mergesort","mergesortInPlace","heapsort", "std_sort","bubblesort","insertionsort","selectionsort"]
sorting_time = []

cuadratic_x = range(0,200001, 25000)
cuadratic_x_label = ["0", "25k", "50k", "75k", "100k", "125k", "150k", "175k", "200k"]

div_and_con_x = range(0, 10000001, 1000000)
div_and_con_x_label = ["0", "1M", "2M", "3M", "4M", "5M", "6M", "7M", "8M", "9M", "10M"]

for sort_name in sort_list:
	file = open(folder+sort_name+".txt","r") 
	data = file.readlines()
	file.close() 

	sorting_time.append(np.array([float(x) for x in data[0].split(";")[:-1]], dtype = np.float32))

fig, ax = plt.subplots(1,2, figsize=(15,6))
fig.suptitle("Vector aleatoreo con valores unicos")

x = [100,500,1000,2000,3000,4000,5000,10000,20000,30000,40000,50000,100000,200000,300000,400000,500000,1000000,2000000,3000000,4000000,5000000,10000000]

for i in range(len(sorting_time)-3):
	ax[1].plot(x, sorting_time[i], label=sort_list[i], color=colors[sort_list[i]])


ax[1].set_title("Algoritmos dividir y conquistar")
ax[1].set_ylabel("Tiempo [s]")
ax[1].set_xlabel("Tamaño del vector")
ax[1].legend()
ax[1].set_xticks(div_and_con_x)
ax[1].set_xticklabels(div_and_con_x_label)
ax[1].grid()


for i in range(len(sorting_time)):
	ax[0].plot(x[:-9], sorting_time[i][:14], label=sort_list[i], color=colors[sort_list[i]])


ax[0].set_title("Algoritmos cuadraticos")
ax[0].set_ylabel("Tiempo [s]")
ax[0].set_xlabel("Tamaño del vector")
ax[0].legend()
ax[0].set_xticks(cuadratic_x)
ax[0].set_xticklabels(cuadratic_x_label)
ax[0].grid()



#PLOT NOT UNIQUE VALUES, BUT RANDOM
folder = "Sort/Datasets/vectorInt/Sorted/"

sort_list = ["quicksort", "quicksortRandomPivot","mergesort","mergesortInPlace","heapsort", "std_sort","bubblesort","insertionsort","selectionsort"]
sorting_time = []

for sort_name in sort_list:
	file = open(folder+sort_name+".txt","r") 
	data = file.readlines()
	file.close() 

	sorting_time.append(np.array([float(i) for i in data[0].split(";")[:-1]], dtype = np.float32))


fig, ax = plt.subplots(1,2, figsize=(15,6))
fig.suptitle("Vector aleatoreo con valores NO unicos")

for i in range(len(sorting_time)-3):
	ax[1].plot(x, sorting_time[i], label=sort_list[i], color=colors[sort_list[i]])


ax[1].set_title("Algoritmos dividir y conquistar")
ax[1].set_ylabel("Tiempo [s]")
ax[1].set_xlabel("Tamaño del vector")
ax[1].legend()
ax[1].set_xticks(div_and_con_x)
ax[1].set_xticklabels(div_and_con_x_label)
ax[1].grid()


for i in range(len(sorting_time)):
	ax[0].plot(x[:-9], sorting_time[i][:14], label=sort_list[i], color=colors[sort_list[i]])


ax[0].set_title("Algoritmos cuadraticos")
ax[0].set_ylabel("Tiempo [s]")
ax[0].set_xlabel("Tamaño del vector")
ax[0].legend()
ax[0].set_xticks(cuadratic_x)
ax[0].set_xticklabels(cuadratic_x_label)
ax[0].grid()



#PLOT SORTED UNIQUE VALUES
folder = "Sort/Datasets/vectorInt sorted/Sorted/"

sort_list = ["quicksort", "quicksortRandomPivot","mergesort","mergesortInPlace","heapsort", "std_sort","bubblesort","insertionsort","selectionsort"]
sorting_time = []

for sort_name in sort_list:
	file = open(folder+sort_name+".txt","r") 
	data = file.readlines()
	file.close() 

	sorting_time.append(np.array([float(x) for x in data[0].split(";")[:-1]], dtype = np.float32))

fig, ax = plt.subplots(1,2, figsize=(15,6))
fig.suptitle("Vector ordenado con valores unicos")

for i in range(1,len(sorting_time)-3):
	ax[1].plot(x, sorting_time[i], label=sort_list[i], color=colors[sort_list[i]])


ax[1].set_title("Algoritmos dividir y conquistar")
ax[1].set_ylabel("Tiempo [s]")
ax[1].set_xlabel("Tamaño del vector")
ax[1].legend()
ax[1].set_xticks(div_and_con_x)
ax[1].set_xticklabels(div_and_con_x_label)
ax[1].grid()



for i in range(len(sorting_time)):
	ax[0].plot(x[:-9], sorting_time[i][:14], label=sort_list[i], color=colors[sort_list[i]])


ax[0].set_title("Algoritmos cuadraticos")
ax[0].set_ylabel("Tiempo [s]")
ax[0].set_xlabel("Tamaño del vector")
ax[0].legend()
ax[0].set_xticks(cuadratic_x)
ax[0].set_xticklabels(cuadratic_x_label)
ax[0].grid()


#PLOT PARTIAL SORTED UNIQUE VALUES
folder = "Sort/Datasets/vectorInt semi sorted With Unique Values/Sorted/"

sort_list = ["quicksort", "quicksortRandomPivot","mergesort","mergesortInPlace","heapsort", "std_sort","bubblesort","insertionsort","selectionsort"]
sorting_time = []

for sort_name in sort_list:
	file = open(folder+sort_name+".txt","r") 
	data = file.readlines()
	file.close() 

	sorting_time.append(np.array([float(x) for x in data[0].split(";")[:-1]], dtype = np.float32))

fig, ax = plt.subplots(1,2, figsize=(15,6))
fig.suptitle("Vector semi ordenado con valores unicos")

for i in range(1,len(sorting_time)-3):
	ax[1].plot(x[:-4], sorting_time[i][:19], label=sort_list[i], color=colors[sort_list[i]])
####################################################################
### quicksort 
file = open("Sort/Datasets/vectorInt special/Sorted/quicksort.txt","r") 
data = file.readlines()
file.close() 
data = np.array([float(x) for x in data[0].split(";")[:-1]], dtype = np.float32)
ax[1].plot(range(100000,1000001,100000), data, label="quicksort", color=colors["quicksort"])
####################################################################

div_and_con_x = range(0,2000001, 200000)
div_and_con_x_label = ["0", "0.2M", "0.4M", "0.6M", "0.8M", "1M", "1.2M", "1.4M", "1.6M", "1.8M", "2M"]

ax[1].set_title("Algoritmos dividir y conquistar")
ax[1].set_ylabel("Tiempo [s]")
ax[1].set_xlabel("Tamaño del vector")
ax[1].legend()
ax[1].set_xticks(div_and_con_x)
ax[1].set_xticklabels(div_and_con_x_label)
ax[1].grid()
ax[1].set_ylim((0,8))



for i in range(len(sorting_time)):
	ax[0].plot(x[:-9], sorting_time[i][:14], label=sort_list[i], color=colors[sort_list[i]])


ax[0].set_title("Algoritmos cuadraticos")
ax[0].set_ylabel("Tiempo [s]")
ax[0].set_xlabel("Tamaño del vector")
ax[0].legend()
ax[0].set_xticks(cuadratic_x)
ax[0].set_xticklabels(cuadratic_x_label)
ax[0].grid()


#PLOT MAXIMUN VALUE TO 100
folder = "Sort/Datasets/vectorInt Random 100 max value/Sorted/"

sort_list = ["quicksort", "quicksortRandomPivot","mergesort","mergesortInPlace","heapsort", "std_sort","bubblesort","insertionsort","selectionsort"]
sorting_time = []

for sort_name in sort_list:
	file = open(folder+sort_name+".txt","r") 
	data = file.readlines()
	file.close() 

	sorting_time.append(np.array([float(x) for x in data[0].split(";")[:-1]], dtype = np.float32))

fig, ax = plt.subplots(1,2, figsize=(15,6))
fig.suptitle("Vector aleatoreo con valores de 0-100")

x = range(1000,100001,1000)

for i in range(len(sorting_time)-3):
	ax[1].plot(x, sorting_time[i], label=sort_list[i], color=colors[sort_list[i]])

x_ticks = range(0, 100001, 10000)
x_ticks_label = ["0", "10k", "20k", "30k", "40k", "50k", "60k", "70k", "80k", "90k", "100k"]

ax[1].set_title("Algoritmos dividir y conquistar")
ax[1].set_ylabel("Tiempo [s]")
ax[1].set_xlabel("Tamaño del vector")
ax[1].legend()
ax[1].set_xticks(x_ticks)
ax[1].set_xticklabels(x_ticks_label)
ax[1].grid()



for i in range(len(sorting_time)):
	ax[0].plot(x, sorting_time[i], label=sort_list[i], color=colors[sort_list[i]])


ax[0].set_title("Algoritmos cuadraticos")
ax[0].set_ylabel("Tiempo [s]")
ax[0].set_xlabel("Tamaño del vector")
ax[0].legend()
ax[0].set_xticks(x_ticks)
ax[0].set_xticklabels(x_ticks_label)
ax[0].grid()
plt.show()