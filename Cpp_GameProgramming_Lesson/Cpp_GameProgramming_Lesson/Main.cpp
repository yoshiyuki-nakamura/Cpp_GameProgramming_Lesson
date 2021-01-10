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
        _is_grounded(true),
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

            // 接地フラグを立てる
            _is_grounded = true;
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
        // 接地していなければ終了
        if (!_is_grounded)
        {
            return;
        }

        // 上向きの速度を加えることでジャンプを表現する
        _velocity.y = -10;

        // 接地フラグを折る
        _is_grounded = false;
    }

    /// <summary>
    /// 当たり判定を取得
    /// </summary>
    /// <returns></returns>
    RectF GetHitArea()
    {
        return RectF(_position, _texture.size());
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
    /// 接地中か
    /// </summary>
    bool _is_grounded;

    /// <summary>
    /// テクスチャ
    /// </summary>
    Texture _texture;
};

/// <summary>
/// 敵
/// </summary>
class Enemy
{
public:
    Enemy(Vec2 position):
        _position(position),
        _initial_position(position),
        _velocity(0, 0),
        _texture(U"assets/textures/enemy.png")
    {
        Reset();
    }

public:
    /// <summary>
    /// 更新
    /// </summary>
    void Update() 
    {
        // 座標に速度を足すことで移動を表現する
        _position += _velocity;

        // 画面左端に達したら
        if (_position.x < -100)
        {
            // リセット
            Reset();
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
    /// 当たり判定を取得
    /// </summary>
    /// <returns></returns>
    RectF GetHitArea()
    {
        return RectF(_position, _texture.size());
    }

private:
    /// <summary>
    /// リセット
    /// </summary>
    void Reset()
    {
        // 初期位置に補正
        _position = _initial_position;

        // 速度をランダムで決定
        _velocity.x = Random(-10.0f, -5.0f);
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
/// シーンの種類
/// </summary>
enum SceneType
{
    Title,
    Game,
    Result,
};

/// <summary>
/// 矩形vs矩形の衝突判定
/// </summary>
/// <param name="rect1"></param>
/// <param name="rect2"></param>
/// <returns></returns>
bool IsHit(RectF rect1, RectF rect2)
{
    // Siv3Dは図形同士の衝突判定がすでに備わっている
    //return rect1.intersects(rect2);

    return rect1.x < rect2.x + rect2.w
        && rect2.x < rect1.x + rect1.w
        && rect1.y < rect2.y + rect2.h
        && rect2.y < rect1.y + rect1.h;
}

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

    // 敵を生成
    Enemy enemy = Enemy(Vec2(900, 400));

    // ゲームルール説明用フォント
    Font game_rule_display_font = Font(20);

    // プレススタート説明用フォント
    Font press_start_guide_font = Font(30);

    // 操作説明用フォント
    Font control_guide_font = Font(30);

    // ゲームオーバー表示用フォント
    Font gameover_font = Font(50);

    // タイトルへ戻る説明用フォント
    Font to_title_guide_font = Font(30);

    // シーンを設定
    SceneType scene = SceneType::Game;

    // ゲームループです。
    // このwhileの中にゲームプログラムを書きます。
    while (System::Update())
    {
        // シーン別更新
        switch (scene)
        {
        case SceneType::Title:
            // スペースを押下したら
            if (KeySpace.down())
            {
                // ゲームシーンへ遷移
                scene = SceneType::Game;
            }
            break;
        case SceneType::Game:
            // スペースを押下したら
            if (KeySpace.down())
            {
                // プレイヤーをジャンプさせる
                player.Jump();
            }

            // プレイヤー更新
            player.Update();

            // 敵更新
            enemy.Update();

            // 衝突したら
            if (IsHit(player.GetHitArea(), enemy.GetHitArea()))
            {
                // リザルトシーンへ
                scene = SceneType::Result;
            }

            break;
        case SceneType::Result:
            // スペースを押下したら
            if (KeySpace.down())
            {
                // タイトルシーンへ遷移
                scene = SceneType::Title;
            }
            break;
        }

        // 背景画像描画
        background.draw(0, 0);

        // プレイヤー描画
        player.Draw();

        // 敵描画
        enemy.Draw();

        // シーン別描画
        switch (scene)
        {
        case SceneType::Title:
            // ゲームルール描画
            game_rule_display_font(U"赤い四角形のあなたは、青い四角形をジャンプでよけ続けるゲーム（仮）").drawAt(Scene::Center().moveBy(0, -100));
            // プレススタート描画
            press_start_guide_font(U"スペースキーでスタート").drawAt(Scene::Center());
            break;
        case SceneType::Game:
            // 操作説明描画
            control_guide_font(U"スペースキーでジャンプ").drawAt(Scene::Center());
            break;
        case SceneType::Result:
            // ゲームオーバー描画
            gameover_font(U"ゲームオーバー").drawAt(Scene::Center().moveBy(0, -100));
            // タイトルへ戻る描画
            to_title_guide_font(U"スペースキーでタイトルへ戻る").drawAt(Scene::Center());
            break;
        }
    }
}
