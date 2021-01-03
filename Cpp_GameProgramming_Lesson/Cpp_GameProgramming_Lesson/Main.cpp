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
        _initial_position(position),
        _velocity(0, 0),
        _texture(U"assets/textures/player.png")
    {
    }

public:
    /// <summary>
    /// 更新
    /// </summary>
    void Update()
    {
        // 速度に下向きの速度を足すことで重力落下を表現する
        _velocity.y += 0.3f;

        // 座標に速度を足すことで移動を表現する
        _position += _velocity;

        // 地面に達したら
        if (_initial_position.y < _position.y)
        {
            // 速度を0にする
            _velocity.y = 0;

            // 座標を地面の位置に補正
            _position.y = _initial_position.y;
        }
    }

    /// <summary>
    /// 描画
    /// </summary>
    void Draw()
    {
        _texture.draw(_position);
    }

    /// <summary>
    /// ジャンプする
    /// </summary>
    void Jump()
    {
        // 上向きの速度を加えることでジャンプを表現する
        _velocity.y = -10;
    }

private:
    /// <summary>
    /// 座標
    /// </summary>
    Vec2 _position;

    /// <summary>
    /// 初期座標
    /// </summary>
    Vec2 _initial_position;

    /// <summary>
    /// 速度
    /// </summary>
    Vec2 _velocity;

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
        // スペースを押下したら
        if (KeySpace.down())
        {
            // プレイヤーをジャンプさせる
            player.Jump();
        }

        // プレイヤー更新
        player.Update();

        // 背景画像描画
        background.draw(0, 0);

        // プレイヤー描画
        player.Draw();
    }
}
