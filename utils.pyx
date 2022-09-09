# distutils: extra_compile_args = -fopenmp
# distutils: extra_link_args = -fopenmp
# cython: profile = True
# distutils:language = c++

from libcpp.vector cimport vector
import numpy as np
import pandas as pd
from cython cimport boundscheck, wraparound, nonecheck, cdivision

cdef extern from "stats.h" namespace "ALPHA":
    cdef vector[double] function1(const vector[double] & X, const vector[double] & Y) 
    cdef vector[vector[double]] function1plus(const vector[vector[double]] &X, const vector[double] &y)
    cdef vector[vector[double]] function2(const vector[vector[double]] &X)
    cdef double w_corr(vector[double] &x, vector[double] &y, double ls_ratio, double power)


def corr1(double[:] X, double[:] Y):
    cdef int length = X.shape[0]
    cdef vector[double] _X, _Y
    cdef int i 
    for i in range(length):
        _X.push_back(X[i])
        _Y.push_back(Y[i])
    return function1(_X, _Y)

def corr1plus(double[:,:] X, double[:] y):
    cdef int row = X.shape[0]
    cdef int col = X.shape[1]
    cdef vector[vector[double]] X_vector
    X_vector.resize(row)
    for i in range(row):
        for j in range(col):
            X_vector[i].push_back(X[i][j])

    cdef int length = y.shape[0]
    cdef vector[double] y_vector
    for i in range(length):
        y_vector.push_back(y[i])
    
    corr_table = pd.DataFrame(function1plus(X_vector, y_vector)).T
    return corr_table

def corr2(double[:,:] X):
    cdef int row = X.shape[0]
    cdef int col = X.shape[1]
    cdef vector[vector[double]] X_vector
    X_vector.resize(row)
    for i in range(row):
        for j in range(col):
            X_vector[i].push_back(X[i][j])
    df_corr = pd.DataFrame(function2(X_vector)).T
    return df_corr

def weighted_ic(double[:] x, double[:] y, double ls_ratio=1, double power=1):
    cdef int length = x.shape[0]
    cdef vector[double] _x,_y
    cdef int i
    for i in range(length):
        _x.push_back(x[i])
        _y.push_back(y[i])
    return w_corr(_x,_y,ls_ratio,power)

@boundscheck(False)
@wraparound(False)
@nonecheck(False)
@cdivision(True)
cdef double mean(double[:] x):
    cdef int length = x.shape[0]
    cdef int i
    cdef double res = 0
    for i in range(length):
        res += x[i]
    return res/length

@boundscheck(False)
@wraparound(False)
@nonecheck(False)
@cdivision(True)
def grp_return(double[:] y, int grp_tot):
    cdef double[:] res
    res = np.zeros(grp_tot,dtype=np.float64)
    cdef int grp_num = y.shape[0] // grp_tot
    cdef int i
    for i in range(grp_tot):
        res[i] = mean(y[i*grp_num: (i+1)*grp_num])
    return np.asarray(res)

