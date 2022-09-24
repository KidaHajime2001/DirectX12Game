#pragma once

//  シングルトンの解放を行うクラス
class SingletonFinalizer {
public:
    /// <summary>
    /// このクラスの関数を利用するための宣言
    /// void = 関数の戻り値
    /// (*)  = 関数名（この場合は解放処理名
    /// ()   = 引数 
    /// </summary>
    using FinalizerFunc = void(*)();
    
    /// <summary>
    /// シングルトンクラスの終了処理時に解放されるインスタンスの登録
    /// </summary>
    /// <param name="_func">
    /// 関数ポインタ
    /// 解放の処理関数を入れる
    /// </param>
    static void AddFinalizer(FinalizerFunc _func);
    //  シングルトンクラスの終了処理
    static void Finalize();
};