#define DIM 196
#define CTGRY 1
#define DATASIZE 180

# return data[DATASIZE][DIM]
def fileRead(fname):
    f = open(fname,'r')
    data = []
    for i in range(DATASIZE):
        data.append([])
        for j in range(DIM):
            data[i].append(int(f.readline()))
    f.close()
    return data

def fileWrite(fname,data):
    f = open(fname,'w')
    for d in data:
        for e in d:
            f.write(str(e)+"\t")
        f.write("\n")
    f.close

def main():
    for ctgry in range(CTGRY):
        rfname = './data/c{0:02d}.txt'.format(ctgry+1)
        data = fileRead(rfname) # data[DATASIZE][DIM]
        #共分散行列を求める
        result = []
        for i in range(DIM):
            result.append([])
            for j in range(DIM):
                result[i].append(0)
                for k in range(DATASIZE):
                    # [k][I]の平均
                    mi = 0
                    mj = 0
                    for l in range(DATASIZE):
                        mi += data[l][i]
                        mj += data[l][j]
                    mi /= DATASIZE
                    mj /= DATASIZE
                    result[i][j] += ((data[k][i] - mi) * (data[k][j] - mj))
                result[i][j] /= DATASIZE
        wfname = './sigma/sigma{0:02d}.txt'.format(ctgry+1)
        print(wfname)        
        fileWrite(wfname,result)

if __name__ == '__main__':
    main()
