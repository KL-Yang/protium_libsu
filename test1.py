import os, sys
import numpy as np

sys.path.insert(0, './module')
import libpysu as su 

os.system("cp -f wav.su wav_test1py.su")
##########################################################################
# create a reversed dataset!
##########################################################################
su1   = su.open("wav_test1py.su", su.UPDATE)
ninst = su.ninst(su1)
nsamp = su.nsamp(su1)
ns = su.read(su1, "ns", 0, 1)
print("#ninst=",ninst,"nsamp=",nsamp,"ns=",ns)
names = su.attrs(su1)
print("#attr:", names)
t1 = su.getattr(su1, "trace")
print("#trace=", t1)
v1 = su.read(su1, "trace", 0, 1)
v2 = -1*v1
print("#shape=",v1.shape)
for i in range(v1.shape[1]):
    print(" %3d  %16e  %16e"%(i, v1[0][i], v2[0][i]))
su.write(su1, "trace", v2, 0, 1)
su.close(su1)
print("#Reach success!")
