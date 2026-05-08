#include "dxlib/DxLib.h"
#include <math.h>
#include <vector>
#include <queue>
#include <time.h>

// --- 定数設定 ---
const int SCREEN_W = 640;
const int SCREEN_H = 600;

// バブルのサイズ関連
const int BUBBLE_RADIUS = 16;
const int BUBBLE_DIAMETER = BUBBLE_RADIUS * 2;
// ハニカム構造（六角形配置）にするための行の高さ (直径 × √3 / 2)
const double ROW_HEIGHT = BUBBLE_DIAMETER * 0.866025;

// フィールドの広さ
const int FIELD_ROWS = 15;
const int FIELD_COLS = 8;
const int FIELD_OFS_X = 192; // 描画開始位置X
const int FIELD_OFS_Y = 40;  // 描画開始位置Y

// バブルの移動スピード
const double BUBBLE_SPEED = 8.0;

// 色の定義
enum BubbleColor {
    NONE = 0,
    RED,
    BLUE,
    GREEN,
    YELLOW,
    PURPLE,
    COLOR_MAX
};

// --- グローバル変数 ---
BubbleColor field[FIELD_ROWS][FIELD_COLS];

// 発射するバブルの情報
double px, py; // 現在位置
double vx, vy; // 速度
BubbleColor pColor;
BubbleColor nextColor;
bool isMoving;

// 大砲（発射角度）
double angle = 3.14159265 / 2.0; // 90度（真上）

// 六角形グリッドにおける隣接する6方向のインデックス（偶数行と奇数行で計算が変わる）
int dirEven[6][2] = { {-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 0} };
int dirOdd[6][2] = { {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, 0}, {1, 1} };

// --- 関数群 ---

// 色の列挙型から実際のRGBカラー値を取得
unsigned int GetDxColor(BubbleColor c) {
    switch (c) {
    case RED:    return GetColor(255, 50, 50);
    case BLUE:   return GetColor(50, 100, 255);
    case GREEN:  return GetColor(50, 220, 50);
    case YELLOW: return GetColor(255, 220, 50);
    case PURPLE: return GetColor(200, 50, 200);
    default:     return GetColor(0, 0, 0);
    }
}

// ランダムな色を取得
BubbleColor GetRandomColor() {
    return (BubbleColor)(GetRand(4) + 1);
}

// 行(Row)と列(Col)から、画面上のXY座標を計算する
void GetBubblePos(int row, int col, double& x, double& y) {
    x = FIELD_OFS_X + col * BUBBLE_DIAMETER + BUBBLE_RADIUS;
    // 奇数行は右に半分（半径分）ずらす
    if (row % 2 != 0) x += BUBBLE_RADIUS;
    y = FIELD_OFS_Y + row * ROW_HEIGHT + BUBBLE_RADIUS;
}

// 発射台の初期位置にバブルをセット
void SetNextBubble() {
    px = FIELD_OFS_X + (FIELD_COLS * BUBBLE_DIAMETER) / 2.0;
    py = FIELD_OFS_Y + FIELD_ROWS * ROW_HEIGHT + 30;
    pColor = nextColor;
    nextColor = GetRandomColor();
    isMoving = false;
}

// 宙に浮いている（天井から繋がっていない）バブルを落下（削除）させる
void DropDisconnectedBubbles() {
    bool connected[FIELD_ROWS][FIELD_COLS] = { false };
    std::queue<std::pair<int, int>> q;

    // 1. 天井（0行目）にあるバブルをすべて繋がっているものとしてキューに入れる
    for (int c = 0; c < FIELD_COLS; ++c) {
        if (field[0][c] != NONE) {
            q.push({ 0, c });
            connected[0][c] = true;
        }
    }

    // 2. 幅優先探索(BFS)で繋がっているバブルをすべてマークする
    while (!q.empty()) {
        auto p = q.front();
        int r = p.first;
        int c = p.second;
        q.pop();

        for (int i = 0; i < 6; ++i) {
            int nr = r + (r % 2 == 0 ? dirEven[i][0] : dirOdd[i][0]);
            int nc = c + (r % 2 == 0 ? dirEven[i][1] : dirOdd[i][1]);

            if (nr >= 0 && nr < FIELD_ROWS && nc >= 0 && nc < FIELD_COLS) {
                if (nr % 2 != 0 && nc == FIELD_COLS - 1) continue; // 奇数行の端は存在しない

                if (field[nr][nc] != NONE && !connected[nr][nc]) {
                    connected[nr][nc] = true;
                    q.push({ nr, nc });
                }
            }
        }
    }

    // 3. マークされなかった（繋がっていない）バブルを消す
    for (int r = 0; r < FIELD_ROWS; ++r) {
        for (int c = 0; c < FIELD_COLS; ++c) {
            if (field[r][c] != NONE && !connected[r][c]) {
                field[r][c] = NONE;
            }
        }
    }
}

// 3つ以上繋がっているか判定し、繋がっていたら消す
void CheckMatch(int startRow, int startCol) {
    BubbleColor targetColor = field[startRow][startCol];
    if (targetColor == NONE) return;

    std::vector<std::pair<int, int>> checked;
    std::vector<std::pair<int, int>> matched;
    std::queue<std::pair<int, int>> q;

    q.push({ startRow, startCol });
    checked.push_back({ startRow, startCol });

    while (!q.empty()) {
        auto p = q.front();
        int r = p.first;
        int c = p.second;
        q.pop();
        matched.push_back({ r, c });

        // 周囲6方向を調べる
        for (int i = 0; i < 6; ++i) {
            int nr = r + (r % 2 == 0 ? dirEven[i][0] : dirOdd[i][0]);
            int nc = c + (r % 2 == 0 ? dirEven[i][1] : dirOdd[i][1]);

            if (nr >= 0 && nr < FIELD_ROWS && nc >= 0 && nc < FIELD_COLS) {
                if (nr % 2 != 0 && nc == FIELD_COLS - 1) continue;

                if (field[nr][nc] == targetColor) {
                    bool alreadyChecked = false;
                    for (auto& chk : checked) {
                        if (chk.first == nr && chk.second == nc) { alreadyChecked = true; break; }
                    }
                    if (!alreadyChecked) {
                        checked.push_back({ nr, nc });
                        q.push({ nr, nc });
                    }
                }
            }
        }
    }

    // 3つ以上繋がっていれば消去
    if (matched.size() >= 3) {
        for (auto& p : matched) {
            field[p.first][p.second] = NONE;
        }
        // 消去した後に、宙に浮いたバブルがないか確認して落とす
        DropDisconnectedBubbles();
    }
}

// 衝突したバブルを最も近い空きグリッドにはめ込む
void SnapBubble() {
    int bestRow = -1, bestCol = -1;
    double minDist = 9999999.0;

    for (int r = 0; r < FIELD_ROWS; ++r) {
        for (int c = 0; c < FIELD_COLS; ++c) {
            if (r % 2 != 0 && c == FIELD_COLS - 1) continue;

            if (field[r][c] == NONE) {
                double bx, by;
                GetBubblePos(r, c, bx, by);
                // 現在位置と空きマスの距離の2乗を計算
                double dist = (bx - px) * (bx - px) + (by - py) * (by - py);
                if (dist < minDist) {
                    minDist = dist;
                    bestRow = r;
                    bestCol = c;
                }
            }
        }
    }

    // 最も近い空きマスに配置
    if (bestRow != -1) {
        field[bestRow][bestCol] = pColor;
        CheckMatch(bestRow, bestCol);
    }
}

// ゲーム初期化
void InitGame() {
    SRand((unsigned int)time(NULL));

    // フィールドをクリア
    for (int r = 0; r < FIELD_ROWS; ++r) {
        for (int c = 0; c < FIELD_COLS; ++c) {
            field[r][c] = NONE;
        }
    }

    // 最初の上部3行にランダムにバブルを配置
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < FIELD_COLS; ++c) {
            if (r % 2 != 0 && c == FIELD_COLS - 1) continue;
            field[r][c] = GetRandomColor();
        }
    }

    nextColor = GetRandomColor();
    SetNextBubble();
}


// --- メイン関数 ---
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    SetGraphMode(SCREEN_W, SCREEN_H, 32);
    ChangeWindowMode(TRUE);
    SetMainWindowText("パズルボブル風ゲーム (DXライブラリ)");

    if (DxLib_Init() == -1) return -1;
    SetDrawScreen(DX_SCREEN_BACK);

    InitGame();

    // メインループ
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        ClearDrawScreen();

        // -------------------------
        // 1. 入力・更新処理
        // -------------------------
        if (!isMoving) {
            // 左右キーで角度変更
            if (CheckHitKey(KEY_INPUT_LEFT))  angle += 0.05;
            if (CheckHitKey(KEY_INPUT_RIGHT)) angle -= 0.05;

            // 角度の制限（真横や下には撃てないようにする）
            if (angle < 0.2) angle = 0.2;
            if (angle > 3.141592 - 0.2) angle = 3.141592 - 0.2;

            // スペースキーで発射
            if (CheckHitKey(KEY_INPUT_SPACE)) {
                vx = cos(angle) * BUBBLE_SPEED;
                vy = -sin(angle) * BUBBLE_SPEED;
                isMoving = true;
            }
        }
        else {
            // 移動処理
            px += vx;
            py += vy;

            // 左右の壁で反射
            double fieldLeft = FIELD_OFS_X;
            double fieldRight = FIELD_OFS_X + FIELD_COLS * BUBBLE_DIAMETER;
            if (px - BUBBLE_RADIUS < fieldLeft) {
                px = fieldLeft + BUBBLE_RADIUS;
                vx = -vx;
            }
            if (px + BUBBLE_RADIUS > fieldRight) {
                px = fieldRight - BUBBLE_RADIUS;
                vx = -vx;
            }

            // 衝突判定
            bool collision = false;

            // 天井との衝突
            if (py - BUBBLE_RADIUS <= FIELD_OFS_Y) {
                collision = true;
            }
            else {
                // 他のバブルとの衝突
                for (int r = 0; r < FIELD_ROWS; ++r) {
                    for (int c = 0; c < FIELD_COLS; ++c) {
                        if (field[r][c] != NONE) {
                            double bx, by;
                            GetBubblePos(r, c, bx, by);
                            // 中心間の距離の2乗を計算して当たり判定
                            double distSq = (bx - px) * (bx - px) + (by - py) * (by - py);
                            if (distSq <= (BUBBLE_DIAMETER - 4) * (BUBBLE_DIAMETER - 4)) {
                                collision = true;
                                break;
                            }
                        }
                    }
                    if (collision) break;
                }
            }

            // 衝突時の処理
            if (collision) {
                SnapBubble();
                SetNextBubble();
            }
        }


        // -------------------------
        // 2. 描画処理
        // -------------------------

        // フィールドの枠線を描画
        DrawBox(FIELD_OFS_X, FIELD_OFS_Y, FIELD_OFS_X + FIELD_COLS * BUBBLE_DIAMETER, FIELD_OFS_Y + FIELD_ROWS * ROW_HEIGHT, GetColor(100, 100, 100), FALSE);

        // 配置されているバブルを描画
        for (int r = 0; r < FIELD_ROWS; ++r) {
            for (int c = 0; c < FIELD_COLS; ++c) {
                if (field[r][c] != NONE) {
                    double bx, by;
                    GetBubblePos(r, c, bx, by);
                    DrawCircle((int)bx, (int)by, BUBBLE_RADIUS - 1, GetDxColor(field[r][c]), TRUE);
                    // ハイライト（少し立体感を出す）
                    DrawCircle((int)bx - 4, (int)by - 4, 4, GetColor(255, 255, 255), TRUE);
                }
            }
        }

        // 大砲（発射の軌道線）を描画
        int cannonX = FIELD_OFS_X + (FIELD_COLS * BUBBLE_DIAMETER) / 2;
        int cannonY = FIELD_OFS_Y + FIELD_ROWS * (int)ROW_HEIGHT + 30;
        DrawLine(cannonX, cannonY, cannonX + (int)(cos(angle) * 50), cannonY - (int)(sin(angle) * 50), GetColor(255, 255, 255), 3);

        // 操作中のバブルを描画
        DrawCircle((int)px, (int)py, BUBBLE_RADIUS - 1, GetDxColor(pColor), TRUE);
        DrawCircle((int)px - 4, (int)py - 4, 4, GetColor(255, 255, 255), TRUE);

        // 次のバブルを描画（左下に小さく表示）
        DrawString(20, 500, "NEXT", GetColor(255, 255, 255));
        DrawCircle(40, 540, BUBBLE_RADIUS - 1, GetDxColor(nextColor), TRUE);

        // 操作説明
        DrawString(20, 20, "← → : 角度調整", GetColor(255, 255, 255));
        DrawString(20, 40, "SPACE : 発射", GetColor(255, 255, 255));

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}