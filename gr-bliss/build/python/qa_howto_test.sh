#!/bin/sh
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/traviscollins/git/blocks/gr-bliss/python
export PATH=/home/traviscollins/git/blocks/gr-bliss/build/python:$PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DYLD_LIBRARY_PATH
export DYLD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DYLD_LIBRARY_PATH
export PYTHONPATH=/home/traviscollins/git/blocks/gr-bliss/build/swig:$PYTHONPATH
/usr/bin/python /home/traviscollins/git/blocks/gr-bliss/python/qa_bliss.py 
