import os, sys
import numpy as np

sys.path.insert(0, './module')
import libpysu as su 

##########################################################################
# create a dataset from scratch
##########################################################################
su1   = su.open("model_cp.su", su.READONLY)
ninst = su.ninst(su1)
nsamp = su.nsamp(su1, 0)
print("#ninst=",ninst,"nsamp=",nsamp)

su2   = su.open("model_test2py.su", su.CREATE)
su.nsamp(su2, nsamp)

for i in range(ninst):
    v1 = su.read(su1, "trace", i, 1)
    v2 = -1*v1
    su.write(su2, "trace", v2, i, 1)

ns = nsamp*np.ones(ninst)
su.write(su2, "ns", ns, 0, ninst)

su.close(su1)
su.close(su2)

print("#Reach success!")
