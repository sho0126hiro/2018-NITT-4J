/* java�̊�{�I�ȃR�[�f�B���O��̌�����N���X SourceExample */
import pr2calc.SourceExample;   // �����_�ł́u���܂��Ȃ��v
import java.io.*;
public class kadai2{  
    public static void main(String[] args)throws Exception{
	SourceExample    ex;    // SourceExample �N���X�̃I�u�W�F�N�g ex ��錾
	if(args.length!=1){
		System.out.println("�������s�K���ł��B�f�[�^���͗p�̃t�@�C�������ēx�w�肵�ĉ������B");
		String fn = null;
		// �L�[�{�[�h����t�@�C��������͂��� �ϐ� fn �ɑ������
		BufferedReader fname;
		fname = new BufferedReader(new InputStreamReader(System.in));
		fn = fname.readLine();
		ex = new SourceExample(fn);
	}else{
		ex = new SourceExample(args[0]);
	}
	System.out.println("�I�u�W�F�N�g��a�t�B�[���h�̒l��"+ex.getA()+"�ł�");
	System.out.println("");
	ex.showAllContentsOfB();
	System.out.println("");
	System.out.println(ex.getStr());
    }
}