//package pr2calc;
// ↑現時点では「おまじない」。pr2calcフォルダの中に当該ファイルを置いて実行する場合には要記述（コメントアウト "//"
// を外す）。

public class SourceExample{	// 同色の中括弧閉じ（この例の一番最後にある"}"）までが、SourceExampleオブジェクト
				            // の扱うデータと処理を定義する、SourceExampleクラス
    private int a;		// 青字の部分がフィールド変数（メソッドの外にある）。
    private int[][] b;	// クラス内の、main()メソッドを除く全メソッドで
    private String str;	// 利用可能

/* 以下のメソッド（関数）はコンストラクタ。オブジェクトの生成（& 初期化）を行う 
 * 引数の設定は自由。引数が異なれば、複数用意しても良い
 */

    public SourceExample(){       // 各変数の初期化を実行（例なので、中身は適当です）
        int h,i;                  // メソッド内で宣言される変数は、メソッド内のみで利用可

        this.a = -1;	// フィールド変数として定義された変数は、クラス内どこでも利用可（this.a ・・・ 
			            // "この(= this)オブジェクト(インスタンス)自身の持つ変数a"）
        this.b = new int[2][2];
 /* java では、配列と文字列はオブジェクトとして用意されているため、新しい配列、文字列を宣言する時には
  *  "new" を使う(上の例では、b を2×2の整数型二次元配列として宣言している）
  */
        for(h=0;h<this.b.length;h++){		// 二次元配列の値を -1 で初期化
            for(i=0;i<this.b[0].length;i++)	// 配列に関しては、"new" を用いずに
                this.b[h][i] = -1;		// 初期化することも可能（詳細はmain
        }					    // メソッド内を参照）
// this.b.length : 配列の第一要素の要素数、this.b[0].length : 配列の第二要素の要素数
        this.str = "";  // 文字列型はオブジェクトとして用意されると記述したが、非常によく
	                    // 用いられる型であるため、左のような記法も認められている
		                // （new String(""); という書き方でも当然OK）
    }

// フィールド変数 a, b, str　の値を内部で初期化（設定）するコンストラクタをもう一つ記述する
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

/* 以降、mainメソッド以外のメソッドは、コンストラクタで生成されたオブジェクト
 * を介して実行される
 */
    public void setA(int value){    //　メソッドを通して、フィールド変数の値を設定する（setterと呼ばれる）
        this.a = value;
    }

    public int getA(){	// メソッドを通して、フィールド変数の値を返す（getterと呼ばれる）
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
        // valueの中身を表示する
        for(int i=0;i<this.b.length;i++){
            for(int j=0;j<this.b[i].length;j++){
                System.out.print(this.b[i][j] + ",");
            }
            System.out.print("\n");
        }
 	System.out.print("\n");
    }

/* このプログラムを実行すると、以下の main メソッドに記述された動作が実行される */
    public static void main(String[] args){
        SourceExample ex;    // SourceExample クラスのオブジェクト ex を宣言
        int value[][] = {{1,2,3},{4,5,6},{7,8,9}}; // "new"を用いない、二次元配列を初期化する書き方
        // ex = new SourceExample();    // SourceExample クラスのオブジェクト ex を生成
        // ex.setA(10); // ex オブジェクトのフィールド this.a の値を10に変更；
        ex = new SourceExample(3,value,"Hello World.");
        // 上の二行をコメントアウトした上で、aを3、bを配列 value、str を文字列 "Hello World." として
        // 初期化するコンストラクタを用いて ex を生成せよ
        System.out.println("オブジェクトのaフィールドの値は"+ex.getA()+"です\n");
        ex.showAllContentsOfB();
        System.out.println(ex.getStr());
    }
}	// ここまでがクラス SourceExample