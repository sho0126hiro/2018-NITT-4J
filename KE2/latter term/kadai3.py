# coding: utf-8
import numpy as np
import math
# from numba import jit

DIM = 196
CTGRY = 1
DATASIZE = 180

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

# 行列のクラス
class Matrix:
    # data[[]]
    def __init__(self,data):
        self.matrix = data             # ndarry[[]]
        self.row    = data.shape[0]    # row
        self.column = data.shape[1]    # column

# ヤコビ法計算クラス  < Matrix
class Jacobi(Matrix):
    def __init__(self,matrix):
        super().__init__(matrix)
        self.k = 0 # 試行回数K
        self.K_MAX = 1000 # 試行回数の最大          (本来ならもっと増やす)
        self.A_MIN = 100 # 非対角行列の要素の最小値 (本来なら0.001ぐらいの値にする)
    
    def getTheta(self,row,column):
        '''P_kに与える行列を得る'''
        tmp = self.matrix[column][column] - self.matrix[row][row]
        if tmp == 0 : return np.pi/4
        result = np.arctan(2*self.matrix[row][column]/tmp)
        result/= 2
        return result
    def getAbsMax(self):
        '''
        行列（ndarry)のなかの非対角成分で絶対値が最大のインデックス(配列番号)を返す  
        @return cdn (list) 絶対値最大のij >> [i,j]
        '''
        tmp = np.abs(self.matrix)
        l = self.row
        for i in range(l):
            tmp[i][i] = 0
        arg_max = np.argmax(tmp)
        a = arg_max // l
        b = arg_max % l
        cdn = [a,b]
        return cdn
    
    def createMatrixP(self,i,j,theta):
        '''
        i,j,行列についてのP行列を算出する
        @param i,j : i行（番号）j列（番号）
        @return ndarry P行列
        '''
        listP =[[1 if i==j else 0 for i in range(196)] for j in range(196)]
        listP[i][i] = np.cos(theta)
        listP[i][j] = np.sin(theta)
        listP[j][i] = -1 * np.sin(theta)
        listP[j][j] = np.cos(theta)
        ndarrayP = np.array(listP)
        return ndarrayP

    def nextMatrix(self,i,j,theta):
        '''
        Pk^-1 A P の計算
        '''
        # tmp = [x[:] for x in self.matrix] # 2次元配列の値渡し
        tmp = np.copy(self.matrix)
        co = np.cos(theta)
        si = np.sin(theta)
        for k in range(DIM):
            self.matrix[i][k] = tmp[i][k] * co - tmp[j][k] * si
            self.matrix[j][k] = tmp[i][k] * si + tmp[j][k] * co
            self.matrix[k][i] = tmp[k][i] * co - tmp[k][j] * si
            self.matrix[k][j] = tmp[k][i] * si + tmp[k][j] * co

    
    def checkMatrixLambda(self,threshold):
        '''
        全要素が閾値以下かを調べる
        @param   閾値
        @return  閾値以下でない：false 閾値以上：true
        '''
        for i in range(self.row):
            for j in range(i+1,self.column):
                if abs(self.matrix[i][j]) >= threshold :
                    return False
        return True
    
    # ヤコビ行列から固有値・固有ベクトルを求める
    def JacobiMethod(self):
        while True:
            maxdata = self.getAbsMax()
            i = maxdata[0]
            j = maxdata[1]
            print(str(self.k)+" "+str(self.matrix[i][j]))
            if abs(self.matrix[i][j]) < self.A_MIN:
                break
            theta = self.getTheta(i,j)
            # P_k = self.createMatrixP(i,j,theta)
            # self.matrix = np.dot(P_k.T,self.matrix)
            # self.matrix = np.dot(self.matrix,P_k)
            # self.nextMatrix(i,j,theta)
            ###############################
            tmp = np.copy(self.matrix)
            co = np.cos(theta)
            si = np.sin(theta)
            for k in range(DIM):
                self.matrix[i][k] = tmp[i][k] * co - tmp[j][k] * si
                self.matrix[j][k] = tmp[i][k] * si + tmp[j][k] * co
                self.matrix[k][i] = tmp[k][i] * co - tmp[k][j] * si
                self.matrix[k][j] = tmp[k][i] * si + tmp[k][j] * co
            ###############################
            self.k+=1
            if self.k > self.K_MAX:
                break

def main():
    for ctgry in range(CTGRY):
        # 共分散行列の読み込み
        sigma = fileRead_sigma('./sigma/sigma{0:02d}.txt'.format(ctgry+1))
        # 全ての対角成分を0に近づける
        narrayA = np.array(sigma)
        matA = Jacobi(narrayA)
        matA.JacobiMethod()
        print(matA.k)
        print(matA.matrix)
        out = list(matA.matrix)
        # 出力
        wfname = './test.txt'
        fileWrite(wfname,out)

if __name__ == '__main__':
    main()
