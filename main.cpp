#include<DxLib.h>
#include"_debug/_DebugDispOut.h"
#include"_debug/_DebugConout.h"

#define SCREEN_SIZE_X 640		//��ʂ̉��T�C�Y
#define SCREEN_SIZE_Y 480		//��ʂ̏c�T�C�Y
#define BG_SIZE_Y	  960		//�w�i�̏c�T�C�Y
#define PLAYER_SIZE_X 32		//���@�̉��T�C�Y
#define PLAYER_SIZE_Y 32		//���@�̏c�T�C�Y
#define ENEMY_SIZE_X 64			//�G�̉��T�C�Y
#define ENEMY_SIZE_Y 64			//�G�̏c�T�C�Y
#define ENEMY2_SIZE_X 64		//�G�Q�̉��T�C�X
#define ENEMY2_SIZE_Y 64		//�G�Q�̏c�T�C�Y
#define SHOT_SIZE_X 32			//�e�̉��T�C�Y
#define SHOT_SIZE_Y 32			//�e�̏c�T�C�Y
#define BEAM_SIZE_X 52			//�r�[���̉��T�C�Y
#define BEAM_SIZE_Y 220			//�r�[���̏c�T�C�Y
#define HADO_SIZE_X 72			//�g���̉��T�C�Y
#define HADO_SIZE_Y 72			//�g���̏c�T�C�Y
#define ANIM_MAX 24
#define BLAST_SIZE_X 96		//�����̉��T�C�Y
#define BLAST_SIZE_Y 96		//�����̏c�T�C�Y

//�ϐ���`
//�v���C���[�֘A
int playerImage;		//�O���t�B�b�N�n���h��
int playerPosX;			//X���W
int playerPosY;			//Y���W
int playerSpeed;		//�ړ����x
bool playerAlive;		//�����t���O

//�G�֘A
int enemyImage;			//�O���t�B�b�N�n���h��
int enemyPosX;			//X���W
int enemyPosY;			//Y���W
int enemySpeed;			//�ړ����x
bool enemyAlive;		//�����t���O

int enemy2Image;
int enemy2PosX;
int enemy2PosY;
int enemy2Speed;
bool enemy2Alive;

//�e�֘A
int shotImage;			//�O���t�B�b�N�n���h��
int shotPosX;			//X���W
int shotPosY;			//Y���W
int shotSpeed;			//�ړ����x
bool shotAlive;			//�����t���O(true:���˒� false:�񔭎˒�)
int shotKey;			//�e�����L�[�̏��
int shotKeyOld;			//�e�����L�[�̏��(1�t���[���O)

int shot2Image;			//�O���t�B�b�N�n���h��
int shot2PosX;			//X���W
int shot2PosY;			//Y���W
int shot2Speed;			//�ړ����x
bool shot2Alive;		//�����t���O(true:���˒� false:�񔭎˒�)
int shotKey2;			//�e�����L�[�̏��
int shotKeyOld2;		//�e�����L�[�̏��(1�t���[���O)

int shot3Image;			//�O���t�B�b�N�n���h��
int shot3PosX;			//X���W
int shot3PosY;			//Y���W
int shot3Speed;			//�ړ����x
bool shot3Alive;		//�����t���O(true:���˒� false:�񔭎˒�)
int shotKey3;			//�e�����L�[�̏��
int shotKeyOld3;		//�e�����L�[�̏��(1�t���[���O)


//�w�i�֘A
int bgImage;			//�O���t�B�b�N�n���h��
int bgPosY1;			//1���ڂ̔w�i���W
int bgPosY2;			//2���ڂ̔w�i���W

//�G�t�F�N�g�֘A
int blastImage[ANIM_MAX];			//�O���t�B�b�N�n���h��
int blastPosX;
int blastPosY;
int blast2PosX;
int blast2PosY;
int blastAnimCnt;		//�A�j���[�V�����J�E���^�[
int blastAnimData[23];		//�A�j���[�V�����̍Đ��ԍ�
bool blastAlive;		//�����t���O
bool blast2Alive;
bool blast3Alive;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �V�X�e���n������
	SetWindowText("2216008_���t ��");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);		//true:�E�B���h�E false:�t���X�N���[��
	if (DxLib_Init() == -1)
	{
		TRACE("DXLIB�̏��������s");
		return -1;
	}
	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 255);

	//�Q�[���p������
	//�O���t�B�b�N�̓o�^
	playerImage = LoadGraph("image/player.png");
	if (playerImage == -1)
	{
		TRACE("�v���C���[�摜�̓ǂݍ��ݎ��s");
	}

	enemyImage = LoadGraph("image/enemy.png");
	if (enemyImage == -1)
	{
		TRACE("�G�摜�̓ǂݍ��ݎ��s");
	}

	enemy2Image = LoadGraph("image/enemy2.png");
	if (enemy2Image == -1)
	{
		TRACE("�G�Q�摜�̓ǂݍ��ݎ��s");
	}


	shotImage = LoadGraph("image/shot.png");
	if (shotImage == -1)
	{
		TRACE("�e�摜�̓ǂݍ��ݎ��s");
	}

	shot2Image = LoadGraph("image/beam.png");
	if (shot2Image == -1)
	{
		TRACE("�r�[���摜�̓ǂݍ��ݎ��s");
	}

	shot3Image = LoadGraph("image/hado.png");
	if (shot3Image == -1)
	{
		TRACE("�g���摜�̓ǂݍ��ݎ��s");
	}

	bgImage = LoadGraph("image/haikei.png");
	if (bgImage == -1)
	{
		TRACE("�w�i�摜�̓ǂݍ��ݎ��s");
	}

	if(LoadDivGraph("image/blast.png", ANIM_MAX, 6, 4, BLAST_SIZE_X, BLAST_SIZE_Y, &blastImage[0]) == -1)
	{
		TRACE("�����G�t�F�N�g�̓ǂݍ��ݎ��s");
	}

	

	//�ϐ��̏�����
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
	//�Q�[�����[�v
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

		//�G�̍ďo������
		if (enemyAlive == false)
		{
			enemyPosX = rand() % SCREEN_SIZE_Y;
			enemyPosY = -ENEMY_SIZE_Y;
			enemyAlive = true;
		}

		//�G�Q�̍ďo������
		if (enemy2Alive == false)
		{
			enemy2PosX = rand() % SCREEN_SIZE_Y;
			enemy2PosY = -ENEMY2_SIZE_Y;
			enemy2Alive = true;
		}

		//���@�̍ďo������
		if (playerAlive == false)
		{
			playerPosX = SCREEN_SIZE_X / 2 - PLAYER_SIZE_X / 2;
			playerPosY = SCREEN_SIZE_Y - PLAYER_SIZE_Y;
			playerAlive = true;
		}

		//�e�̔��˗p�̃L�[��񏈗�
		shotKeyOld = shotKey;
		shotKey = CheckHitKey(KEY_INPUT_Z);

		shotKeyOld2 = shotKey2;
		shotKey2 = CheckHitKey(KEY_INPUT_X);

		shotKeyOld3 = shotKey3;
		shotKey3 = CheckHitKey(KEY_INPUT_C);

		//�v���C���[�̈ړ�����
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

			//�e�̔��ˏ���
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
		//�e�̈ړ�����
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

		//�G�ւ̒e�̓����蔻��
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

		//�G�Q�ւ̒e�̓����蔻��
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

		//�G�̈ړ�����
		if (enemyAlive == true)
		{
			enemyPosY += enemySpeed;
			if (enemyPosY >= SCREEN_SIZE_Y)
			{
				enemyAlive = false;
			}
		}

		//�G�Q�̈ړ�����
		if (enemy2Alive == true)
		{
			enemy2PosY += enemy2Speed;
			if (enemy2PosY >= SCREEN_SIZE_Y)
			{
				enemy2Alive = false;
			}
		}

		//�G�̓����蔻��
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

		//�G�Q�̓����蔻��
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

		SetDrawScreen(DX_SCREEN_BACK);							//�`�����o�b�N�o�b�t�@�ɐݒ�
		ClsDrawScreen();										//�`���̃N���A�[
		DrawGraph(0, bgPosY1, bgImage, true);
		DrawGraph(0, bgPosY2, bgImage, true);
		if (enemyAlive == true)
		{
			DrawGraph(enemyPosX, enemyPosY, enemyImage, true);	//�G�̕`��
		}

		if (enemy2Alive == true)
		{
			DrawGraph(enemy2PosX, enemy2PosY, enemy2Image, true);	//�G�Q�̕`��
		}

		if (shotAlive == true)
		{
			DrawGraph(shotPosX, shotPosY, shotImage, true);			//�e�̕`��
		}

		if (shot2Alive == true)
		{
			DrawGraph(shot2PosX, shot2PosY, shot2Image, true);			//�r�[���̕`��
		}

		if (shot3Alive == true)
		{
			DrawGraph(shot3PosX, shot3PosY, shot3Image, true);			//�g���̕`��
		}

		if (playerAlive == true)
		{
			DrawGraph(playerPosX, playerPosY, playerImage, true);	//���@�̕`��
		}

		if (blastAlive == true)
		{
			DrawGraph(blastPosX - 16, blastPosY - 16, blastImage[blastAnimData[blastAnimCnt / 2] % 24], true);		//�����̕`��
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
			DrawGraph(blastPosX - 16, blastPosY - 16, blastImage[blastAnimData[blastAnimCnt / 2] % 24], true);		//�����̕`��
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
			DrawGraph(playerPosX - 32, playerPosY - 32, blastImage[blastAnimData[blastAnimCnt / 2] % 24], true);		//�����̕`��
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
		ScreenFlip();												//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
		
	}
	//�I������
	DxLib_End();
	return 0;

}