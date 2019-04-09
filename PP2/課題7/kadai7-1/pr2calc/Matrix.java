package pr2calc;


public class Matrix {
	// �K�v�ȃt�B�[���h�i�C���X�^���X�j�ϐ��̐錾
	public double[][] m;
	public int numOfRow; // �s��
	public int numOfColumn; // ��
	
	/**
	 *  �s��̍s��,�񐔂��i�[����C���X�^���X�ϐ��̒l��0�ɏ�����
	 */ 
	public Matrix() {
		this.numOfColumn = 0;
		this.numOfRow    = 0;
	}
	
	/**
	 * �s���E�񐔂��w�肵�ď�����
	 * @param Row
	 * @param Column
	 */
	public Matrix(int Row,int Column){
		this.numOfRow       = Row;
		this.numOfColumn    = Column;
		this.m = new double[this.numOfRow][this.numOfColumn];
	}
	
	/**
	 * �񎟌��z��̓��e�ōs��̏�����
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
	 * �ꎟ���z��̓��e�ōs���������
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
	 * @return {int} �s�̒���
	 */
	public int getNumOfRow() {
		return this.numOfRow;
	}
	/**
	 * @return {int} ��̒���
	 */
	public int getNumOfColumn() {
		return this.numOfColumn;
	}

	/**
	 * �w�肵���s��i�x�N�g���j�̗v�f��Ԃ�
	 * @param rowIndex		{int}		�s���@�i�x�N�g���̏ꍇ�A0����́j
	 * @param columnIndex	{int}		��
	 * @return				{double} 	�w�肳�ꂽ�s��(�x�N�g���j�̗v�f
	 */
	public double showsComponentOf(int rowIndex, int columnIndex){
        if(rowIndex>this.m.length || columnIndex>this.m.length || rowIndex<0 || columnIndex<0){
            System.out.println("[Matrix.showsComponentOf] �w�肷��v�f�͑��݂��܂���.");
    	    System.exit(0);
        }
		return this.m[rowIndex][columnIndex];
    }

	/**
	 * �s��/�x�N�g����\������
	 * @param type {String} "vector" : �x�N�g���@"matrix" : �s��
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
				System.out.println("[Matrix.display] �������������^�����Ă��܂���");
				System.exit(0);
		}
	}

	/**
	 * �x�N�g��(matrix class this)��vecB�̓��� �iMatrix�EvecB�j�̌��ʂ�Ԃ�
	 * @param vecB		{Matrix Class} 
	 * @return result	{double}
	 */
	public double getInnerProduct(Matrix vecB){ 
		double result = 0.0;
		// A����x�N�g���ł���ꍇ�A�G���[���b�Z�[�W��\�������� System.exit(0)
		if(this.numOfColumn==1){
			System.out.println("[Matrix.getInnerProduct] A����x�N�g���̂��߁A���ς����߂��܂���");
			System.exit(0);
		}
		// A, B �o���Ƃ��s�x�N�g���A���A�v�f������������Γ��ς��v�Z
		if((this.numOfRow == 1 && vecB.numOfRow == 1) || (this.numOfColumn == vecB.numOfColumn)){
			for(int i=0;i<this.m[0].length;i++){
				result += this.m[0][i] * vecB.m[0][i];
			}
			return result;
		}
		// A���s�x�N�g���AB����x�N�g���ŁA�v�f������������Γ��ς��v�Z
		if((this.numOfRow == 1 && vecB.numOfColumn ==1) || (this.numOfColumn == vecB.numOfRow)){
			for(int i=0;i<this.m[0].length;i++){
				result += this.m[i][0] * vecB.m[0][i];
			}
			return result;
		}
		// ���όv�Z���\�ȏ����𖞂����Ȃ��ꍇ�́A�G���[���b�Z�[�W��\��������System.out.exit(0)
		System.out.println("this.Row = "+ this.numOfRow);
		System.out.println("this.Column = "+ this.numOfColumn);		
		System.out.println("vecB.Raw = "+ vecB.numOfRow);		
		System.out.println("vecB.Column = "+ vecB.numOfColumn);		
		System.out.println("[Matrix.getInnerProduct] ���ό��ʂ��\�ȏ����𖞂����܂���");
		System.exit(0);
		return 0.0;
	}

	/**
	 * �s��̐ώZ���\�����肷��(X �~ Y)
	 * @param x	{Matrix} �|������s��
	 * @param y	{Matrix} �|����s��
	 * @return `{boolean}
	 */
	public static boolean multipliable(Matrix x ,Matrix y){
		if(x.numOfColumn!=y.numOfRow)return false;
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
	 * @param theta {double} �p�x
	 * @return {double}      ���W�A��
	 */
	public static double convertIntoRadian(double theta){
		return theta * (Math.PI/180);
	}

	/**
	 * �i�s��2�̗�x�N�g���̂ݑΉ��j
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
			System.out.println("[Matrix.rotate] ��2�̍s�x�N�g�� >> �s�x�N�g���ɕϊ����Čv�Z���܂��B");
			Matrix transpose = this.transpose();
			double rad = convertIntoRadian(deg);
			double[][] rotation = { {Math.cos(rad) ,-1 * Math.sin(rad)},
									{Math.sin(rad) ,     Math.cos(rad)} };
			Matrix rotationMatrix = new Matrix(rotation);
			Matrix result = rotationMatrix.multiplyMatrix(transpose);
			return result;
		}else{
			System.out.println("[Matrix.rotate] �s��2�̗�x�N�g���ł͂���܂���");
            System.exit(0);
		}
		return this;
	}
}