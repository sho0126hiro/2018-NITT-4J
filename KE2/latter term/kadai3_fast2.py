# coding: utf-8
import numpy as np
import math
import time
from numba import jit

DIM = 196
CTGRY = 1
DATASIZE = 180

STEP_MAX = 1000000 # 試行回数
A_MIN = 0.001 #最小値

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
@jit
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

@jit('f8(f8[:,:],i8,i8)')
def getTheta(matrix,row,column):
    tmp = matrix[column][column] - matrix[row][row]
    if tmp == 0 : return np.pi/4
    result = np.arctan(2*matrix[row][column]/tmp)
    result/= 2
    return result

@jit('f8[:,:](f8[:,:])')
def Jacobi(matrix):
    for k_try in range(STEP_MAX+1):
        # 絶対値最大のインデックスを求める
        tmp = np.abs(matrix)
        for i in range(DIM):
            tmp[i][i] = 0
        arg_max = np.argmax(tmp)
        i = arg_max // DIM
        j = arg_max % DIM
        # 終了するかの判定
        if(k_try%10000==0): print("10000")
        # print(str(k_try)+" "+str(matrix[i][j]))
        if abs(matrix[i][j]) < A_MIN:
            print("out"+str(k_try)+" "+matrix[i][j])
            break
        # thetaを求める
        tmp = matrix[j][j] - matrix[i][i]
        if tmp == 0 :
            theta = np.pi/4
        else :
            theta = np.arctan(2*matrix[i][j]/tmp)
            theta /= 2
        ###############################
        tmp = np.copy(matrix)
        co = np.cos(theta)
        co2 = np.cos(theta*2)
        si = np.sin(theta)
        si2 = np.sin(theta*2)
        for x in range(DIM):
            matrix[i][x] = tmp[i][x] * co + tmp[j][x] * si;
            matrix[j][x] = -1* tmp[i][x] * si + tmp[j][x] * co;
            matrix[x][i] = matrix[i][x];
            matrix[x][j] = matrix[j][x];
        matrix[i][i] = (matrix[j][j]+matrix[j][i])*0.5 - (matrix[j][j]-matrix[j][i])*co2*0.5 + matrix[j][i]*si2; 
        matrix[j][j] = (matrix[j][j]+matrix[j][i])*0.5 + (matrix[j][j]-matrix[j][i])*co2*0.5 - matrix[j][i]*si2; 
        matrix[i][j] = 0;
        matrix[j][i] = 0;
        ###############################
    return matrix

def main():
    for ctgry in range(CTGRY):
        # 共分散行列の読み込み
        sigma = fileRead_sigma('./sigma/sigma{0:02d}.txt'.format(ctgry+1))
        # 全ての対角成分を0に近づける
        narrayA = np.array(sigma)
        t1 = time.time()
        out = Jacobi(narrayA)
        t2 = time.time()
        elapsed_time = t2-t1
        print(f"経過時間：{elapsed_time}")
        # 出力
        print(out)
        # wfname = './test.txt'
        # fileWrite(wfname,out)

if __name__ == '__main__':
    main()
