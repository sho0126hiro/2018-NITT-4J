package pr2calc;

public class SimultaneousEquation extends Matrix{
	protected double[] answers;
	protected int[] deal; // 解の順番を格納する

	// constractor
	public SimultaneousEquation(double[][] input){
		super(input);
		this.answers = new double[this.numOfRow];
		this.deal    = new int[this.numOfColumn-1];
		for(int i=1;i<=this.numOfColumn-1;i++){
			deal[i-1] = i;
		}
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
	/**
	 *  指定された行ベクトルを定数倍し、引く
	 * @param row1 {int} 引く行
	 * @param row2 {int} 引かれる行
	 */
	public void vectorSubandFactor(int row1,int row2){
		row1-=1;
		row2-=1;
		for(int i=0;i<this.numOfColumn;i++){
			this.m[row2][i] -= this.m[row1][i];
		}
	}

	/**
	 * ガウスの消去法を行うメソッド
	 */
	public void solveByGauss(){
		for(int j=1;j<this.numOfRow;j++){
			for(int i=j;i<this.numOfRow;i++){
				double multiplier = this.m[i][j-1]/this.m[j-1][j-1];
				this.constantFactor(j, multiplier);
				this.vectorSubtraction(j, i+1);
				this.constantFactor(j,1/multiplier);
			}
			this.display("matrix");
			System.out.print("\n");
		}
		for(int j=this.numOfRow-1;j>=0;j--){
			double tmp = this.m[j][this.numOfRow];
			for(int i=this.numOfRow-1;i>=j;i--){
				tmp -= this.m[j][i] * answers[i];
			}
			this.answers[j] = tmp / this.m[j][j];
		}
		for(int i=0;i<this.answers.length;i++){
			if(i==this.numOfRow-1)System.out.print("x"+(i+1)+" = "+this.answers[i]+".\n");
			else System.out.print("x"+(i+1)+" = "+this.answers[i]+", ");
		}
	}

	/**
	 * 行列内の特定の2行を入れ替える
	 * @param row1 {int} 行番号 (1~)
	 * @param row2 {int} 行番号 (1~)
	 */
	protected void exchangeRows(int row1,int row2){
		row1-=1;
		row2-=1;
		double[] tmp = new double[this.numOfColumn];
		for(int i=0;i<this.numOfColumn;i++){
			tmp[i] = this.m[row1][i];
			this.m[row1][i] = this.m[row2][i];
			this.m[row2][i] = tmp[i];
		}
	}

	/**
	 * 行列内の特定の2列を入れ替える
	 * @param column1 {int} 列番号 (1~)
	 * @param column2 {int} 列番号 (1~)
	 */
	protected void exchangeColumns(int column1,int column2){
		column1-=1;
		column2-=1;
		double tmp;
		for(int i=0;i<this.numOfRow;i++){
			tmp = this.m[i][column1];
			this.m[i][column1] = this.m[i][column2];
			this.m[i][column2] = tmp;
		}
		int   tmp2;
		tmp2 = this.deal[column1];
		this.deal[column1] = this.deal[column2];
		this.deal[column2] = tmp2;
	}

	/**
	 * ピボットが含まれる列の中で絶対値が最大の要素が含まれる行番号を返す
	 * @param column {int} 列番号 (1~)
	 * @return row {int}  行番号 (1~)
	 */
	protected int selectPivotFromRow(int column){
		column -= 1;
		int row = column;
		for(int i=column;i<this.numOfRow;i++){
			if(Math.abs(this.m[row][column]) < Math.abs(this.m[i][column])){
				row = i;
			}
		}
		return row+1;
	}

	/**
	 * ガウスの消去法 - ピボットの部分選択法を行うメソッド
	 */
	public void solveByGaussWithPartialSelection(){
		for(int j=1;j<this.numOfRow;j++){
			this.exchangeRows(j,this.selectPivotFromRow(j));
			for(int i=j;i<this.numOfRow;i++){
				double multiplier = this.m[i][j-1]/this.m[j-1][j-1];
				this.constantFactor(j, multiplier);
				this.vectorSubtraction(j, i+1);
				this.constantFactor(j,1/multiplier);
			}
			this.display("matrix");
			System.out.print("\n");
		}
		for(int j=this.numOfRow-1;j>=0;j--){
			double tmp = this.m[j][this.numOfRow];
			for(int i=this.numOfRow-1;i>=j;i--){
				tmp -= this.m[j][i] * answers[i];
			}
			this.answers[j] = tmp / this.m[j][j];
		}
		for(int i=0;i<this.answers.length;i++){
			if(i==this.numOfRow-1)System.out.print("x"+(i+1)+" = "+this.answers[i]+".\n");
			else System.out.print("x"+(i+1)+" = "+this.answers[i]+", ");
		}
	}

	/**
	 * ピボットが含まれる行内で絶対値最大の要素が含まれる行列番号を返す
	 * @param column {int} ピボットが含まれる列番号
	 * @return element {int[]} [0]:行番号 [1]:列番号 data[0]行data[1]列
	 */
	protected int[] selectPivodFromRC(int column){
		column-=1;
		int row_tmp = column;
		int column_tmp = column;
		int[] element = new int[2];
		for(int i=column;i<this.numOfRow;i++){
			for(int j=column;j<this.numOfColumn-1;j++){
				if(Math.abs(this.m[row_tmp][column_tmp]) < Math.abs(this.m[i][j])){
					column_tmp = j;
					row_tmp = i;
				}
			}
		}
		element[0] = row_tmp + 1;
		element[1] = column_tmp + 1;
		return element;
	}
	/**
	 * 現在のピボットとピボットにしたい要素を入れ替えるように
	 * 行と列（[r1][c2]と[r2][c2]）を入れ替えるメソッド
	 * @param r1,c1 {int} 交換前の行、列番号 (1~)
	 * @param r1,c2 {int} 交換後の行、列番号 (1~)
	 */
	protected void exchangeRowsAndColumns(int r1,int c1,int r2,int c2){
		this.exchangeRows(r1,r2);
		this.exchangeColumns(c1,c2);
	}

	/**
	 * ガウスの消去法 - ピボットの完全選択法を行うメソッド
	 */
	public void solveByGaussWithCompleteSelection(){
		for(int j=1;j<this.numOfRow;j++){
			// this.exchangeRows(j,this.selectPivotFromRow(j));
			int[] data = this.selectPivodFromRC(j);
			this.exchangeRowsAndColumns(j,j,data[0],data[1]);
			this.display("matrix");
			for(int i=j;i<this.numOfRow;i++){
				double multiplier = this.m[i][j-1]/this.m[j-1][j-1];
				this.constantFactor(j, multiplier);
				this.vectorSubtraction(j, i+1);
				this.constantFactor(j,1/multiplier);
			}
			System.out.print("\n");
		}
		for(int j=this.numOfRow-1;j>=0;j--){
			double tmp = this.m[j][this.numOfRow];
			for(int i=this.numOfRow-1;i>=j;i--){
				tmp -= this.m[j][i] * answers[i];
			}
			this.answers[j] = tmp / this.m[j][j];
		}
		int count = 1;
		for(int i=0;i<this.deal.length;i++){
			for(int j=0;j<this.deal.length;j++){			
			if(deal[i] == j+1){
					if(i==this.numOfRow-1)System.out.print(" x"+count+" = "+this.answers[deal[j]-1]+".\n");
					else System.out.print(" x"+count+" = "+this.answers[deal[j]-1]+",");
					count++;
				}
			}
		}
	}
}