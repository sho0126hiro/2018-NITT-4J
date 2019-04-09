/* javaの基本的なコーディングを体験するクラス SourceExample */
import pr2calc.SourceExample;   // 現時点では「おまじない」
import java.io.*;
public class kadai2{  
    public static void main(String[] args) {
	SourceExample    ex;    // SourceExample クラスのオブジェクト ex を宣言
    // 入力データの含まれているファイル名をsample.datとした場合
	ex = new SourceExample("kadai-02.dat"); //pathを指定して実装しました。
	System.out.println("オブジェクトのaフィールドの値は"+ex.getA()+"です");
	System.out.println("");
	ex.showAllContentsOfB();
	System.out.println("");
	System.out.println(ex.getStr());
    }
}