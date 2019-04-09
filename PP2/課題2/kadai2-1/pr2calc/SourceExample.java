/* java�̊�{�I�ȃR�[�f�B���O��̌�����N���X SourceExample */
package pr2calc;   // �����_�ł́u���܂��Ȃ��v
import java.io.*;
public class SourceExample{  

	private int a;
	private int[][] b;
	private String str;

   	public SourceExample(){
        int h,i;
        this.a = -1; 
        this.b = new int[2][2];
        for(h=0;h<this.b.length;h++){
            for(i=0;i<this.b[0].length;i++)
                this.b[h][i] = -1;
        }
        this.str = "";
    }

	// �t�B�[���h�ϐ� a, b, str�@�̒l������ŏ������i�ݒ�j����R���X�g���N�^
    public SourceExample(int x,int[][] y , String z){
        this.a = x;
        this.b = y;
        for(int i=0;i<this.b.length;i++){
            for(int j=0;j<this.b[0].length;j++){
                this.b[i][j] = b[i][j];
            }
        }
        this.str = z;
	}
	
    // �t�@�C������̃f�[�^���͂ŕϐ�������������R���X�g���N�^���쐬
    public SourceExample(String fileName){
       try{
		// �t�@�C��"fileName"����A�f�[�^��ǂݍ��ރ��\�b�h���Ăяo��
		loadData(fileName);
       }catch(IOException e){  System.out.println("�t�@�C������̓��͂Ɏ��s���܂����B");}
    }

    private boolean loadData(String fileName) throws IOException{
		int h,i;
		int row, column;
		BufferedReader fin = new BufferedReader(new FileReader(fileName));
		String inputData;
		String[] inputValue;
		// inputData �ɁA�t�@�C�����當�������s���ǂݍ���
		// ����ꂽ������f�[�^���A�X�y�[�X(= "\\s") �ŋ�؂�A�z�� inputValue �֊i�[
		inputData = fin.readLine();
		inputValue = inputData.split("\\s");
		if(inputValue.length != 1){
			fin.close();
			return false;
		}else{
			// �t�B�[���h�i�C���X�^���X�j�ϐ� a �ɁAinputValue�̍ŏ��i0�Ԗځj�̗v�f����
			this.a = Integer.parseInt(inputValue[0]);
			// ������s�ǂݍ��݁A�X�y�[�X��؂�� inputValue �փf�[�^(���ɓǂݍ��ލs��̍s�����񐔁j���i�[
			inputData = fin.readLine();
			inputValue = inputData.split("\\s");
			if(inputValue.length != 2){
				// �s�����񐔂̑o�����i�[����Ă��Ȃ����
				fin.close();
				return false;
			}
			else{
				// �ϐ� row �ɍs���̃f�[�^�Acolumn �ɗ񐔂̃f�[�^����
				row    = Integer.parseInt(inputValue[0]);
				column = Integer.parseInt(inputValue[1]);
				this.b = new int[row][column];
				// �z�� b ��h�si��ڂ̗v�f�ɁA�ǂ݂񂾃t�@�C����h�s�ځA(������ji�Ԗڂ̃f�[�^���i�[
				for(h=0;h<row;h++){
					inputData = fin.readLine();
					inputValue = inputData.split("\\s");
					for(i=0;i<column;i++){
						this.b[h][i] = Integer.parseInt(inputValue[i]);
					}
				}
				// �t�B�[���h�i�C���X�^���X�j�ϐ� str �ɁA�i�[�������������
				this.str = fin.readLine();
			}
		}
		fin.close(); 
		return true;
	}

	public void setA(int value){    //�@���\�b�h��ʂ��āA�t�B�[���h�ϐ��̒l��ݒ肷��isetter�ƌĂ΂��j
        this.a = value;
    }

    public int getA(){	// ���\�b�h��ʂ��āA�t�B�[���h�ϐ��̒l��Ԃ��igetter�ƌĂ΂��j
        return this.a;
    }

    public void setB(int[][] value){
        this.b = value;
    }

    public int[][] getB(){
        return this.b;
    }

    public void setStr(String value){
        this.str = value;
    }

    public String getStr(){
        return this.str;
    }

    public void showAllContentsOfB(){
        // value�̒��g��\������
        for(int i=0;i<this.b.length;i++){
            for(int j=0;j<this.b[i].length;j++){
                System.out.print(this.b[i][j] + ",");
            }
            System.out.print("\n");
        }
 	System.out.print("\n");
    }
}