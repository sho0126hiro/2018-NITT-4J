/* java�̊�{�I�ȃR�[�f�B���O��̌�����N���X SourceExample */
import pr2calc.SourceExample;   // �����_�ł́u���܂��Ȃ��v
import java.io.*;
public class kadai2{  
    public static void main(String[] args) {
	SourceExample    ex;    // SourceExample �N���X�̃I�u�W�F�N�g ex ��錾
    // ���̓f�[�^�̊܂܂�Ă���t�@�C������sample.dat�Ƃ����ꍇ
	ex = new SourceExample("kadai-02.dat"); //path���w�肵�Ď������܂����B
	System.out.println("�I�u�W�F�N�g��a�t�B�[���h�̒l��"+ex.getA()+"�ł�");
	System.out.println("");
	ex.showAllContentsOfB();
	System.out.println("");
	System.out.println(ex.getStr());
    }
}