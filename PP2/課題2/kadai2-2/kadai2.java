/* javaの基本的なコーディングを体験するクラス SourceExample */
import pr2calc.SourceExample;   // 現時点では「おまじない」
import java.io.*;
public class kadai2{  
    public static void main(String[] args)throws Exception{
	SourceExample    ex;    // SourceExample クラスのオブジェクト ex を宣言
	if(args.length!=1){
		System.out.println("引数が不適当です。データ入力用のファイル名を再度指定して下さい。");
		String fn = null;
		// キーボードからファイル名を入力して 変数 fn に代入する
		BufferedReader fname;
		fname = new BufferedReader(new InputStreamReader(System.in));
		fn = fname.readLine();
		ex = new SourceExample(fn);
	}else{
		ex = new SourceExample(args[0]);
	}
	System.out.println("オブジェクトのaフィールドの値は"+ex.getA()+"です");
	System.out.println("");
	ex.showAllContentsOfB();
	System.out.println("");
	System.out.println(ex.getStr());
    }
}