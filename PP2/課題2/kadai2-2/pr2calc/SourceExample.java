/* javaの基本的なコーディングを体験するクラス SourceExample */
package pr2calc;   // 現時点では「おまじない」
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

	// フィールド変数 a, b, str　の値を内部で初期化（設定）するコンストラクタ
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
	
    // ファイルからのデータ入力で変数を初期化するコンストラクタを作成
    public SourceExample(String fileName){
       try{
		// ファイル"fileName"から、データを読み込むメソッドを呼び出す
		loadData(fileName);
       }catch(IOException e){  System.out.println("ファイルからの入力に失敗しました。");}
    }

    private boolean loadData(String fileName) throws IOException{
		int h,i;
		int row, column;
		BufferedReader fin = new BufferedReader(new FileReader(fileName));
		String inputData;
		String[] inputValue;
		// inputData に、ファイルから文字列を一行分読み込む
		// 得られた文字列データを、スペース(= "\\s") で区切り、配列 inputValue へ格納
		inputData = fin.readLine();
		inputValue = inputData.split("\\s");
		if(inputValue.length != 1){
			fin.close();
			return false;
		}else{
			// フィールド（インスタンス）変数 a に、inputValueの最初（0番目）の要素を代入
			this.a = Integer.parseInt(inputValue[0]);
			// もう一行読み込み、スペース区切りで inputValue へデータ(次に読み込む行列の行数＆列数）を格納
			inputData = fin.readLine();
			inputValue = inputData.split("\\s");
			if(inputValue.length != 2){
				// 行数＆列数の双方が格納されていなければ
				fin.close();
				return false;
			}
			else{
				// 変数 row に行数のデータ、column に列数のデータを代入
				row    = Integer.parseInt(inputValue[0]);
				column = Integer.parseInt(inputValue[1]);
				this.b = new int[row][column];
				// 配列 b のh行i列目の要素に、読みんだファイルのh行目、(左から）i番目のデータを格納
				for(h=0;h<row;h++){
					inputData = fin.readLine();
					inputValue = inputData.split("\\s");
					for(i=0;i<column;i++){
						this.b[h][i] = Integer.parseInt(inputValue[i]);
					}
				}
				// フィールド（インスタンス）変数 str に、格納した文字列を代入
				this.str = fin.readLine();
			}
		}
		fin.close(); 
		return true;
	}

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
}