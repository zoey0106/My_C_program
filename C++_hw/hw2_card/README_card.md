姓名:江若綾
學號:409335047
email:zoezoezoe0106@gmail.com

$$$$$~~~~$$$$$$
使用 ./card_hw2 input.txt 來執行
$$$$$~~~~$$$$$$

完成項目:
I.  
1.bool isvalid (const string& cardNumber)
2.int sumofDoubleEvenPlace (const string& cardNumber)
3.int getDigit (int number)
4.int sumOfOddPlace (const string& cardNumber)
5.bool startsWith (const string& cardNumber, const string& substr)
皆運作成功，名字一模一樣
#分別標了數字#
II.當輸入特定字串時 (例："004") 生成指定要求(副函式名稱:void generator(const string& buffer))
1.可生成要求的合法信用卡號碼 
2.使用timer計算 印出時間

Bonus :
1.使用非講義的方法，生成合法的信用卡號碼
方法: 我讓前兩個或一個數字(根據要生成的卡號)固定，除了最後一個數字，其他都亂數產生數字，計算valid需要的最後一個數字，再
放入此卡號的末尾，就生成了一個valid的特定品牌卡號了
2.判斷是否在一開始就輸入過多或過少指令，並印出提示
3.在生成時若是寫入了不知名的指令(ex. 000,123,002)，並印出提示
