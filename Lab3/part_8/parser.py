import sys
counter=0
if len(sys.argv)<3:
	print("Please enter valid arguments")
file=sys.argv[1]
axis=sys.argv[2]
index=0
if axis=="x":
	index=1
elif axis =="y":
	index=2
elif axis =="z":
	index=3
elif axis == "time":
	index=4
#writen = open("timing.txt","w")
xw = open("xing.txt","w")
yw = open("ying.txt","w")
zw = open("zing.txt","w")
try:
    f=open(file,"r")
except OSError:
    print ("Could not open/read file:")
    sys.exit()
text=f.readlines()
past=0
for x in text:
	holder= x.replace(" ","")
	holder= holder.replace(",","")
	split_arr=holder.split(":")
	#print(str(split_arr))
	if len(split_arr)!=4: #for reqular
	#if len(split_arr)!=5: #for onHour File
		#writen.write("\n")
		continue
	#if(counter == 0):
	#if(int(split_arr[4][:-1])>past):
		#writen.write(split_arr[4][:-1])
	xw.write(split_arr[1][:-1])
	yw.write(split_arr[2][:-1])
	zw.write(split_arr[3][:-1])
	#writen.write("\n")
	xw.write("\n")
	yw.write("\n")
	zw.write("\n")
		#past=int(split_arr[4][:-1])
	#counter=counter+1
xw.close()
yw.close()
zw.close()
f.close()
