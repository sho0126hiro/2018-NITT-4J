package pr2calc;

public class SimultaneousEquation extends Matrix{
	protected double[] answers;
	protected int[] deal; // ���̏��Ԃ��i�[����

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
	 * �w�肵���s�̑Ίp������1�ɂ���
	 * @param row {int} �s��
	 */
	public void normalize(int row){
		row-=1;
		double divisor = this.m[row][row];
		for(int j=0;j<this.numOfColumn;j++){
			this.m[row][j] /= divisor;
		}
	}
	
	/**
	 * �s����̎w�肵���s�x�N�g���i1�s�̍s��j��萔�{����
	 * @param row {int} �s
	 * @param multiplier {double} �����鐔
	 */
	public void constantFactor(int row,double multiplier){
		row-=1;
		for(int i=0;i<this.m[row].length;i++){
			this.m[row][i] *= multiplier;
		}
	}
	/**
	 * �s��(this)���̍s�x�N�g��(row1)����A�s�x�N�g��(row2)������
	 * @param row1 {int} �����s
	 * @param row2 {int} �������s
	 */
	public void vectorSubtraction(int row1,int row2){
		row1-=1;
		row2-=1;
		for(int i=0;i<this.numOfColumn;i++){
			this.m[row2][i] -= this.m[row1][i];
		}
	}

	/**
	 * �Ίp������1�ƂȂ����s�S�̂ɓK�؂Ȓl���悶�A���̑��̓���̍s�̑Ή������̗v�f��0�ƂȂ�悤�ɍ�������
	 * @param row1 {int} �����s
	 * @param row2 {int} �������s
	 */
	public void subtractRowFrom(int row1,int row2){
		row1-=1;
		row2-=1;
		// System.out.println(this.m[row1][row1]);
		if(this.m[row1][row1]!=1){
			System.out.println("[SimultaneousEquation.subtractRowFrom] �����s�̗v�f��1�ł͂���܂���\n"+
			                    this.m[row1][row1]+"�ł�");
			System.exit(0);			
		}else{
			double multiplier  = this.m[row2][row1];
			this.constantFactor(row1+1, multiplier);
			this.vectorSubtraction(row1+1,row2+1);
			this.constantFactor(row1+1, 1/multiplier);
		}
	}

	/**
	 * �|���o���@���������郁�\�b�h
	 */
	public void solveByGaussJordan(){
		for(int i=0;i<this.numOfColumn-1;i++){
			System.out.println("\n"+(i+1)+"�s"+(i+1)+"��ڂ�1�ƂȂ�悤�Ɋ���A���̍s��"+(i+1)+"��ڂ�0�ƂȂ�悤�Ɉ���");
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
	 *  �w�肳�ꂽ�s�x�N�g����萔�{���A����
	 * @param row1 {int} �����s
	 * @param row2 {int} �������s
	 */
	public void vectorSubandFactor(int row1,int row2){
		row1-=1;
		row2-=1;
		for(int i=0;i<this.numOfColumn;i++){
			this.m[row2][i] -= this.m[row1][i];
		}
	}

	/**
	 * �K�E�X�̏����@���s�����\�b�h
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
	 * �s����̓����2�s�����ւ���
	 * @param row1 {int} �s�ԍ� (1~)
	 * @param row2 {int} �s�ԍ� (1~)
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
	 * �s����̓����2������ւ���
	 * @param column1 {int} ��ԍ� (1~)
	 * @param column2 {int} ��ԍ� (1~)
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
	 * �s�{�b�g���܂܂���̒��Ő�Βl���ő�̗v�f���܂܂��s�ԍ���Ԃ�
	 * @param column {int} ��ԍ� (1~)
	 * @return row {int}  �s�ԍ� (1~)
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
	 * �K�E�X�̏����@ - �s�{�b�g�̕����I��@���s�����\�b�h
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
	 * �s�{�b�g���܂܂��s���Ő�Βl�ő�̗v�f���܂܂��s��ԍ���Ԃ�
	 * @param column {int} �s�{�b�g���܂܂���ԍ�
	 * @return element {int[]} [0]:�s�ԍ� [1]:��ԍ� data[0]�sdata[1]��
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
	 * ���݂̃s�{�b�g�ƃs�{�b�g�ɂ������v�f�����ւ���悤��
	 * �s�Ɨ�i[r1][c2]��[r2][c2]�j�����ւ��郁�\�b�h
	 * @param r1,c1 {int} �����O�̍s�A��ԍ� (1~)
	 * @param r1,c2 {int} ������̍s�A��ԍ� (1~)
	 */
	protected void exchangeRowsAndColumns(int r1,int c1,int r2,int c2){
		this.exchangeRows(r1,r2);
		this.exchangeColumns(c1,c2);
	}

	/**
	 * �K�E�X�̏����@ - �s�{�b�g�̊��S�I��@���s�����\�b�h
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