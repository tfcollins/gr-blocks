#!/bin/sh
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/traviscollins/git/blocks/gr-BLISS/python
export PATH=/home/traviscollins/git/blocks/gr-BLISS/build/python:$PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DYLD_LIBRARY_PATH
export DYLD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DYLD_LIBRARY_PATH
export PYTHONPATH=/home/traviscollins/git/blocks/gr-BLISS/build/swig:$PYTHONPATH
/usr/bin/python /home/traviscollins/git/blocks/gr-BLISS/python/qa_BLISS_vector_conjugate.py 
