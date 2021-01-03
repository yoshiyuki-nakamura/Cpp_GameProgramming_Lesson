// Siv3Dを使うために必要です。
#include <Siv3D.hpp>

/// <summary>
/// Main関数です。
/// ここからプログラムが始まります。
/// </summary>
void Main()
{
    // 背景画像を準備
    Texture background = Texture(U"assets/textures/background.png");

    // ゲームループです。
    // このwhileの中にゲームプログラムを書きます。
    while (System::Update())
    {
        // 背景画像描画
        background.draw(0, 0);
    }
}
