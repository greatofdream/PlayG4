'''
convert the PlayG4 output root file to hdf5 using uproot
'''
import argparse

import uproot, h5py, numpy as np, pandas as pd

psr = argparse.ArgumentParser()
psr.add_argument('-i', dest='ipt', help='MC root file')
psr.add_argument('-o', dest='opt', help='output hdf5 name')
args = psr.parse_args()
print('begin to read the root file')
simtruth = uproot.open(args.ipt+":SimTruth")
simtrack = uproot.open(args.ipt+":SimTrack")
simstep = uproot.open(args.ipt+":SimStep")
# electron step array: The result array is hierarchical structure, have to use awkward array to do selection
step_dtype = [('eid', int), ('StepPoint_Pre_x', float), ('StepPoint_Pre_y', float), ('StepPoint_Pre_z', float), ('StepPoint_Post_x', float), ('StepPoint_Post_y', float), ('StepPoint_Post_z', float), ('StepLength', float), ('T', float), ('TrackId', int), ('E_k', float), ('dE', float), ('Px', float), ('Py', float), ('Pz', float), ('ProcessType', int), ('ProcessSubType', int)]
track_dtype = []
step_keys = ['StepPoint_Pre_x', 'StepPoint_Pre_y', 'StepPoint_Pre_z', 'StepPoint_Post_x', 'StepPoint_Post_y', 'StepPoint_Post_z', 'StepLength', 'T', 'TrackId', 'E_k', 'dE', 'Px', 'Py', 'Pz', 'ProcessType', 'ProcessSubType']
track_keys = ['ParentTrackId', 'TrackId', 'PdgId', 'ProcessType', 'ProcessSubType']
simstep_arr = simstep.arrays(step_keys, library='np')
step_len_arr = [len(arr) for arr in simstep_arr['TrackId']]
step_N = np.sum(step_len_arr)
simtrack_arr = simtrack.arrays(library='np')
print('finish read the root')
# reformat the data structure
simstep_ = np.zeros((step_N,), dtype=step_dtype)
simstep_['eid'] = np.repeat(np.arange(len(simstep_arr['TrackId'])), step_len_arr)
for key in step_keys:
    simstep_[key] = np.concatenate(simstep_arr[key])
# for i in len(simstep_arr):
#    simstep
with h5py.File(args.opt, 'w') as opt:
    opt.create_dataset('step', data=simstep_, compression='gzip')
