// Siv3Dを使うために必要です。
#include <Siv3D.hpp>

/// <summary>
/// プレイヤー
/// </summary>
class Player
{
public:
    Player(Vec2 position) :
        _position(position),
        _texture(U"assets/textures/player.png")
    {
    }

public:
    /// <summary>
    /// 描画
    /// </summary>
    void Draw()
    {
        _texture.draw(_position);
    }

private:
    /// <summary>
    /// 座標
    /// </summary>
    Vec2 _position;

    /// <summary>
    /// テクスチャ
    /// </summary>
    Texture _texture;
};

/// <summary>
/// Main関数です。
/// ここからプログラムが始まります。
/// </summary>
void Main()
{
    // 背景画像を準備
    Texture background = Texture(U"assets/textures/background.png");

    // プレイヤーを生成
    Player player = Player(Vec2(100, 400));

    // ゲームループです。
    // このwhileの中にゲームプログラムを書きます。
    while (System::Update())
    {
        // 背景画像描画
        background.draw(0, 0);

        // プレイヤー描画
        player.Draw();
    }
}
