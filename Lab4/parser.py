import sys
counter=0
if len(sys.argv)<3:
	print("Please enter valid arguments")
file=sys.argv[1]
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
	split_arr=holder.split(",")
	if len(split_arr)!=3:
		continue
	xw.write(split_arr[1])
	yw.write(split_arr[2])
	zw.write(split_arr[3])
	xw.write("\n")
	yw.write("\n")
	zw.write("\n")
xw.close()
yw.close()
zw.close()
f.close()
