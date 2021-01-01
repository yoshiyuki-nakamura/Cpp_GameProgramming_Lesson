// Siv3Dを使うために必要です。
#include <Siv3D.hpp>

/// <summary>
/// Main関数です。
/// ここからプログラムが始まります。
/// </summary>
void Main()
{
    // テキスト描画用
    Font font(60);

    // ゲームループです。
    // このwhileの中にゲームプログラムを書きます。
    while (System::Update())
    {
        // テキスト描画
        font(U"Hello World!").drawAt(Scene::Center());
    }
}
