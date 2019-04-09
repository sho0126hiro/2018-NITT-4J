package calc;

import calc.Matrix;

public class Jacobi extends Matrix{
    protected int k;
    protected int K_MAX;
    protected double A_MIN;
    public int DIM;
    public double[][] ResultP;

    public Jacobi(double[][] input) {
        super(input);
        this.K_MAX = 100000;
        this.A_MIN = 0.01;
        this.DIM = 196;
        this.ResultP = new double[DIM][DIM];
    } 

    /**
     * 行列の中の絶対値最大のインデックスを取得する
     */
    public int[] getAbsMax(){
        double tmp = 0;
        int cdn[] = {0,0};
        for(int i=0;i<this.row;i++){
            for(int j=i+1;j<this.column;j++){
                if(Math.abs(this.matrix[i][j]) > tmp){
                    tmp = Math.abs(this.matrix[i][j]);
                    cdn[0] = i;
                    cdn[1] = j;
                }
            }
        }
        return cdn;
    }
    
    public double getTheta(int i,int j){
        double tmp = this.matrix[j][j]-this.matrix[i][i];
        if(tmp == 0){
            System.out.println("hit");
            return Math.PI/4;
        }
        return 0.5 * Math.atan(2*this.matrix[i][j]/(tmp));
    }

    public void JacobiMethod(){
        Matrix E = identity(DIM);
        Matrix P = identity(DIM);
        for(int k=0;k<this.K_MAX;k++){
            int[] maxdata = this.getAbsMax();
            int i = maxdata[0];
            int j = maxdata[1];

            if(Math.abs(this.matrix[i][j])<this.A_MIN){
                System.out.println("OUT " + k+" "+this.matrix[i][j]);        
                break;
            }
            // P^-1APの計算
            // System.out.println(k+" "+this.matrix[i][j]+" "+i+" "+j);
            Matrix tmp = new Matrix(this.matrix);
            
            double theta = this.getTheta(i, j);
            double co = Math.cos(theta);
            double si = Math.sin(theta);
            double si2 = Math.sin(theta*2);
            double co2 = Math.cos(theta*2);
            for(int x=0;x<DIM;x++){
                this.matrix[i][x] = tmp.matrix[i][x] * co - tmp.matrix[j][x] * si;
                this.matrix[j][x] = tmp.matrix[i][x] * si + tmp.matrix[j][x] * co;
                this.matrix[x][i] = this.matrix[i][x];
                this.matrix[x][j] = this.matrix[j][x];
            }
            this.matrix[i][i] = (tmp.matrix[i][i]+tmp.matrix[j][j])*0.5 + (tmp.matrix[i][i]-tmp.matrix[j][j])*co2 * 0.5 - tmp.matrix[i][j]*si2; 
            this.matrix[j][j] = (tmp.matrix[i][i]+tmp.matrix[j][j])*0.5 - (tmp.matrix[i][i]-tmp.matrix[j][j])*co2*0.5 + tmp.matrix[i][j]*si2; 
            this.matrix[i][j] = 0;
            this.matrix[j][i] = 0;
            // this.display();
            // 固有ベクトルの計算
            Matrix now = new Matrix(E.matrix);
            tmp = new Matrix(P.matrix);
            now.matrix[i][i] = co;
            now.matrix[i][j] = si;
            now.matrix[j][i] = -1*si;
            now.matrix[j][j] = co;
            // P = P.multiply(now);
            // P = P*now
            for(int x=0;x<DIM;x++){
                P.matrix[x][i] = tmp.matrix[x][i] * now.matrix[i][i] + tmp.matrix[x][j] * now.matrix[j][i];
                P.matrix[x][j] = tmp.matrix[x][i] * now.matrix[i][j] + tmp.matrix[x][j] * now.matrix[j][j];
            }
            // P.display();
            // System.out.println("*******************************************");
        }
        for(int i=0;i<DIM;i++){
            for(int j=0;j<DIM;j++){
                this.ResultP[i][j] = P.matrix[i][j];
            }
        }
    }

    public double[] getEigenvalues(){
        double[] result = new double[DIM];
        for(int i=0;i<DIM;i++){
            result[i] = this.matrix[i][i];
        }
        return result;
    }
}