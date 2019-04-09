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
     * 指定した行数の単位行列（正方行列）を返す。
     * @param length {int} 行数
     * @return e {Matrix} 単位行列
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
	 * 行列同士・行列とベクトルの積を計算する（[matrix] this * [matrix] target
	 * @param target {Matrix} 掛けられる行列orベクトル
	 * @return result {Matrix} 積（行列）
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
	 * 行列の一部を表示する(debug用)
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
