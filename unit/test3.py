#!/usr/bin/python3

import os, sys
import numpy as np

sys.path.insert(0, '../module')
import libpysu as su 

# find the last trace in the group
def group_last(gather, first):
    the_last=len(gather)
    for i in range(first+1, the_last):
        if gather[i]!=gather[first]:
            return i-1
    return the_last-1
 
##########################################################################
# create a dataset from scratch
##########################################################################
su1   = su.open("shots.total.su", su.READONLY)
ninst = su.ninst(su1)
nsamp = su.nsamp(su1)
print("#ninst=",ninst,"nsamp=",nsamp)

fldr  = su.read(su1, "fldr", 0, ninst)
nshot,first,tr0,trn=0,0,[],[]
while first<ninst:
    last=group_last(fldr, first)
    tr0.append(first)
    trn.append(last-first+1)
    first=last+1
    nshot=nshot+1

for i in range(nshot):
    print("group[%4d] %8d->%8d"%(i, tr0[i], tr0[i]+trn[i]-1))

su2   = su.open("shots.test3py.su", su.CREATE)
su.nsamp(su2, nsamp)
for i in range(nshot):
    v1 = su.read(su1, "trace", tr0[i], trn[i])
    v1 = -1*v1
    su.write(su2, "trace", v1, tr0[i], trn[i])
    a1 = su.read(su1, "fldr", tr0[i], trn[i])
    su.write(su2, "fldr", a1, tr0[i], trn[i])
    a1 = nsamp*np.ones(trn[i])
    su.write(su2, "ns", a1, tr0[i], trn[i])

su.close(su1)
su.close(su2)

print("#Reach success!")
sys.exit(0)

#tracl = su.read(su1, "tracl", 0, ninst)
#print(tracl)
#tracr = su.read(su1, "tracr", 0, ninst)
#print(tracr)
#tracf = su.read(su1, "tracf", 0, ninst)
#print(tracf)
