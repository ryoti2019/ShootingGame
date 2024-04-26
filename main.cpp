#include<DxLib.h>
#include"_debug/_DebugDispOut.h"
#include"_debug/_DebugConout.h"

#define SCREEN_SIZE_X 640		//画面の横サイズ
#define SCREEN_SIZE_Y 480		//画面の縦サイズ
#define BG_SIZE_Y	  960		//背景の縦サイズ
#define PLAYER_SIZE_X 32		//自機の横サイズ
#define PLAYER_SIZE_Y 32		//自機の縦サイズ
#define ENEMY_SIZE_X 64			//敵の横サイズ
#define ENEMY_SIZE_Y 64			//敵の縦サイズ
#define ENEMY2_SIZE_X 64		//敵２の横サイス
#define ENEMY2_SIZE_Y 64		//敵２の縦サイズ
#define SHOT_SIZE_X 32			//弾の横サイズ
#define SHOT_SIZE_Y 32			//弾の縦サイズ
#define BEAM_SIZE_X 52			//ビームの横サイズ
#define BEAM_SIZE_Y 220			//ビームの縦サイズ
#define HADO_SIZE_X 72			//波動の横サイズ
#define HADO_SIZE_Y 72			//波動の縦サイズ
#define ANIM_MAX 24
#define BLAST_SIZE_X 96		//爆発の横サイズ
#define BLAST_SIZE_Y 96		//爆発の縦サイズ

//変数定義
//プレイヤー関連
int playerImage;		//グラフィックハンドル
int playerPosX;			//X座標
int playerPosY;			//Y座標
int playerSpeed;		//移動速度
bool playerAlive;		//生存フラグ

//敵関連
int enemyImage;			//グラフィックハンドル
int enemyPosX;			//X座標
int enemyPosY;			//Y座標
int enemySpeed;			//移動速度
bool enemyAlive;		//生存フラグ

int enemy2Image;
int enemy2PosX;
int enemy2PosY;
int enemy2Speed;
bool enemy2Alive;

//弾関連
int shotImage;			//グラフィックハンドル
int shotPosX;			//X座標
int shotPosY;			//Y座標
int shotSpeed;			//移動速度
bool shotAlive;			//生存フラグ(true:発射中 false:非発射中)
int shotKey;			//弾を撃つキーの状態
int shotKeyOld;			//弾を撃つキーの状態(1フレーム前)

int shot2Image;			//グラフィックハンドル
int shot2PosX;			//X座標
int shot2PosY;			//Y座標
int shot2Speed;			//移動速度
bool shot2Alive;		//生存フラグ(true:発射中 false:非発射中)
int shotKey2;			//弾を撃つキーの状態
int shotKeyOld2;		//弾を撃つキーの状態(1フレーム前)

int shot3Image;			//グラフィックハンドル
int shot3PosX;			//X座標
int shot3PosY;			//Y座標
int shot3Speed;			//移動速度
bool shot3Alive;		//生存フラグ(true:発射中 false:非発射中)
int shotKey3;			//弾を撃つキーの状態
int shotKeyOld3;		//弾を撃つキーの状態(1フレーム前)


//背景関連
int bgImage;			//グラフィックハンドル
int bgPosY1;			//1枚目の背景座標
int bgPosY2;			//2枚目の背景座標

//エフェクト関連
int blastImage[ANIM_MAX];			//グラフィックハンドル
int blastPosX;
int blastPosY;
int blast2PosX;
int blast2PosY;
int blastAnimCnt;		//アニメーションカウンター
int blastAnimData[23];		//アニメーションの再生番号
bool blastAlive;		//生存フラグ
bool blast2Alive;
bool blast3Alive;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// システム系初期化
	SetWindowText("2216008_寺師 遼");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);		//true:ウィンドウ false:フルスクリーン
	if (DxLib_Init() == -1)
	{
		TRACE("DXLIBの初期化失敗");
		return -1;
	}
	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 255);

	//ゲーム用初期化
	//グラフィックの登録
	playerImage = LoadGraph("image/player.png");
	if (playerImage == -1)
	{
		TRACE("プレイヤー画像の読み込み失敗");
	}

	enemyImage = LoadGraph("image/enemy.png");
	if (enemyImage == -1)
	{
		TRACE("敵画像の読み込み失敗");
	}

	enemy2Image = LoadGraph("image/enemy2.png");
	if (enemy2Image == -1)
	{
		TRACE("敵２画像の読み込み失敗");
	}


	shotImage = LoadGraph("image/shot.png");
	if (shotImage == -1)
	{
		TRACE("弾画像の読み込み失敗");
	}

	shot2Image = LoadGraph("image/beam.png");
	if (shot2Image == -1)
	{
		TRACE("ビーム画像の読み込み失敗");
	}

	shot3Image = LoadGraph("image/hado.png");
	if (shot3Image == -1)
	{
		TRACE("波動画像の読み込み失敗");
	}

	bgImage = LoadGraph("image/haikei.png");
	if (bgImage == -1)
	{
		TRACE("背景画像の読み込み失敗");
	}

	if(LoadDivGraph("image/blast.png", ANIM_MAX, 6, 4, BLAST_SIZE_X, BLAST_SIZE_Y, &blastImage[0]) == -1)
	{
		TRACE("爆発エフェクトの読み込み失敗");
	}

	

	//変数の初期化
	playerPosX = SCREEN_SIZE_X / 2 - PLAYER_SIZE_X / 2;
	playerPosY = SCREEN_SIZE_Y - PLAYER_SIZE_Y;
	playerSpeed = 5;
	playerAlive = true;


	enemyPosX = SCREEN_SIZE_X / 2 - ENEMY_SIZE_X / 2;
	enemyPosY = 0;
	enemySpeed = 3;
	enemyAlive = true;

	enemy2PosX = SCREEN_SIZE_X - ENEMY2_SIZE_X;
	enemy2PosY = 0;
	enemy2Speed = 5;
	enemy2Alive = true;

	shotPosX = 100; 
	shotPosY = SCREEN_SIZE_Y;
	shotSpeed = 10;
	shotAlive = false;
	shotKey = 0;
	shotKeyOld = 0;

	shot2PosX = 100;
	shot2PosY = SCREEN_SIZE_Y;
	shot2Speed = 20;
	shot2Alive = false;
	shotKey2 = 0;
	shotKeyOld2 = 0;

	shot3PosX = 100;
	shot3PosY = SCREEN_SIZE_Y;
	shot3Speed = 5;
	shot3Alive = false;
	shotKey3 = 0;
	shotKeyOld3 = 0;

	bgPosY1 = 0;
	bgPosY2 = bgPosY1 -BG_SIZE_Y;

	
	blastAnimCnt = 0;
	blastPosX = 0;
	blastPosY = 0;
	blastAnimData[0] = 0;
	blastAnimData[1] = 1;
	blastAnimData[2] = 2;
	blastAnimData[3] = 3;
	blastAnimData[4] = 4;
	blastAnimData[5] = 5;
	blastAnimData[6] = 6;
	blastAnimData[7] = 7;
	blastAnimData[8] = 8;
	blastAnimData[9] = 9;
	blastAnimData[10] = 10;
	blastAnimData[11] = 11;
	blastAnimData[12] = 12;
	blastAnimData[13] = 13;
	blastAnimData[14] = 14;
	blastAnimData[15] = 15;
	blastAnimData[16] = 16;
	blastAnimData[17] = 17;
	blastAnimData[18] = 18;
	blastAnimData[19] = 19;
	blastAnimData[20] = 20;
	blastAnimData[21] = 21;
	blastAnimData[22] = 22;
	blastAnimData[23] = 23;
	blastAlive = false;
	blast2Alive = false;
	blast3Alive = false;

	//BGM
	PlayMusic("sound/bgm.mp3", DX_PLAYTYPE_LOOP);
	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_dbgStartDraw();

		bgPosY1 += 2;
		bgPosY2 += 2;
		if (bgPosY1 >= SCREEN_SIZE_Y)
		{
			bgPosY1 = bgPosY2 - BG_SIZE_Y;
		}
		if (bgPosY2 >= SCREEN_SIZE_Y)
		{
			bgPosY2 = bgPosY1 - BG_SIZE_Y;
		}

		//敵の再出現処理
		if (enemyAlive == false)
		{
			enemyPosX = rand() % SCREEN_SIZE_Y;
			enemyPosY = -ENEMY_SIZE_Y;
			enemyAlive = true;
		}

		//敵２の再出現処理
		if (enemy2Alive == false)
		{
			enemy2PosX = rand() % SCREEN_SIZE_Y;
			enemy2PosY = -ENEMY2_SIZE_Y;
			enemy2Alive = true;
		}

		//自機の再出現処理
		if (playerAlive == false)
		{
			playerPosX = SCREEN_SIZE_X / 2 - PLAYER_SIZE_X / 2;
			playerPosY = SCREEN_SIZE_Y - PLAYER_SIZE_Y;
			playerAlive = true;
		}

		//弾の発射用のキー情報処理
		shotKeyOld = shotKey;
		shotKey = CheckHitKey(KEY_INPUT_Z);

		shotKeyOld2 = shotKey2;
		shotKey2 = CheckHitKey(KEY_INPUT_X);

		shotKeyOld3 = shotKey3;
		shotKey3 = CheckHitKey(KEY_INPUT_C);

		//プレイヤーの移動処理
		if (playerAlive == true)
		{
			if (CheckHitKey(KEY_INPUT_LEFT) == 1)
			{
				if (playerPosX - playerSpeed >= 0)
				{
					playerPosX -= playerSpeed;
				}
				else
				{
					playerPosX = 0;
				}
			}

			if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
			{
				if (playerPosX + playerSpeed <= SCREEN_SIZE_X - PLAYER_SIZE_X)
				{
					playerPosX += playerSpeed;
				}
				else
				{
					playerPosX = SCREEN_SIZE_X - PLAYER_SIZE_X;
				}
			}

			if (CheckHitKey(KEY_INPUT_UP) == 1)
			{
				if (playerPosY - playerSpeed >= 0)
				{
					playerPosY -= playerSpeed;
				}
				else
				{
					playerPosY = 0;
				}
			}

			if (CheckHitKey(KEY_INPUT_DOWN) == 1)
			{
				if (playerPosY + playerSpeed <= SCREEN_SIZE_Y - PLAYER_SIZE_Y)
				{
					playerPosY += playerSpeed;
				}
				else
				{
					playerPosY = SCREEN_SIZE_Y - PLAYER_SIZE_Y;
				}
			}

			//弾の発射処理
			if (shotKey == 1 && shotKeyOld == 0)
			{
				if (shotAlive == false)
				{
					shotPosX = playerPosX;
					shotPosY = playerPosY;
					PlaySoundFile("sound/shot.ogg", DX_PLAYTYPE_BACK);
					shotAlive = true;
				}
			}
			if (shotKey2 == 1 && shotKeyOld2 == 0)
			{
				if (shot2Alive == false)
				{
					shot2PosX = playerPosX - 10;
					shot2PosY = playerPosY;
					PlaySoundFile("sound/beam.ogg", DX_PLAYTYPE_BACK);
					shot2Alive = true;
				}
			}
			if (shotKey3 == 1 && shotKeyOld3 == 0)
			{
				if (shot3Alive == false)
				{
					shot3PosX = playerPosX -25;
					shot3PosY = playerPosY;
					PlaySoundFile("sound/hado.ogg", DX_PLAYTYPE_BACK);
					shot3Alive = true;
				}
			}
		}
		//弾の移動処理
		if (shotPosY <= -SHOT_SIZE_Y)
		{
			shotAlive = false;
		}
		if (shotAlive == true)
		{
			shotPosY -= shotSpeed;
		}

		if (shot2PosY <= -BEAM_SIZE_Y)
		{
			shot2Alive = false;
		}
		if (shot2Alive == true)
		{
			shot2PosY -= shot2Speed;
		}

		if (shot3PosY <= -HADO_SIZE_Y)
		{
			shot3Alive = false;
		}
		if (shot3Alive == true)
		{
			shot3PosY -= shot3Speed;
		}

		//敵への弾の当たり判定
		if (shotAlive == true && enemyAlive == true)
		{
			if (shotPosX < enemyPosX + ENEMY_SIZE_X && enemyPosX < shotPosX + SHOT_SIZE_X && shotPosY < enemyPosY + ENEMY_SIZE_Y && enemyPosY < shotPosY + SHOT_SIZE_Y)
			{
				blastPosX = enemyPosX;
				blastPosY = enemyPosY;
				shotAlive = false;
				enemyAlive = false;
				blastAlive = true;
			}
			if (enemyAlive == false && blastAlive == true)
			{
				PlaySoundFile("sound/enemyblast.ogg", DX_PLAYTYPE_BACK);
				blastAnimCnt = 0;
			}
		}

		if (shot2Alive == true && enemyAlive == true)
		{
			if (shot2PosX < enemyPosX + ENEMY_SIZE_X && enemyPosX < shot2PosX + BEAM_SIZE_X && shot2PosY < enemyPosY + ENEMY_SIZE_Y && enemyPosY < shot2PosY + BEAM_SIZE_Y)
			{
				blastPosX = enemyPosX;
				blastPosY = enemyPosY;
				shot2Alive = false;
				enemyAlive = false;
				blastAlive = true;
			}
			if (enemyAlive == false && blastAlive == true)
			{
				PlaySoundFile("sound/enemyblast.ogg", DX_PLAYTYPE_BACK);
				blastAnimCnt = 0;
			}

		}

		if (shot3Alive == true && enemyAlive == true)
		{
			if (shot3PosX < enemyPosX + ENEMY_SIZE_X && enemyPosX < shot3PosX + HADO_SIZE_X && shot3PosY < enemyPosY + ENEMY_SIZE_Y && enemyPosY < shot3PosY + HADO_SIZE_Y)
			{
				blastPosX = enemyPosX;
				blastPosY = enemyPosY;
				shot3Alive = false;
				enemyAlive = false;
				blastAlive = true;
			}
			if (enemyAlive == false && blastAlive == true)
			{
				PlaySoundFile("sound/enemyblast.ogg", DX_PLAYTYPE_BACK);
				blastAnimCnt = 0;
			}

		}

		//敵２への弾の当たり判定
		if (shotAlive == true && enemy2Alive == true)
		{
			if (shotPosX < enemy2PosX + ENEMY2_SIZE_X && enemy2PosX < shotPosX + SHOT_SIZE_X && shotPosY < enemy2PosY + ENEMY2_SIZE_Y && enemy2PosY < shotPosY + SHOT_SIZE_Y)
			{
				blastPosX = enemy2PosX;
				blastPosY = enemy2PosY;
				shotAlive = false;
				enemy2Alive = false;
				blast2Alive = true;
			}
			if (enemy2Alive == false && blast2Alive == true)
			{
				PlaySoundFile("sound/enemyblast.ogg", DX_PLAYTYPE_BACK);
				blastAnimCnt = 0;
			}
		}

		if (shot2Alive == true && enemy2Alive == true)
		{
			if (shot2PosX < enemy2PosX + ENEMY2_SIZE_X && enemy2PosX < shot2PosX + BEAM_SIZE_X && shot2PosY < enemy2PosY + ENEMY2_SIZE_Y && enemy2PosY < shot2PosY + BEAM_SIZE_Y)
			{
				blastPosX = enemy2PosX;
				blastPosY = enemy2PosY;
				shot2Alive = false;
				enemy2Alive = false;
				blast2Alive = true;
			}
			if (enemy2Alive == false && blast2Alive == true)
			{
				PlaySoundFile("sound/enemyblast.ogg", DX_PLAYTYPE_BACK);
				blastAnimCnt = 0;
			}
		}

		if (shot3Alive == true && enemyAlive == true)
		{
			if (shot3PosX < enemyPosX + ENEMY2_SIZE_X && enemy2PosX < shot3PosX + HADO_SIZE_X && shot3PosY < enemy2PosY + ENEMY2_SIZE_Y && enemy2PosY < shot3PosY + HADO_SIZE_Y)
			{
				blastPosX = enemy2PosX;
				blastPosY = enemy2PosY;
				shot3Alive = false;
				enemy2Alive = false;
				blast2Alive = true;
			}
			if (enemy2Alive == false && blast2Alive == true)
			{
				PlaySoundFile("sound/enemyblast.ogg", DX_PLAYTYPE_BACK);
				blastAnimCnt = 0;
			}
		}

		//敵の移動処理
		if (enemyAlive == true)
		{
			enemyPosY += enemySpeed;
			if (enemyPosY >= SCREEN_SIZE_Y)
			{
				enemyAlive = false;
			}
		}

		//敵２の移動処理
		if (enemy2Alive == true)
		{
			enemy2PosY += enemy2Speed;
			if (enemy2PosY >= SCREEN_SIZE_Y)
			{
				enemy2Alive = false;
			}
		}

		//敵の当たり判定
		if (playerAlive == true && enemyAlive == true)
		{
			if (playerPosX < enemyPosX + ENEMY_SIZE_X && enemyPosX < playerPosX + PLAYER_SIZE_X && playerPosY < enemyPosY + ENEMY_SIZE_Y && enemyPosY < playerPosY + PLAYER_SIZE_Y)
			{
				blastPosX = playerPosX;
				blastPosY = playerPosY;
				playerAlive = false;
				enemyAlive = false;
				blast3Alive = true;
			}
			if (playerAlive == false && blast3Alive == true)
			{
				
				PlaySoundFile("sound/playerblast.ogg", DX_PLAYTYPE_BACK);
				blastAnimCnt = 0;
			}
		}

		//敵２の当たり判定
		if (playerAlive == true && enemy2Alive == true)
		{
			if (playerPosX < enemy2PosX + ENEMY2_SIZE_X && enemy2PosX < playerPosX + PLAYER_SIZE_X && playerPosY < enemy2PosY + ENEMY2_SIZE_Y && enemy2PosY < playerPosY + PLAYER_SIZE_Y)
			{
				blastPosX = playerPosX;
				blastPosY = playerPosY;
				playerAlive = false;
				enemy2Alive = false;
				blast3Alive = true;
			}
			if (playerAlive == false && blast3Alive == true)
			{
				PlaySoundFile("sound/playerblast.ogg", DX_PLAYTYPE_BACK);
				blastAnimCnt = 0;
			}
			
		}
		
		_TRACE_S(0xffffff, "playerPosX", playerPosX);
		_TRACE_S(0xffffff, "playerPosY", playerPosY);

		//TRACE("playerPosX:%d  ", playerPosX);
		//TRACE("playerPosY:%d\n", playerPosY);

		SetDrawScreen(DX_SCREEN_BACK);							//描画先をバックバッファに設定
		ClsDrawScreen();										//描画先のクリアー
		DrawGraph(0, bgPosY1, bgImage, true);
		DrawGraph(0, bgPosY2, bgImage, true);
		if (enemyAlive == true)
		{
			DrawGraph(enemyPosX, enemyPosY, enemyImage, true);	//敵の描画
		}

		if (enemy2Alive == true)
		{
			DrawGraph(enemy2PosX, enemy2PosY, enemy2Image, true);	//敵２の描画
		}

		if (shotAlive == true)
		{
			DrawGraph(shotPosX, shotPosY, shotImage, true);			//弾の描画
		}

		if (shot2Alive == true)
		{
			DrawGraph(shot2PosX, shot2PosY, shot2Image, true);			//ビームの描画
		}

		if (shot3Alive == true)
		{
			DrawGraph(shot3PosX, shot3PosY, shot3Image, true);			//波動の描画
		}

		if (playerAlive == true)
		{
			DrawGraph(playerPosX, playerPosY, playerImage, true);	//自機の描画
		}

		if (blastAlive == true)
		{
			DrawGraph(blastPosX - 16, blastPosY - 16, blastImage[blastAnimData[blastAnimCnt / 2] % 24], true);		//爆発の描画
			if (blastAnimCnt == 24)
			{
				blastAlive = false;
			}
			else
			{
				blastAnimCnt++;
			}
		}

		if (blast2Alive == true)
		{
			DrawGraph(blastPosX - 16, blastPosY - 16, blastImage[blastAnimData[blastAnimCnt / 2] % 24], true);		//爆発の描画
			if (blastAnimCnt == 24)
			{
				blast2Alive = false;
			}
			else
			{
				blastAnimCnt++;
			}
		}
		

		if (blast3Alive == true)
		{
			DrawGraph(playerPosX - 32, playerPosY - 32, blastImage[blastAnimData[blastAnimCnt / 2] % 24], true);		//爆発の描画
			if (blastAnimCnt == 24)
			{
				blast3Alive = false;
			}
			else
			{
				blastAnimCnt++;
			}
		}
		

		_dbgDraw();
		ScreenFlip();												//バックバッファとフロントバッファの入れ替え
		
	}
	//終了処理
	DxLib_End();
	return 0;

}