package pr2calc;
// import pr2calc.Matrix;
public class SimultaneousEquation extends Matrix{
	protected double[] answers;

	// constractor
	public SimultaneousEquation(double[][] input){
		super(input);
		this.answers = new double[this.numOfColumn];
	}

	/**
	 * 指定した行の対角成分を1にする
	 * @param row {int} 行数
	 */
	public void normalize(int row){
		row-=1;
		double divisor = this.m[row][row];
		for(int j=0;j<this.numOfColumn;j++){
			this.m[row][j] /= divisor;
		}
	}
	
	/**
	 * 行列内の指定した行ベクトル（1行の行列）を定数倍する
	 * @param row {int} 行
	 * @param multiplier {double} かける数
	 */
	public void constantFactor(int row,double multiplier){
		row-=1;
		for(int i=0;i<this.m[row].length;i++){
			this.m[row][i] *= multiplier;
		}
	}
	/**
	 * 行列(this)内の行ベクトル(row1)から、行ベクトル(row2)を引く
	 * @param row1 {int} 引く行
	 * @param row2 {int} 引かれる行
	 */
	public void vectorSubtraction(int row1,int row2){
		row1-=1;
		row2-=1;
		for(int i=0;i<this.numOfColumn;i++){
			this.m[row2][i] -= this.m[row1][i];
		}
	}

	/**
	 * 対角成分が1となった行全体に適切な値を乗じ、その他の特定の行の対応する列の要素が0となるように差し引く
	 * @param row1 {int} 引く行
	 * @param row2 {int} 引かれる行
	 */
	public void subtractRowFrom(int row1,int row2){
		row1-=1;
		row2-=1;
		// System.out.println(this.m[row1][row1]);
		if(this.m[row1][row1]!=1){
			System.out.println("[SimultaneousEquation.subtractRowFrom] 引く行の要素が1ではありません\n"+
			                    this.m[row1][row1]+"です");
			System.exit(0);			
		}else{
			double multiplier  = this.m[row2][row1];
			this.constantFactor(row1+1, multiplier);
			this.vectorSubtraction(row1+1,row2+1);
			this.constantFactor(row1+1, 1/multiplier);
		}
	}

	/**
	 * 掃き出し法を実現するメソッド
	 */
	public void solveByGaussJordan(){
		for(int i=0;i<this.numOfColumn-1;i++){
			System.out.println("\n"+(i+1)+"行"+(i+1)+"列目が1となるように割り、他の行の"+(i+1)+"列目が0となるように引く");
			this.normalize(i+1);
			for(int j=0;j<this.numOfRow;j++){
				if(i!=j){
					this.subtractRowFrom(i+1,j+1);
				}
			}
			this.display("matrix");
		}
		System.out.println("\nAnswer:");		
		for(int i=0;i<this.numOfRow;i++){
			this.answers[i] = this.m[i][numOfColumn-1];
			if(i==this.numOfRow-1)System.out.print("x"+(i+1)+" = "+this.answers[i]+".\n");
			else System.out.print("x"+(i+1)+" = "+this.answers[i]+", ");
		}
	}
}