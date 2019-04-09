# coding: utf-8
import numpy as np
import math
from numba import cuda

DIM = 196
CTGRY = 1
DATASIZE = 180

K_MAX = 100000
A_MIN = 1

griddim = 100, 100
blockdim = 16, 16

# return data[DIM][DIM]
def fileRead_sigma(fname):
    f = open(fname,'r')
    # 配列の静的確保 data[DIM][DIM]
    data = [[0 for i in range(DIM)] for j in range(DIM)]
    for i in range(DIM):
        line = f.readline().split('\t')
        for j in range(DIM):
            data[i][j] = float(line[j])
    f.close()
    return data

#data[DIM][DIM]
def fileWrite(fname,data):
    with open(fname, mode='w') as f:
        for i in data:
            for j in i:
                f.write(str(j)+"\t")
            f.write('\n')

# @jit('f8[:](f8[:,:])')
@cuda.jit
def getAbsMax(matrix):
    '''
    行列（ndarry)のなかの非対角成分で絶対値が最大のインデックス(配列番号)を返す  
    @return cdn (list) 絶対値最大のij >> [i,j]
    '''
    tmp = np.abs(matrix)
    l = matrix.shape[0] #行
    for i in range(l):
        tmp[i][i] = 0
    arg_max = np.argmax(tmp)
    a = arg_max // l
    b = arg_max % l
    cdn = [a,b]
    return cdn

# @cuda.jit('f8(f8[:,:],i8,i8)')
@cuda.jit
def getTheta(matrix,row,column):
    tmp = matrix[column][column] - matrix[row][row]
    if tmp == 0 : return np.pi/4
    result = np.arctan(2*matrix[row][column]/tmp)
    result/= 2
    return result

# @cuda.jit('f8[:,:](f8[:,:])')
@cuda.jit
def Jacobi(matrix):
    k_try = 0
    while True:
        maxdata = getAbsMax[griddim,blockdim](matrix)
        i = maxdata[0]
        j = maxdata[1]
        # print(str(k_try)+" "+str(matrix[i][j]))
        if abs(matrix[i][j]) < A_MIN:
            break
        theta = getTheta[griddim,blockdim](matrix,i,j)
        ###############################
        tmp = np.copy(matrix)
        co = np.cos(theta)
        si = np.sin(theta)
        for k in range(DIM):
            matrix[i][k] = tmp[i][k] * co - tmp[j][k] * si
            matrix[j][k] = tmp[i][k] * si + tmp[j][k] * co
            matrix[k][i] = tmp[k][i] * co - tmp[k][j] * si
            matrix[k][j] = tmp[k][i] * si + tmp[k][j] * co
        ###############################
        k_try +=1
        if k_try > K_MAX:
            break
    return matrix

def main():
    for ctgry in range(CTGRY):
        # 共分散行列の読み込み
        sigma = fileRead_sigma('./sigma/sigma{0:02d}.txt'.format(ctgry+1))
        # 全ての対角成分を0に近づける
        narrayA = np.array(sigma)
        out = Jacobi[griddim,blockdim](narrayA)
        # 出力
        print(out)
        # wfname = './test.txt'
        # fileWrite(wfname,out)

if __name__ == '__main__':
    main()
