import java.io.*;



public final int DIM = 196;
public final int DATASIZE = 180;
public final int  CTGRY = 1;
public final int K_MAX = 10000;
public final double A_MIN = 100;


private class Matrix{
    public double[][] matrix;
    public int row;
    public int column;
    
    public Matrix(double[][] input) {
        this.row = input.length;
        this.column = input[0].length;
        this.matrix = new double[this.row][this.column];
        for (int i = 0; i < input.length; i++) {
            for (int j = 0; j < input[0].length; j++) {
                this.matrix[i][j] = input[i][j];
            }
        }
    }
    /**
	 * �s���E�񐔂��w�肵�ď�����
	 * @param Row
	 * @param Column
	 */
	public Matrix(int Row,int Column){
		this.row       = Row;
		this.column    = Column;
		this.matrix = new double[this.row][this.column];
	}
    /**
	 * �s��̐ώZ���\�����肷��(X �~ Y)
	 * @param x	{Matrix} �|������s��
	 * @param y	{Matrix} �|����s��
	 * @return `{boolean}
	 */
	public static boolean multipliable(Matrix x ,Matrix y){
		if(x.column!=y.row)return false;
		return true;
    }
    
    /**
	 * �s�񓯎m�E�s��ƃx�N�g���̐ς��v�Z����i[matrix] this * [matrix] target
	 * @param target {Matrix} �|������s��or�x�N�g��
	 * @return result {Matrix} �ρi�s��j
	 */
	public Matrix multiplyMatrix(Matrix target){
		// �|������s��̗񐔂Ɗ|����s��̍s�����������Ȃ�
		Matrix result = new Matrix();
		if(multipliable(this,target)){
			// �ς̌v�Z��������������
			result.matrix = new double [this.row][target.column];
			for(int k=0;k<this.row;k++){
				for(int n=0;n<target.column;n++){
					double resultElement = 0.0;
					for(int i=0;i<target.row;i++){
						resultElement+=this.matrix[k][i] * target.matrix[i][n];
					}
					result.matrix[k][n] = resultElement;
				}
			}
			result.row = result.matrix.length;
			result.column = result.matrix[0].length;
        }else{
            System.out.println("[Matrix.multiplyMatrix] �v�f�����v�Z�ł���g�ݍ��킹�ƂȂ��Ă��܂���");
            System.exit(0);
        }
		// �ς̌��ʂ�Matrix�^�ŕԂ�
		return result;
    }
    /**
	 * �s�񓯎m�E�s��ƃx�N�g���̐ς��v�Z����i[matrix] a * [matrix] b
	 * @param a {Matrix} �|����s��or�x�N�g��
	 * @param b {Matrix} �|������s��or�x�N�g��     * 
	 * @return result {Matrix} �ρi�s��j
	 */
	public Matrix multiplyMatrix2(Matrix a,Matrix b){
		// �|������s��̗񐔂Ɗ|����s��̍s�����������Ȃ�
		Matrix result = new Matrix();
		if(multipliable(a,b)){
			// �ς̌v�Z��������������
			result.matrix = new double [a.row][b.column];
			for(int k=0;k<a.row;k++){
				for(int n=0;n<b.column;n++){
					double resultElement = 0.0;
					for(int i=0;i<b.row;i++){
						resultElement+=a.matrix[k][i] * b.m[i][n];
					}
					result.matrix[k][n] = resultElement;
				}
			}
			result.row = result.matrix.length;
			result.column = result.matrix[0].length;
        }else{
            System.out.println("[Matrix.multiplyMatrix] �v�f�����v�Z�ł���g�ݍ��킹�ƂȂ��Ă��܂���");
            System.exit(0);
        }
		// �ς̌��ʂ�Matrix�^�ŕԂ�
		return result;
	}
    /**
	 * this�̓]�u�s���Ԃ����\�b�h
	 * @return result {Matrix} �]�u�s��
	 */
	public Matrix transpose(){
		Matrix result = new Matrix(this.column,this.row);
		for(int i=0;i<this.row;i++){
			for(int j=0;j<this.column;j++){
				result.matrix[j][i] = this.matrix[i][j];
			}
		}
		return result;
	}
}

private class Jacobi extends Matrix{
    protected int k;
    protected int K_MAX;
    protected int A_MIN;

    public Jacobi(double[][] input) {
        super(input);
        this.k = 0;
        this.K_MAX = 10000;
        this.A_MIN = 1;
    } 

    public int[] getAbsMax(){
        double tmp = 0;
        int cdn[] = {0,0};
        for(int i=0;i<this.row;i++){
            for(int j=i+1;j<this.columns;j++){
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
        double result = Math.atan(2*this.matrix[i][j]/(this.matrix[j][j]-this.matrix[i][i]));
        result /= 2;
        return result;
    }

    public Matrix createMatrixP(int row,int col){
        double[][] Pk = new double[DIM][DIM];
        for(int i=0;i<DIM;i++){
            for(int j=0;j<DIM;j++){
                if(i==j)Pk[i][j] = 1;
                else Pk[i][j] = 0;
            }
        }
        double theta = this.getTheta(row,col);
        Pk[row][row] = Math.cos(theta);
        Pk[row][col] = Math.sin(theta);
        Pk[col][row] = -1 * Math.sin(theta);
        Pk[col][col] = Math.cos(theta);
        Matrix matPk = new Matrix(Pk);
        return matPk;
    }

    public boolean checkMatrixLambda(double threshold){
        for(int i=0;i<this.row;i++){
            for(int j=i+1;j<this.column;j++){
                if(Math.abs(this.matrix[i][j]) >= threshold){
                    return false;
                }
            }
        }
        return true;
    }

    public void JacobiMethod(){
        while(true){
            double[] maxdata = this.getAbsMax();
            int i = parseInt(maxdata[0]);
            int j = parseInt(maxdata[1]);
            if(Math.abs(this.matrix[i][j])<this.A_MIN){
                break;
            }
            Matrix p_k = this.createMatrixP(i, j);
            this = this.multiplyMatrix(p_k.transpose(),this);
            this = this.multiplyMatrix(this,p_k);
            this.k+=1;
            if(this.k > this.K_MAX){
                break;
            }
        }
    }
}

public class kadai3{
    

    public double[][] fileRead_sigma(String fname){
        try{
            BufferedReader bufferedReader = new BufferedReader(new FileReader(fname));
            double[][] sigma = new double[DIM][DIM];
            for(int i=0;i<this.DIM;i++){
                String[] line = bufferedReader.readLine().split("\t",0);
                for(int j=0;j<this.DIM;j++){
                    sigma[i][j] = parseDouble(line[j]);
                }
            }
            fileReader.close();
            return sigma;
        }catch(IOException e){
            e.printStackTrace();
            System.exit(0);
        }
    }

    public static void main(String[] args) {
        for(int i=0;i<CTGRY;i++){
            // * �t�@�C�����I��
            String fname;
            if(i<10)  fname= "./sigma/sigma"+0+i;
            else fname = "./sigma/shigma"+i;
            double[][] sigma =this.fileRead_sigma(fname);
            Jacobi matA = new Jacobi(sigma);
            matA.JacobiMethod();
        }
	}
}
