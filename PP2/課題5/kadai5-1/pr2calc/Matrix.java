package pr2calc;


public class Matrix {
	// 必要なフィールド（インスタンス）変数の宣言
	public double[][] m;
	public int numOfRow; // 行数
	public int numOfColumn; // 列数
	
	/**
	 *  行列の行数,列数を格納するインスタンス変数の値を0に初期化
	 */ 
	public Matrix() {
		this.numOfColumn = 0;
		this.numOfRow    = 0;
	}
	
	/**
	 * 行数・列数を指定して初期化
	 * @param Row
	 * @param Column
	 */
	public Matrix(int Row,int Column){
		this.numOfRow       = Row;
		this.numOfColumn    = Column;
		this.m = new double[this.numOfRow][this.numOfColumn];
	}
	
	/**
	 * 二次元配列の内容で行列の初期化
	 * @param input {double[][]}
	 */
	public Matrix(double[][] input) {
		this.numOfRow = input.length;
		this.numOfColumn = input[0].length;
		this.m = new double[this.numOfRow][this.numOfColumn];
		for (int i = 0; i < input.length; i++) {
			for (int j = 0; j < input[0].length; j++) {
				this.m[i][j] = input[i][j];
			}
		}
	}

	/**
	 * 一次元配列の内容で行列を初期化
	 * @param input {double[]}
	 */
	public Matrix(double[] input) {
		this.numOfRow = 1;
		this.numOfColumn = input.length;
		this.m = new double[1][this.numOfColumn];
		for(int i=0;i<this.numOfColumn;i++){
			this.m[0][i] = input[i];
		}
	}

	/**
	 * @return {int} 行の長さ
	 */
	public int getNumOfRow() {
		return this.numOfRow;
	}
	/**
	 * @return {int} 列の長さ
	 */
	public int getNumOfColumn() {
		return this.numOfColumn;
	}

	/**
	 * 指定した行列（ベクトル）の要素を返す
	 * @param rowIndex		{int}		行数　（ベクトルの場合、0を入力）
	 * @param columnIndex	{int}		列数
	 * @return				{double} 	指定された行列(ベクトル）の要素
	 */
	public double showsComponentOf(int rowIndex, int columnIndex){
        if(rowIndex>this.m.length || columnIndex>this.m.length || rowIndex<0 || columnIndex<0){
            System.out.println("[Matrix.showsComponentOf] 指定する要素は存在しません.");
    	    System.exit(0);
        }
		return this.m[rowIndex][columnIndex];
    }

	/**
	 * 行列/ベクトルを表示する
	 * @param type {String} "vector" : ベクトル　"matrix" : 行列
	 */
	public void display(String type){
		switch(type){
			case "vector":
				System.out.print("[");
				for(int i=0;i<this.m[0].length;i++){
					if(i == this.m[0].length-1) System.out.print(this.m[0][i]);
					else                     System.out.print(this.m[0][i] + " ");
				}
				System.out.print("]\n");
				break;
			case "matrix":
				for(int i=0;i<this.m.length;i++){
					System.out.print("[");
					for(int j=0;j<this.m[0].length;j++){
						if(j == this.m[0].length-1) System.out.print(this.m[i][j]);
						else                        System.out.print(this.m[i][j] + " ");
					}
					System.out.print("]\n");
				}
				break;
			default:
				System.out.println("[Matrix.display] 正しい引数が与えられていません");
				System.exit(0);
		}
	}

	/**
	 * ベクトル(matrix class this)とvecBの内積 （Matrix・vecB）の結果を返す
	 * @param vecB		{Matrix Class} 
	 * @return result	{double}
	 */
	public double getInnerProduct(Matrix vecB){ 
		double result = 0.0;
		// Aが列ベクトルである場合、エラーメッセージを表示させて System.exit(0)
		if(this.numOfColumn==1){
			System.out.println("[Matrix.getInnerProduct] Aが列ベクトルのため、内積を求められません");
			System.exit(0);
		}
		// A, B 双方とも行ベクトル、かつ、要素数が等しければ内積を計算
		if((this.numOfRow == 1 && vecB.numOfRow == 1) || (this.numOfColumn == vecB.numOfColumn)){
			for(int i=0;i<this.m[0].length;i++){
				result += this.m[0][i] * vecB.m[0][i];
			}
			return result;
		}
		// Aが行ベクトル、Bが列ベクトルで、要素数が等しければ内積を計算
		if((this.numOfRow == 1 && vecB.numOfColumn ==1) || (this.numOfColumn == vecB.numOfRow)){
			for(int i=0;i<this.m[0].length;i++){
				result += this.m[i][0] * vecB.m[0][i];
			}
			return result;
		}
		// 内積計算が可能な条件を満たさない場合は、エラーメッセージを表示させてSystem.out.exit(0)
		System.out.println("this.Row = "+ this.numOfRow);
		System.out.println("this.Column = "+ this.numOfColumn);		
		System.out.println("vecB.Raw = "+ vecB.numOfRow);		
		System.out.println("vecB.Column = "+ vecB.numOfColumn);		
		System.out.println("[Matrix.getInnerProduct] 内積結果が可能な条件を満たしません");
		System.exit(0);
		return 0.0;
	}

	/**
	 * 行列の積算が可能か判定する(X × Y)
	 * @param x	{Matrix} 掛けられる行列
	 * @param y	{Matrix} 掛ける行列
	 * @return `{boolean}
	 */
	public static boolean multipliable(Matrix x ,Matrix y){
		if(x.numOfColumn!=y.numOfRow)return false;
		return true;
	}

	/**
	 * 行列同士・行列とベクトルの積を計算する（[matrix] this * [matrix] target
	 * @param target {Matrix} 掛けられる行列orベクトル
	 * @return result {Matrix} 積（行列）
	 */
	public Matrix multiplyMatrix(Matrix target){
		// 掛けられる行列の列数と掛ける行列の行数が等しいなら
		Matrix result = new Matrix();
		if(multipliable(this,target)){
			// 積の計算処理を実装せよ
			result.m = new double [this.numOfRow][target.numOfColumn];
			for(int k=0;k<this.numOfRow;k++){
				for(int n=0;n<target.numOfColumn;n++){
					double resultElement = 0.0;
					for(int i=0;i<target.numOfRow;i++){
						resultElement+=this.m[k][i] * target.m[i][n];
					}
					result.m[k][n] = resultElement;
				}
			}
			result.numOfRow = result.m.length;
			result.numOfColumn = result.m[0].length;
        }else{
            System.out.println("[Matrix.multiplyMatrix] 要素数が計算できる組み合わせとなっていません");
            System.exit(0);
        }
		// 積の結果をMatrix型で返す
		return result;
	}
	
	/**
	 * thisの転置行列を返すメソッド
	 * @return result {Matrix} 転置行列
	 */
	public Matrix transpose(){
		Matrix result = new Matrix(this.numOfColumn,this.numOfRow);
		for(int i=0;i<this.numOfRow;i++){
			for(int j=0;j<this.numOfColumn;j++){
				result.m[j][i] = this.m[i][j];
			}
		}
		return result;
	}

	/**
	 * deg -> rad
	 * @param theta {double} 角度
	 * @return {double}      ラジアン
	 */
	public static double convertIntoRadian(double theta){
		return theta * (Math.PI/180);
	}

	/**
	 * （行数2の列ベクトルのみ対応）
	 * @param deg
	 * @return
	 */
	public Matrix rotate(double deg){
		if(this.numOfRow == 2 && this.numOfColumn == 1){
			double rad = convertIntoRadian(deg);
			double[][] rotation = { {Math.cos(rad) ,-1 * Math.sin(rad)},
									{Math.sin(rad) ,     Math.cos(rad)} };
			Matrix rotationMatrix = new Matrix(rotation);
			Matrix result = rotationMatrix.multiplyMatrix(this);
			return result;
		}else if(this.numOfRow == 1 && this.numOfColumn == 2){
			System.out.println("[Matrix.rotate] 列数2の行ベクトル >> 行ベクトルに変換して計算します。");
			Matrix transpose = this.transpose();
			double rad = convertIntoRadian(deg);
			double[][] rotation = { {Math.cos(rad) ,-1 * Math.sin(rad)},
									{Math.sin(rad) ,     Math.cos(rad)} };
			Matrix rotationMatrix = new Matrix(rotation);
			Matrix result = rotationMatrix.multiplyMatrix(transpose);
			return result;
		}else{
			System.out.println("[Matrix.rotate] 行数2の列ベクトルではありません");
            System.exit(0);
		}
		return this;
	}
}