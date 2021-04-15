#!/usr/bin/python3

import os, sys
import numpy as np

sys.path.insert(0, '../module')
import libpysu as su 

if len(sys.argv)!=3:
     print("Usage: cpy a.su b.su\n"
            "    copy data only to create b.su from empty!\n");
     sys.exit(1);

aname = sys.argv[1]
bname = sys.argv[2]
##########################################################################
# create a dataset from scratch
##########################################################################
su1   = su.open(aname, su.READONLY)
ninst = su.ninst(su1)
nsamp = su.nsamp(su1)
#print("#ninst=",ninst,"nsamp=",nsamp)

su2   = su.open(bname, su.CREATE)
su.nsamp(su2, nsamp)

for i in range(ninst):
    v1 = su.read(su1, "trace", i, 1)
    v2 = -1*v1
    su.write(su2, "trace", v2, i, 1)

ns = nsamp*np.ones(ninst)
su.write(su2, "ns", ns, 0, ninst)

su.close(su1)
su.close(su2)

print("# test-2py success")
