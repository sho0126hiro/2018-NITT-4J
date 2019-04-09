package pr2calc;
// import pr2calc.Matrix;
public class SimultaneousEquation extends Matrix{
	protected double[] answers;

	// constractor
	public SimultaneousEquation(double[][] input){
		super(input);
	}

	/**
	 * �w�肵���s�̑Ίp������1�ɂ���
	 * @param row {int} �s���i0�ȏ�j
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
}