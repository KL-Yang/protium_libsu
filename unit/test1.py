#!/usr/bin/python3

import os, sys
import numpy as np

sys.path.insert(0, '../module')
import libpysu as su 

if len(sys.argv)!=3:
    print("Usage: inv a.su b.su\n"
        +"     copy su and inverse its value!");
    sys.exit(1)

aname = sys.argv[1]
bname = sys.argv[2]
os.system("cp -f %s %s"%(aname, bname))

##########################################################################
# create a reversed dataset!
##########################################################################
su1   = su.open(bname, su.UPDATE)
ninst = su.ninst(su1)
nsamp = su.nsamp(su1)
ns = su.read(su1, "ns", 0, 1)
print("#ninst=",ninst,"nsamp=",nsamp,"ns=",ns)
names = su.attrs(su1)
#print("#attr:", names)
t1 = su.getattr(su1, "trace")
#print("#trace=", t1)
v1 = su.read(su1, "trace", 0, ninst)
v2 = -1*v1
#print("#shape=",v1.shape)
error=0
for j in range(v1.shape[0]):
    for i in range(v1.shape[1]):
        if v1[j][i]!=(-1)*v2[j][i]:
            print(" %3d  %16e  %16e"%(i, v1[j][i], v2[j][i]))
            error=error+1
su.write(su1, "trace", v2, 0, ninst)
su.close(su1)
if error:
    print("# test-1py failed")
else:
    print("# test-1py success")
