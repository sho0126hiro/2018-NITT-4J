//package pr2calc;
// �������_�ł́u���܂��Ȃ��v�Bpr2calc�t�H���_�̒��ɓ��Y�t�@�C����u���Ď��s����ꍇ�ɂ͗v�L�q�i�R�����g�A�E�g "//"
// ���O���j�B

public class SourceExample{	// ���F�̒����ʕ��i���̗�̈�ԍŌ�ɂ���"}"�j�܂ł��ASourceExample�I�u�W�F�N�g
				            // �̈����f�[�^�Ə������`����ASourceExample�N���X
    private int a;		// ���̕������t�B�[���h�ϐ��i���\�b�h�̊O�ɂ���j�B
    private int[][] b;	// �N���X���́Amain()���\�b�h�������S���\�b�h��
    private String str;	// ���p�\

/* �ȉ��̃��\�b�h�i�֐��j�̓R���X�g���N�^�B�I�u�W�F�N�g�̐����i& �������j���s�� 
 * �����̐ݒ�͎��R�B�������قȂ�΁A�����p�ӂ��Ă��ǂ�
 */

    public SourceExample(){       // �e�ϐ��̏����������s�i��Ȃ̂ŁA���g�͓K���ł��j
        int h,i;                  // ���\�b�h���Ő錾�����ϐ��́A���\�b�h���݂̂ŗ��p��

        this.a = -1;	// �t�B�[���h�ϐ��Ƃ��Ē�`���ꂽ�ϐ��́A�N���X���ǂ��ł����p�ithis.a �E�E�E 
			            // "����(= this)�I�u�W�F�N�g(�C���X�^���X)���g�̎��ϐ�a"�j
        this.b = new int[2][2];
 /* java �ł́A�z��ƕ�����̓I�u�W�F�N�g�Ƃ��ėp�ӂ���Ă��邽�߁A�V�����z��A�������錾���鎞�ɂ�
  *  "new" ���g��(��̗�ł́Ab ��2�~2�̐����^�񎟌��z��Ƃ��Đ錾���Ă���j
  */
        for(h=0;h<this.b.length;h++){		// �񎟌��z��̒l�� -1 �ŏ�����
            for(i=0;i<this.b[0].length;i++)	// �z��Ɋւ��ẮA"new" ��p������
                this.b[h][i] = -1;		// ���������邱�Ƃ��\�i�ڍׂ�main
        }					    // ���\�b�h�����Q�Ɓj
// this.b.length : �z��̑��v�f�̗v�f���Athis.b[0].length : �z��̑��v�f�̗v�f��
        this.str = "";  // ������^�̓I�u�W�F�N�g�Ƃ��ėp�ӂ����ƋL�q�������A���ɂ悭
	                    // �p������^�ł��邽�߁A���̂悤�ȋL�@���F�߂��Ă���
		                // �inew String(""); �Ƃ����������ł����ROK�j
    }

// �t�B�[���h�ϐ� a, b, str�@�̒l������ŏ������i�ݒ�j����R���X�g���N�^��������L�q����
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

/* �ȍ~�Amain���\�b�h�ȊO�̃��\�b�h�́A�R���X�g���N�^�Ő������ꂽ�I�u�W�F�N�g
 * ����Ď��s�����
 */
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

/* ���̃v���O���������s����ƁA�ȉ��� main ���\�b�h�ɋL�q���ꂽ���삪���s����� */
    public static void main(String[] args){
        SourceExample ex;    // SourceExample �N���X�̃I�u�W�F�N�g ex ��錾
        int value[][] = {{1,2,3},{4,5,6},{7,8,9}}; // "new"��p���Ȃ��A�񎟌��z������������鏑����
        // ex = new SourceExample();    // SourceExample �N���X�̃I�u�W�F�N�g ex �𐶐�
        // ex.setA(10); // ex �I�u�W�F�N�g�̃t�B�[���h this.a �̒l��10�ɕύX�G
        ex = new SourceExample(3,value,"Hello World.");
        // ��̓�s���R�����g�A�E�g������ŁAa��3�Ab��z�� value�Astr �𕶎��� "Hello World." �Ƃ���
        // ����������R���X�g���N�^��p���� ex �𐶐�����
        System.out.println("�I�u�W�F�N�g��a�t�B�[���h�̒l��"+ex.getA()+"�ł�\n");
        ex.showAllContentsOfB();
        System.out.println(ex.getStr());
    }
}	// �����܂ł��N���X SourceExample