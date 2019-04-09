package calc;
public class Matrix{
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

    public Matrix(int row,int column) {
        this.row = row;
        this.column = column;
        this.matrix = new double[this.row][this.column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                this.matrix[i][j] = 0;
            }
        }
    }

    /**
     * �w�肵���s���̒P�ʍs��i�����s��j��Ԃ��B
     * @param length {int} �s��
     * @return e {Matrix} �P�ʍs��
     */
    public static Matrix identity(int length){
        double[][] tmp = new double[length][length];
        for(int i=0;i<length;i++){
            for(int j=0;j<length;j++){
                if(i==j) tmp[i][j] = 1;
                else tmp[i][j] = 0;
            }
        }
        Matrix e = new Matrix(tmp);
        return e;
    }
    /**
	 * �s�񓯎m�E�s��ƃx�N�g���̐ς��v�Z����i[matrix] this * [matrix] target
	 * @param target {Matrix} �|������s��or�x�N�g��
	 * @return result {Matrix} �ρi�s��j
	 */
	public Matrix multiply(Matrix target){
		Matrix result = new Matrix(this.row,target.column);
		for(int k=0;k<this.row;k++){
			for(int n=0;n<target.column;n++){
				double resultElement = 0.0;
				for(int i=0;i<target.row;i++){
					resultElement+=this.matrix[k][i] * target.matrix[i][n];
				}
				result.matrix  [k][n] = resultElement;
			}
		}
		result.row = result.matrix.length;
		result.column = result.row;
	    return result;
    }
    
    /**
	 * �s��̈ꕔ��\������(debug�p)
	 */
	public void display(){
		for(int i=0;i<4;i++){
			System.out.print("[");
			for(int j=0;j<4;j++){
			    if(j == 3) System.out.print(this.matrix[i][j]);
			    else                        System.out.print(this.matrix[i][j] + " ");
			}
			System.out.print("]\n");
		}
	}
}
