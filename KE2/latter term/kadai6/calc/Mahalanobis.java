package calc;

public class Mahalanobis{
    protected double[] source; // ���̃f�[�^[DIM]
    protected double[] mean;   // ����[DIM]
    protected double[] lambda;  // �ŗL�l[DIM]
    protected double[][] E;    // �ŗL�x�N�g��(��x�N�g���j[DIM][DIM]
    public static final int DIM = 196;
    protected double bias;
    
    /**
     * @param source
     * @param mean
     * @param lamda
     * @param E
     */
    public Mahalanobis(double[] source,double[] mean,double[] lambda,double[][] E) {
        this.source   = new double[DIM];
        this.mean     = new double[DIM];
        this.lambda   = new double[DIM];
        this.E        = new double[DIM][DIM];
        for(int i=0;i<DIM;i++){
            this.source[i] = source[i];
            this.mean[i]   = mean[i];
            this.lambda[i]  = lambda[i];
            for(int j=0;j<DIM;j++){
                this.E[i][j] = E[i][j];
            }
        }
        this.bias = 20;
    }

    /**
     * �}�n���m�r�X�������v�Z����
     */
    public double CalcMahalanobisDistance(){
        double result=0.0;
        int i,j;
        for(j=0;j<DIM;j++){
            double[] tmp = new double[DIM];
            for(i=0;i<DIM;i++){
                tmp[i] = this.source[i] - this.mean[i];
            }
            double innerproduct = 0.0;
            for(i=0;i<DIM;i++){
                innerproduct += tmp[i]*this.E[i][j];
            }
            // innerproduct /= this.lambda[j];
            innerproduct = Math.pow(innerproduct,2);
            if(this.bias<this.lambda[j]){
                innerproduct /= this.lambda[j];
            }else{
                innerproduct /= (this.lambda[j]+this.bias);
            }
            result += innerproduct;
        }
        return result;
    }
}