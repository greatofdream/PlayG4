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
simtrackstep = uproot.open(args.ipt+":SimTrackStep")
# electron step array: The result array is hierarchical structure, have to use awkward array to do selection
step_dtype = [('EventID', int), ('PdgId', int), ('StepPoint_Pre_x', float), ('StepPoint_Pre_y', float), ('StepPoint_Pre_z', float), ('StepPoint_Post_x', float), ('StepPoint_Post_y', float), ('StepPoint_Post_z', float), ('StepLength', float), ('T', float), ('TrackId', int), ('E_k', float), ('dE', float), ('Px', float), ('Py', float), ('Pz', float), ('ProcessType', int), ('ProcessSubType', int)]
track_dtype = [('EventID', int), ('ParentTrackId', int), ('ParentStepId', int), ('TrackId', int), ('PdgId', int), ('ProcessType', int), ('ProcessSubType', int), ('StartPoint_x', float), ('StartPoint_y', float), ('StartPoint_z', float), ('T', float), ('Px', float), ('Py', float), ('Pz', float), ('E_k', float)]
truth_dtype = [('EventID', int), ('VertexId', int), ('x', float), ('y', float), ('z', float)]
step_keys = ['StepPoint_Pre_x', 'StepPoint_Pre_y', 'StepPoint_Pre_z', 'StepPoint_Post_x', 'StepPoint_Post_y', 'StepPoint_Post_z', 'StepLength', 'T', 'TrackId', 'E_k', 'dE', 'Px', 'Py', 'Pz', 'ProcessType', 'ProcessSubType', 'PdgId']
track_keys = ['ParentTrackId', 'TrackId', 'PdgId', 'ProcessType', 'ProcessSubType', 'StartPoint_x', 'StartPoint_y', 'StartPoint_z', 'T', 'Px', 'Py', 'Pz', 'E_k']
truth_keys = ['EventID', 'VertexId', 'x', 'y', 'z']
Entries = simstep.num_entries
simstep_arr = simstep.arrays(step_keys, library='np')
step_len_arr = [len(arr) for arr in simstep_arr['TrackId']]
step_N = np.sum(step_len_arr)

simtrack_arr = simtrack.arrays(track_keys, library='np')
track_len_arr = [len(arr) for arr in simtrack_arr['TrackId']]
track_N = np.sum(track_len_arr)

simtrackstep_arr = simtrackstep.arrays(['TrackId', 'StepId', 'StartPoint_x', 'StartPoint_y', 'StartPoint_z', 'T'], library='np')
trackstep_len_arr = [len(arr) for arr in simtrackstep_arr['TrackId']]

simtrackstep_df = pd.DataFrame({
    'EventID': np.repeat(np.arange(Entries), trackstep_len_arr),
    'TrackId': np.concatenate(simtrackstep_arr['TrackId']),
    'StepId': np.concatenate(simtrackstep_arr['StepId']),
    # 'ChildTrackId': np.concatenate(simtrackstep_arr['ChildTrackId']),
    'StartPoint_x': np.concatenate(simtrackstep_arr['StartPoint_x']),
    'StartPoint_y': np.concatenate(simtrackstep_arr['StartPoint_y']),
    'StartPoint_z': np.concatenate(simtrackstep_arr['StartPoint_z']),
    'T': np.concatenate(simtrackstep_arr['T']),
})

simtruth_arr = simtruth.arrays(library='np')
print('finish read the root')
# reformat the data structure
simstep_ = np.zeros((step_N,), dtype=step_dtype)
simstep_['EventID'] = np.repeat(np.arange(Entries), step_len_arr)
for key in step_keys:
    simstep_[key] = np.concatenate(simstep_arr[key])

simtrack_ = np.zeros((track_N,), dtype=track_dtype)
simtrack_['EventID'] = np.repeat(np.arange(Entries), track_len_arr)
for key in track_keys:
    simtrack_[key] = np.concatenate(simtrack_arr[key])
select_photon = (simtrack_['TrackId']!=1) & (simtrack_['PdgId']==0)
simtrack_['ParentStepId'][select_photon] = simtrackstep_df.set_index(['EventID', 'T']).loc[simtrack_[select_photon][['EventID', 'T']].tolist()]['StepId']
#.set_index('ChildTrackId').loc[simtrack_['TrackId']]['StepId']

simtruth_ = np.zeros((Entries,), dtype=truth_dtype)
for key in truth_keys:
    simtruth_[key] = simtruth_arr[key]
with h5py.File(args.opt, 'w') as opt:
    opt.create_dataset('SimStep', data=simstep_, compression='gzip')
    opt.create_dataset('SimTrack', data=simtrack_, compression='gzip')
    opt.create_dataset('SimTruth', data=simtruth_, compression='gzip')
