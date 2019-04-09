package calc;

public class BayesDiscriminant{
    protected double[] source; // ���̃f�[�^[DIM]
    protected double[] mean;   // ����[DIM]
    protected double[] lambda;  // �ŗL�l[DIM]
    protected double[][] E;    // �ŗL�x�N�g��(��x�N�g���j[DIM][DIM]
    public static final int DIM = 196;
    protected double alpha;
    protected double bias;
    protected double bias2;
    
    /**
     * @param source
     * @param mean
     * @param lamda
     * @param E
     */
    public BayesDiscriminant(double[] source,double[] mean,double[] lambda,double[][] E) {
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
        this.bias2 = 15;
        this.alpha = 0.8;
    }

    /**
     * �x�C�Y���ʊ֐����v�Z����
     */
    public double CalcBayesDiscriminant(){
        double first_term=0.0;
        double second_term=0.0;
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
            innerproduct = Math.pow(innerproduct,2);
            innerproduct /= (this.lambda[j]+this.bias);
            first_term += innerproduct;
        }
        first_term *= this.alpha;
        // first_term : ��ꍀ
        for (j=0;j<DIM;j++){
            second_term += Math.log(this.lambda[j]+this.bias2);
        }
        
        second_term = Math.log(second_term);
        second_term *= (1-this.alpha);
        double result = first_term + second_term;
        return result;
    }
}