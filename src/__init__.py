#!/usr/bin/env python
# encoding=utf-8

# Created by vfx at October 10/31/24 (21:25:23)

# author        : Seongcheol Jeon
# project       : FTH_AR
# file path     : src/__init__.py
# created date  : 2024.10.31
# modified date : 2024.10.31
# description   : 


from . import _FTHArResolver
from pxr import Tf


Tf.PrepareModule(_FTHArResolver, locals())
del Tf

try:
    import __DOC
    __DOC.Execute(locals())
    del __DOC
except Exception:
    try:
        import __tmpDoc
        __tmpDoc.Execute(locals())
        del __tmpDoc
    except:
        pass
