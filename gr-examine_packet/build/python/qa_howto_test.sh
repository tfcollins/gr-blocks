#!/bin/sh
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/traviscollins/git/blocks/gr-examine_packet/python
export PATH=/home/traviscollins/git/blocks/gr-examine_packet/build/python:$PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DYLD_LIBRARY_PATH
export DYLD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DYLD_LIBRARY_PATH
export PYTHONPATH=/home/traviscollins/git/blocks/gr-examine_packet/build/swig:$PYTHONPATH
/usr/bin/python /home/traviscollins/git/blocks/gr-examine_packet/python/qa_howto.py 
